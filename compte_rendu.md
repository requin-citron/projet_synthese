## Compte rendu


<!-- TABLE OF CONTENTS -->
  <summary>Sommaire</summary>
  <ol>
    <li>
        <a href="#math">Les Maths</a>
    </li>
    <li>
        <a href="#modelisation">Modélisation</a>
        <ul>
          <li><a href="#corp">Corps</a></li>
          <li><a href="#head">Tête</a></li>
          <li><a href="#yeux">Yeux</a></li>
          <li><a href="#cornes">Cornes</a></li>
          <li><a href="#ailes">Ailes</a></li>
          <li><a href="#assemblage">Assemblage</a></li>
        </ul>
    </li>
    <li><a href="#animation">Animation</a></li>
      <ul>
        <li><a href="#mouvement_tete">Mouvement Tête</a></li>
        <li><a href="#feu">Feu</a></li>
        <li><a href="#laser">Laser</a></li>
        <li><a href="#mouvement_corp">Animation corp</a></li>
        <li><a href="#mouvement_cornes">Mouvement Cornes</a></li>
        <li><a href="#mouvement_yeux">Mouvement Yeux</a></li>
        <li><a href="#mouvement_ailes">Mouvement Ailes</a></li>
        <li><a href="#camera">Camera</a></li>
    </ul>
    <li><a href="">Lumières</a></li>
  </ol>




### Les Maths {#math}

Nous allons utiliser énormément l'algèbre linaire pour dessiner le dragon.
Pour cela nous avons crée plusieurs fonctions permetant de faire les choses de bases.

Trois structures dans le code sont intéressantes

1. [point](structpoint.html)
2. [vector](structvector.html)
3. [matrix](structmatrix.html)

la structure de point et vector sont identiques cela permet de bien differencier dans les fonction qui fais quoi.
Le code permet de de faire des changement de base de facon transparante.

#### Problématique

Dans le cas ou l'on dessine une courbe de besizer ou autres. Si l'on veux desiner un parterne, il ne suivera pas le shema car il sera dans le plan par default.

Il faut donc utiliser le vecteur tangent pour dessiner le parterne sur le plan decrit par celui ci.

#### resolution

##### Calcule de la tangent

Avec OpenGL si nous voulons utiliser des formules parametrique nous avons besoin de les discrétiser.
Par example pour un cercle nous sommes obligée de le transformer en plusieur segment.Avec beaucoup de segment nous formons un cercle.

Dans notre cas nous n'avons pas besoin de calculer la dérivé notre figures est une suite de segment qui sont pas définition la dérivé.

##### Calcule de la base

Maintenant que nous avons le verteur normal de notre plan il ne nous reste plus qu'a calculer deux vecteur du plan orthogono entre eux.
Pour cela nous allons utiliser le dot product et le cross product.
Pour le premier vecteur il suffit de trouver un vecteur qui crée un dot product entre le vecteur normal est celui ci.


$$\overrightarrow{\boldsymbol{N}}=\begin{pmatrix} x \\\ y \\\ z \end{pmatrix}$$
$$\overrightarrow{\boldsymbol{N}}\cdot \overrightarrow{\boldsymbol{V1}} = 0$$
$$\boldsymbol{Nx}\cdot\boldsymbol{V1x}+\boldsymbol{Ny}\cdot\boldsymbol{V1y}+\boldsymbol{Nz}\cdot\boldsymbol{V1z}=0$$
$$\boldsymbol{V1x}=\frac{1}{Nx} \ \ \ \ \ \ \ \ \ \ \ \ \boldsymbol{V1x}=\frac{-1}{Ny}\ \ \ \ \ \ \ \ \ \ \ \ \boldsymbol{V1x}=0$$

Nous avons maintenant un vecteur du plan ainsi que le vecteur normal.
$$Calculons\ \ \boldsymbol{V2}\ \ a\ \ l'aide\ \ du\ \ cross\ \ product$$
$$\overrightarrow{\boldsymbol{V2}} = \overrightarrow{\boldsymbol{N}}\wedge\overrightarrow{\boldsymbol{V1}}$$
$$\overrightarrow{\boldsymbol{V2}} = \begin{pmatrix} \boldsymbol{Ny}\cdot\boldsymbol{V1z} - \boldsymbol{Nz}\cdot\boldsymbol{V1y} \\\ \boldsymbol{Nz}\cdot\boldsymbol{V1x} - \boldsymbol{Nx}\cdot\boldsymbol{V1z} \\\ \boldsymbol{Nx}\cdot\boldsymbol{V1y} - \boldsymbol{Ny}\cdot\boldsymbol{V1x} \end{pmatrix}$$
Pour avoir une base homogène nous devons maintenant normaliser nos 3 vecteur.
c'est dire que la norme de chaque vecteur soit égale a 1.

![normalize](../images/normalise_exemple.png)

Pour cela nous devoir diviser tout les composante des vecteur par leurs normes
$$Malheureusement\ \ nous\ \ avons\ \ besoin\ \ de\ \ calculer\ \ \frac{1}{\sqrt{\|\|\overrightarrow{\boldsymbol{V}\|\|}}}$$
Cette expression est utilisé un **trés trés** grand nombre de fois, mais elle est trés couteuse
en resource.Pour cela nous avons utilisé un hack qui permet de calculer 1/sqrt(x) de facon **trés** rapide
avec une faible marge d'erreur.

[**Video explicative sur youtube**](https://www.youtube.com/watch?v=p8u_k2LIZyo)

Nous avons maintenant tout ce qu'il faut pour faire une base.
$$B\ =\ \begin{pmatrix} Nx & V1x & V2x \\\ Ny & V1y & V2y \\\ Nz & V1z & V2z \end{pmatrix}$$

Maintenant que nous avons la matrice qui décrit notre base nous pouvons traduire des points de notre base X,Y,Z
dans notre nouvelle base B
$$\begin{pmatrix} P'x \\\ P'y \\\ P'z \end{pmatrix}\ =\ \begin{pmatrix} Nx & V1x & V2x \\\ Ny & V1y & V2y \\\ Nz & V1z & V2z \end{pmatrix}\cdot\begin{pmatrix} Px \\\ Py \\\ Pz \end{pmatrix}$$

Nous pouvons maintenant tracer tout ce qu'on veut qui suit une courbe de bézier par example:<br/>

![normalize](../images/normalise_exemple1.png) ![normalize](../images/normalise_exemple2.png)

Maintenant que nos outils sont prés nous allons pouvoir commencer la modélisation.

### Modélisation {#modelisation}

#### Le Corps {#corp}

Nous Somme partie sur un dragon en spirale. Nous avons donc commencé par faire une spirale en lignes.
Pour ensuite utiliser ce les maths vue plus haut pour crée un cylindre qui suis la ligne.
##### La spirale

Pour faire un cercle il suffit de décomposer le cercle en petit segment. Puis il ne reste plus qu'a incrementer la hauteur a chaque iteration et de faire plusieur cercles pour obtenir une spirale.

`Toutes les constantes pour jouer avec la spirale sont dans spring.h`

![spirale1](../images/spirale1.png) ![spirale2](../images/spirale2.png)

Il ne reste plus qu'a remplacer la ligne par un cylindre pour obtenir **un corp imparfait**
effectivement a cause du changement de base entre chaque cylindre apparait un vide.

![probleme1](../images/probleme1.png)

Nous avons deux facon de résoudre ce problème
##### Solution 1

Nous pouvons reboucher l'ecart entre deux sections en créant un autre cylindre.

##### Solution 2

Nous pouvons également relier le nouveau cylindre a l'encien directement.

##### Solution retenue

Nous avons utilisé les deux solutions l'une permet de donner un aspect avec des cassure (utiliser pour le corp) et une permet de donner un aspect uniforme

![spirale3](../images/spirale3.png)       ![head1](../images/head1.png)

En jouant avec les paramétre il est possible d'obtenir des resultats sympas

![spirale4](../images/spirale4.png)

##### Texture

Pour la peau de dragon nous utiliserons une image trouvé sur google image.
il suffit aprés de l'enrouler autout du cylindre pour ca on découpe la texture en largeur en autant de morceaux que d'iteration pour faire le cylindre.Il suffit de coller chaque moceau a chaque face du cylindre.

![dragon](../images/dragon.jpg)       ![spirale5](../images/spirale5.png)

#### La Tête {#head}

Pour la tete nous avons opté pour une courbe de bézier qui permet de faire des forme plus "naturelle"
ainsi que de pouvoir l'animer facilement.
Nous utiliserons une courbe de bezier en 4 points

![kig1](../images/kig1.png)

Nous avons implementé une animation en modifiant les deux premier point de controle de la courbe de bezier.
Le dragon sera capable de baisser la tete. La transition des deux images ce fais de manière linaire pour un résultat optimal.

![kig2](../images/kig2.png)

Il ne reste plus qu'a tracer un cylindre de rayon variable.
En utilisant la deuxieme technique de rebouchage pour donner un aspect lisse a la tete.
Puis on colle les textures sur la tête comme pour le corp.
Nous avons donc toutes les grosses pièce.

![head2](../images/head2.png)

#### Les Yeux {#yeux}

Nous yeux sont représenté par une sphere. Pour cela nous avons codé notre propre sphére.<br/>
Nous avons expliquer aux dessus comment dessiner un cercle.
On peut donc faire un conne facilement en augmentant la hauteur et en diminuant le rayon.

![chepito](../images/chapito.png)

Maintenant nous voulons une shpere pour cela nous allons utiliser pythagore.<br/>
Nous allons utiliser cette propriétée pour obtenir la hauteur en fontion du rayon.
$$Avec\ \ R\ \ le\ \ Rayon$$
$$sin(\alpha)^2 + cos(\alpha)^2 = 1$$
$$(R\cdot sin(\alpha))^2 + (R\cdot cos(\alpha))^2 = R^2$$
$$Y^2 + X^2 = R^2$$
$$Y = \sqrt{R^2 - X^2}$$

![demi_sphere](../images/demi_sphere.png)

Ils ne reste plus qu'a faire le symétrique.<br/>
Pour la texture il suffit de mettre en noir un intervalede polygon.<br/>
Tout le reste en blanc.

![yeux](../images/yeux.png)

#### Les Cornes {#cornes}

Nous voulions partir sur un disign type corail ou chandelié.<br/>
Pour cela nous avons utilisé un empilement de pavé drois la encore codé par nos soins.<br/>
Nous somme partie sur un pavée droit horizontal et deux vertical

![pavee](../images/corne1.png)

Nous avons opté pour un algorithme récusif qui nous permet de générer un empilement de ce parterne.<br/>
L'algorithme va s'executer N fois et a chaque recursion va désinner le même partern en plus petit aux bout des pavée vertical.

![corne2](../images/corne2.png)

Nous trouvions le resultats trop plat, pour cela nous avons, dans la fonction de création, crée plusieur parternes comme ci dessus espacé d'un angle.<br/>
Le resultat est assez intéressant et nous avons décidé de le garder.

![corne3](../images/corne3.png)

#### Ailes {#ailes}

Il reste une dernière pièce a notre dragon les ailes.
Nous voulions partir sur quelque chose de différent pour donné un style sympas a notre dragon.<br/>
Nous avons donc opté pour une répésentation sans polygon.<br/>
En effet nos ailes ne sont que des lignes blanches qui donne un style Winx.<br/>

![winx](../images/winx.png)

Pour cela nous avons fais une conique en 5 point  pour représenté une figure fermée qui ce raproche d'une éllipse sans en etre une.<br/>
Malheureusement nous n' avions que les points, aprés plusieurs recherche sur internet nous avons trouvé des articles qui expliquer comment recupérer l'equation a partir de ces 5 points.<br/>
Malheureusement c'etait un petit peu trop dur pour nous et nous avons légérement triché.

![geogebra](../images/geogebra.png)

Nous avons maintenant notre équation paramétre !

$$t \in [0;2\pi]$$
$$X\ \ = \ \ 1.43 - 1.39\cdot cos(t)\ \ +\ \ 0.21\cdot sin(t)$$
$$Y\ \ = \ \ 1.13 -1.08\cdot cos(t)\ \ -\ \ 0.26\cdot sin(t)$$

En faisant varier t nous obtenons notre figure.
De plus nous avons déssiner plusieurs fois la meme figures avec une diminution d'échelle a chaque fois.<br/>
ce qui nous permet de remplir un peu l'aile.

![ailes](../images/ailes1.png)

#### Assemblage {#assemblage}

Maintenant que nous avons tout nos morceaux il faut les assembler.
Pour rappel nous avons:

* Le corp
* La tête
* Les yeux
* Les cornes
* Les ailes

> <span style="color:red"> Translation et Rotation le quel en premier</span><br/>Nous avons empiriquement remarqué que la rotation faisais une rotation local et non une rotation a partir de l'origin ce qui est de mémoire l'inverse que ce que nous avons vue en cours.La translation ce fais avec les coordonée du répére local de la pièce. C'est pour cela que nous translaton avant de faire une rotation. Dans le cas inverse le repère local est inversé et donc la translation est bièsé.


##### Tête + Yeux + Cornes

Dans le premier assemblage nous fusionons les yeux avec la tete et les cones avec la tête.
La tete ayant comme axe de symetrie l'axe X nous allons nous en servir pour place juste un oeil et une corne de facon propre la symétrie fera le reste.<br/>
Nous avons utilisé notre courbe de bézier ainsi que notre fonction de calcule de rayon en fonction de t (bézier), pour placé l'oeil en effet nous connaisons la possition de la courbe de bézier dans l'espace ainsi que sont rayon a cette endroit nous avons plus qu'a translaté l'oeil aux coordonée donnée par la courbe de bézier en additionant le rayon ainsi qu'un décalage obtenue la main pour le décaler un peu sur le coté.<br/>
Il suffit de faire la même chose avec juste un décalage négatif pour mettre l'oeil de l'autre coté.<br/>
L'intéré de possitioner l'oeil en fonction de la courbe de bézier c'est que lors de l'animation de la tete les yeux suives parfaitement le mouvement.

Ou utilise le meme procédé pour les cournes avec juste un décalage sur la courbe de bézier pour quelle sont aprés les yeux, de la même manière les cornes suive parfaitement le mouvement de la tête.

![head3](../images/head3.png)

##### Tête + Corps
Il faut maintenant racordé le corp a la tête, c'est la partie la plus subtile car les deux extrémité de sont pas parfaitement droit.<br/>
nous aurions pue faire un cylindre droit qui bouche cette espace mais nous trouvions ca pas propre nous avons donc réutilisé ce que nous avions fais pour le corps et la tête.<br/>
Effectivement nous avons récupéré le dernier point ainsi que sa matrice de base du corp et de la tête.<br/>
Il ne nous reste plus qu'a relier les deux morceau.

![raccord1](../images/raccord1.png) ![raccord2](../images/raccord2.png)

On vois que que tout es parfaitement raccord.

##### Ailes + Corp

Les ailes sont déployable !(cf plus loin) nous avons voulais faire des pair d'ailes nous avons donc mis des mini ailes deux a deux sur les deux dernière spirales du dragon toutes les 4 section.<br/>
De base elles sont rétracté donc on ne les vois casiment pas.

De la même manière nous avons translaté les ailes sur la spirale + le rayon de corp puis nous les avons tourné de manière quelle soit orthogonal aux vecteur rayon (cela ce fais facilement gace a l'angle permétant de tracer les petit segment d'un cercle).

![ailes2](../images/ailes2.png)

### Animation {#animation}

Nous allons traité des animations il a deux type d'annimations:
* Mouvement de Caméra
* Mouvement du Dragon

Nous avons opté pour un mouvement de tête un jet de laser et de feu ainsi que des ailes.<br/>
Pour la caméra nous pouvons nous raprocher nous éloigner et tourner autout du dragon.

#### Mouvement Tête {#mouvement_tete}

Comme expliqué plus haut notre tête est basé sur un courbe de bézier il suffit de modifier les coordonées de ces points pour faire bouger la tête.<br/>
nous avons donc utilisé une variable globale allant de 0 a 100 controlé par le clavier qui permet de progressivement changer les points de la courbe la tête étant basé dessus la tête bouge !

#### Feu {#feu}

Notre dragon tire du feux !
Pour modéliser le feux nous some partie sur l'idée d'utiliser un prisme avec un dégradé de rouge.

![fire1](../images/fire1.png)

Ils suffit ensuite de crée énormément de de prisme de petite tailles (comme des particules).<br/>
Puis de les placer de facon alléatoire dans un cylindre avec des angle aléatoire, le prisme avec un angle aléatoire donne une impression de particules et le placement alétoire donne une impression de progression.<br/>
Le déplacement des particules est une ilusion mais du faite de la nature de l'oeil humain l'imprésion de jet de feu fonctionne.

![fire2](../images/fire2.png)

Il suffit de donner le rayon de la pointe du nez pour que le rayon du feu soit de bonne taille
et de le translater aux bonne endroit (ici on utilise le meme principe que pour les yeux et les conres).

#### Laser {#laser}

Le laser est juste un cylindre bleu mis aux même endoit que le feu.<br/>
Nous trouvions notre laser enuyant comparé a notre feu pour cela nous avons rajouté des particules.<br/>
Pour cela nous avons desinner des cercle bleu autour du laser puis nous avons rendu leur rayon et leur décalage du début du laser alétoire.<br/>
ce qui signifie que tout les segment qui compose un cercle sont décalé ce qui donne un impression de particule.

![laser](../images/laser.png)

#### Animation Corp {#mouvement_corp}

Nous avons décidé de faire une animation de chargement du laser et du feu qui serais visible sur le corps.<br/>
Pour cela nous allons utilisé les striurre entre les cylindre du corp, en les faisant changer de couleur de facon progressive.<br/>
On chane la couleur des entre cylindre de facon progressive de la queue a la tete.

![laser_action](../images/laser_action.png)

![feu_action](../images/feu_action.png)

#### Mouvement Cornes {#mouvement_cornes}

De la même manière nous avons voulue donner une annimation aux cornes lors du chargement du laser ou du feu.<br/>
Pour cela nous avons décidé de faire tourner les cornes sur elles même lors du chargement.<br/>

#### Mouvement Yeux {#mouvement_yeux}

De la même manière nous avons décidé de rajouter une animation lors du chargement pour les yeux.<br/>
Nous avons donc changer la couleur des yeux avec respectivement bleu pour le laser et rouge pour le feu.

![yeux_anim1](../images/yeux_anim1.png)  ![yeux_anim2](../images/yeux_anim2.png)

#### Mouvement Ailes {#mouvement_ailes}

L'Animation des ailes ce suffit a elle même, elle ce décompose en trois phases:
* déploiment
* rotation
* batement

Le déploiment consiste a augement la taille par un scaling, une fois à la bonne taille les ailes sont vertical.<br/>
Nous faison donc une rotation de 90° pour les rendre horizontal.<br/>
La dernière étape est de la faire le batement d'ailles, nous avons pensé a faire notre propre fonction mais pourquoi faire compliquer quand on peut faire simple.<br/>
Nous utiliserons donc la fonction sinus qui.L'aile doit battre entre -90° et 90°.

$$90 \cdot sin(var)$$

Nous utilisons cette fonction dans la fonction appellé de façon passive par openGL.<br/>
Nous incrémentons var de 0.1 en partant de 0, l'incrément de 0.1 est obtenue de facon empirique.<br/>
de facon plus mathématique il est possible de calculer la période et la frequence du batement.

$$sin(t \cdot T)$$

$$La\ \ période\ \ =\ \ \frac{T}{2\pi}$$

$$La\ \ Fréquence\ \ =\ \ \frac{1}{La\ \ période}\ \ =\ \ \frac{2\pi}{T}$$

![ailes_animation](../images/ailes_animation.png)

#### Camera {#camera}

Les annimations de caméra sont celle demandé par le sujet, c'est a dire:
* rotation autour de l'objet
* zoom avant
* room arrière
