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
    <li><a href="#lumiere">Lumières</a></li>
  </ol>




### Les Maths {#math}

Nous allons utiliser énormément l'algèbre linéaire pour dessiner le dragon.
Pour cela nous avons créé plusieurs fonctions permettant de faire les choses de base.

Trois structures dans le code sont intéressantes

1. [point](structpoint.html)
2. [vector](structvector.html)
3. [matrix](structmatrix.html)

Les structures de point et vector sont identiques. Cela permet de bien différencier dans les fonctions qui fait quoi.
Le code permet de faire des changements de base de façon transparente.

#### Problèmatique

Dans le cas où on dessine une courbe de bezier ou autre, si l'on veut dessiner un patern, il ne suivra pas le schéma car il sera dans le plan par défaut.

Il faut donc utiliser le vecteur tangent pour dessiner le patern sur le plan décrit par celui-ci.

#### résolution

##### Calcul de la tangente

Avec OpenGL, si nous voulons utiliser des formules parametriques, nous avons besoin de les discrétiser.
Par exemple pour un cercle nous sommes obligés de le transformer en plusieurs segments. Avec beaucoup de segments nous formons un cercle.

Dans notre cas, nous n'avons pas besoin de calculer la dérivée. Notre figure est une suite de segments qui sont par définition la dérivée.

##### Calcul de la base

Maintenant que nous avons le vecteur normal de notre plan il ne nous reste plus qu'à calculer deux vecteurs du plan orthogonaux entre eux.
Pour cela nous allons utiliser le dot product et le cross product.
Pour le premier vecteur il suffit de trouver un vecteur qui crée un dot product entre le vecteur normal et celui-ci.


$$\overrightarrow{\boldsymbol{N}}=\begin{pmatrix} x \\\ y \\\ z \end{pmatrix}$$
$$\overrightarrow{\boldsymbol{N}}\cdot \overrightarrow{\boldsymbol{V1}} = 0$$
$$\boldsymbol{Nx}\cdot\boldsymbol{V1x}+\boldsymbol{Ny}\cdot\boldsymbol{V1y}+\boldsymbol{Nz}\cdot\boldsymbol{V1z}=0$$
$$\boldsymbol{V1x}=\frac{1}{Nx} \ \ \ \ \ \ \ \ \ \ \ \ \boldsymbol{V1x}=\frac{-1}{Ny}\ \ \ \ \ \ \ \ \ \ \ \ \boldsymbol{V1x}=0$$

Nous avons maintenant un vecteur du plan ainsi que le vecteur normal.
$$Calculons\ \ \boldsymbol{V2}\ \ a\ \ l'aide\ \ du\ \ cross\ \ product$$
$$\overrightarrow{\boldsymbol{V2}} = \overrightarrow{\boldsymbol{N}}\wedge\overrightarrow{\boldsymbol{V1}}$$
$$\overrightarrow{\boldsymbol{V2}} = \begin{pmatrix} \boldsymbol{Ny}\cdot\boldsymbol{V1z} - \boldsymbol{Nz}\cdot\boldsymbol{V1y} \\\ \boldsymbol{Nz}\cdot\boldsymbol{V1x} - \boldsymbol{Nx}\cdot\boldsymbol{V1z} \\\ \boldsymbol{Nx}\cdot\boldsymbol{V1y} - \boldsymbol{Ny}\cdot\boldsymbol{V1x} \end{pmatrix}$$
Pour avoir une base homogène nous devons maintenant normaliser nos 3 vecteurs.
C'est à dire que la norme de chaque vecteur soit égale à 1.

![normalize](../images/normalise_exemple.png)

Pour cela nous devons diviser toutes les composantes des vecteurs par leurs normes
$$Malheureusement\ \ nous\ \ avons\ \ besoin\ \ de\ \ calculer\ \ \frac{1}{\sqrt{\|\|\overrightarrow{\boldsymbol{V}\|\|}}}$$
Cette expression est utilisée un **trés trés** grand nombre de fois, mais elle est aussi trés coûteuse
en ressources. Pour cela nous avons utilisé une amélioration qui permet de calculer 1/sqrt(x) de façon **trés** rapide
avec une faible marge d'erreur.

[**Video explicative sur youtube**](https://www.youtube.com/watch?v=p8u_k2LIZyo)

Nous avons maintenant tout ce qu'il faut pour faire une base.
$$B\ =\ \begin{pmatrix} Nx & V1x & V2x \\\ Ny & V1y & V2y \\\ Nz & V1z & V2z \end{pmatrix}$$

Maintenant que nous avons la matrice qui décrit notre base nous pouvons traduire des points de notre base X,Y,Z
dans notre nouvelle base B
$$\begin{pmatrix} P'x \\\ P'y \\\ P'z \end{pmatrix}\ =\ \begin{pmatrix} Nx & V1x & V2x \\\ Ny & V1y & V2y \\\ Nz & V1z & V2z \end{pmatrix}\cdot\begin{pmatrix} Px \\\ Py \\\ Pz \end{pmatrix}$$

Nous pouvons maintenant tracer tout ce qu'on veut qui suit une courbe de Bézier par exemple:<br/>

![normalize](../images/normalise_exemple1.png) ![normalize](../images/normalise_exemple2.png)

Maintenant que nos outils sont prêts nous allons pouvoir commencer la modélisation.

### Modélisation {#modelisation}

#### Le Corps {#corp}

Nous sommes parti sur un dragon en spirale. Nous avons donc commencé par faire une spirale en ligne pour ensuite utiliser les maths vues plus haut pour créer un cylindre qui suit la ligne.

##### La spirale

Pour faire un cercle il suffit d'en décomposer un en petits segments. Puis il ne reste plus qu'à incrémenter la hauteur à chaque itération et faire plusieurs cercles pour obtenir une spirale.

`Toutes les constantes pour jouer avec la spirale sont dans spring.h`

![spirale1](../images/spirale1.png) ![spirale2](../images/spirale2.png)

Ensuite, on peut remplacer la ligne par un cylindre pour obtenir **un corps imparfait**.
Effectivement à cause du changement de base entre chaque cylindre apparait un vide.

![probleme1](../images/probleme1.png)

Nous avons deux façons de résoudre ce problème
##### Solution 1

Nous pouvons reboucher l'écart entre deux sections en créant un autre cylindre.

##### Solution 2

Nous pouvons également relier le nouveau cylindre a l'ancien directement.

##### Solution retenue

Nous avons utilisé les deux solutions. La première permet de donner un aspect avec des cassures (utiliser pour le corps) et la deuxième permet de donner un aspect uniforme.

![spirale3](../images/spirale3.png)       ![head1](../images/head1.png)

En jouant avec les paramètres, il est possible d'obtenir des résultats convenables

![spirale4](../images/spirale4.png)

##### Texture

Pour la peau de dragon nous utiliserons une image trouvée sur google.
Il suffit aprés de l'enrouler autour du cylindre. Pour ça on découpe la texture en largeur en autant de morceaux que d'iteration pour faire le cylindre. Il suffit de coller chaque morceau à chaque face du cylindre.

![dragon](../images/dragon.jpg)       ![spirale5](../images/spirale5.png)

#### La Tête {#head}

Pour la tête, nous avons opté pour une courbe de Bézier qui permet de faire des formes plus "naturelles" ainsi que de pouvoir l'animer facilement.
Nous utiliserons une courbe de Bézier en 4 points

![kig1](../images/kig1.png)

Nous avons implémenté une animation en modifiant les deux premiers points de contrôle de la courbe de Bézier.
Le dragon sera capable de baisser la tête. La transition des deux images ce fait de manière linéaire pour un résultat optimal.

![kig2](../images/kig2.png)

Il ne reste plus qu'à tracer un cylindre de rayon variable.
En utilisant la deuxième technique de rebouchage pour donner un aspect lisse à la tête.
Puis on colle les textures sur la tête comme pour le corps.
Nous avons donc toutes les grosses pièces.

![head2](../images/head2.png)

#### Les Yeux {#yeux}

Nous yeux sont représentés par une sphére. Pour cela nous avons codé notre propre sphére.<br/>
Nous avons expliquer au dessus comment dessiner un cercle.
On peut faire un cône facilement en augmentant la hauteur et en diminuant le rayon.

![chepito](../images/chapito.png)

Maintenant nous voulons une sphère. Pour cela nous allons utiliser Pythagore.<br/>
Nous allons utiliser cette propriétée pour obtenir la hauteur en fonction du rayon.
$$Avec\ \ R\ \ le\ \ Rayon$$
$$sin(\alpha)^2 + cos(\alpha)^2 = 1$$
$$(R\cdot sin(\alpha))^2 + (R\cdot cos(\alpha))^2 = R^2$$
$$Y^2 + X^2 = R^2$$
$$Y = \sqrt{R^2 - X^2}$$

![demi_sphere](../images/demi_sphere.png)

Ils ne reste plus qu'à faire le symétrique.<br/>
Pour la texture, il suffit de mettre en noir un interval de polygone.<br/>
Tout le reste sera en blanc.

![yeux](../images/yeux.png)

#### Les Cornes {#cornes}

Nous voulions partir sur un design type corail ou chandelier.<br/>
Pour cela nous avons utilisé un empilement de pavés droits là encore codé par nos soins.<br/>
Nous sommes partis sur un pavé droit horizontal et deux verticaux

![pavee](../images/corne1.png)

Nous avons opté pour un algorithme récursif qui nous permet de générer un empilement de ce patern.<br/>
L'algorithme va s'executer N fois et à chaque récursion va dessiner le même patern en plus petit au bout des pavés verticaux.

![corne2](../images/corne2.png)

Nous trouvions le resultat trop plat. Nous avons, dans la fonction de création, crée plusieurs paterns comme ci dessus espacés d'un angle.<br/>
Le résultat est assez intéressant et nous avons décidé de le garder.

![corne3](../images/corne3.png)

#### Ailes {#ailes}

Il reste une dernière pièce à notre dragon : les ailes.
Nous voulions partir sur quelque chose de différent pour donner un style sympa à notre dragon.<br/>
Nous avons donc opté pour une réprésentation sans polygone.<br/>
En effet nos ailes ne sont que des lignes blanches qui donnent un style Winx.<br/>

![winx](../images/winx.png)

Pour cela, nous avons fait une conique en 5 points  pour représenter une figure fermée qui se rapproche d'une ellipse sans en être une.<br/>
Nous n' avions que les points. Aprés plusieurs recherches sur internet nous avons trouvé des articles qui expliquaient comment récupérer l'équation à partir de ces 5 points.<br/>
C'était un petit peu trop complexe pour nous et nous avons légerement triché.

![geogebra](../images/geogebra.png)

Nous avons maintenant notre équation paramètre !

$$t \in [0;2\pi]$$
$$X\ \ = \ \ 1.43 - 1.39\cdot cos(t)\ \ +\ \ 0.21\cdot sin(t)$$
$$Y\ \ = \ \ 1.13 -1.08\cdot cos(t)\ \ -\ \ 0.26\cdot sin(t)$$

En faisant varier t nous obtenons notre figure.
De plus nous avons dessiner plusieurs fois la meme figure avec une diminution d'échelle à chaque fois.<br/>
ce qui nous permet de remplir un peu l'aile.

![ailes](../images/ailes1.png)

#### Assemblage {#assemblage}

Maintenant que nous avons tous nos morceaux il faut les assembler.
Pour rappel nous avons:

* Le corps
* La tête
* Les yeux
* Les cornes
* Les ailes

> <span style="color:red"> Translation et Rotation : lequel en premier ?</span><br/>Nous avons empiriquement remarqué que la rotation faisait une rotation locale et non une rotation à partir de l'origine. Cette observation contredit ce que nous avons vu en cours. La translation se fait avec les coordonées du répére local de la pièce. C'est pour cela que nous translatons avant de faire une rotation. Dans le cas inverse le repère local est inversé et donc la translation est bièsé.


##### Tête + Yeux + Cornes

Dans le premier assemblage nous fusionnons les yeux avec la tête et les cornes avec la tête.
La tête ayant comme axe de symetrie l'axe X nous allons nous en servir pour placer juste un oeil et une corne de façon propre. la symétrie fera le reste.<br/>
Nous avons utilisé notre courbe de Bézier ainsi que notre fonction de calcul de rayon en fonction de t (Bézier) pour placer l'oeil. En effet, nous connaissons la position de la courbe de Bézier dans l'espace ainsi que son rayon a cet endroit. Nous n'avons alors plus qu'à translater l'oeil aux coordonées données par la courbe de Bézier en additionant le rayon ainsi qu'un décalage (constante) pour le décaler un peu sur le coté.<br/>
Il suffit de faire la même chose avec juste un décalage négatif pour mettre l'oeil de l'autre coté.<br/>
L'intérêt de positioner l'oeil en fonction de la courbe de Bézier est que lors de l'animation de la tête les yeux suivent parfaitement le mouvement.

Ou utilise le même procédé pour les cornes avec un décalage supérieur sur la courbe de Bézier pour qu'elles soient plus loin que les yeux. De la même manière, les cornes suivent parfaitement le mouvement de la tête.

![head3](../images/head3.png)

##### Tête + Corps
Il faut maintenant raccorder le corps à la tête. C'est la partie la plus subtile car les deux extrémités ne sont pas parfaitement droites.<br/>
Nous aurions pu faire un cylindre droit qui bouche cet espace mais nous ne trouvions ça pas propre. Nous avons donc réutilisé ce que nous avions fait pour le corps et la tête.<br/>
Nous avons récupéré le dernier point ainsi que sa matrice de base du corps et de la tête.<br/>
Il ne nous reste plus qu'à relier les deux morceaux.

![raccord1](../images/raccord1.png) ![raccord2](../images/raccord2.png)

On voit que que tout est parfaitement raccord.

##### Ailes + Corps

Les ailes sont déployables !(cf plus loin). Nous avons voulu faire des paires d'ailes. Nous avons donc mis des mini-ailes deux à deux sur les deux dernières spirales du dragon toutes les 4 sections.<br/>
De base elles sont rétractées donc on ne les voit quasiment pas.

De la même manière nous avons translaté les ailes sur la spirale + le rayon de corps puis nous les avons tourné de manière qu'elles soient orthogonales au vecteur rayon (cela se fait facilement grâce à l'angle permettant de tracer les petits segments d'un cercle).

![ailes2](../images/ailes2.png)

### Animation {#animation}

Il y a deux types d'animations:
* Mouvement de Caméra
* Mouvement du Dragon

Nous avons opté pour un mouvement de tête, des ailes ainsi qu'un jet de laser et de feu.<br/>
Pour la caméra nous pouvons nous rapprocher, nous éloigner et tourner autour du dragon.

#### Mouvement Tête {#mouvement_tete}

Notre tête est basée sur une courbe de Bézier. Il suffit de modifier les coordonées de ces points pour faire bouger la tête.<br/>
Nous avons donc utilisé une variable globale allant de 0 a 100 controlée par le clavier qui permet de progressivement changer les points de la courbe. La tête étant basée dessus, la tête bouge !

#### Feu {#feu}

Notre dragon tire du feu !
Pour modéliser le feu, nous sommes parti sur l'idée d'utiliser un prisme avec un dégradé de rouge.

![fire1](../images/fire1.png)

Il suffit ensuite de créer énormément de prismes de petite tailles(comme des particules).<br/>
Puis de les placer de façon aléatoire dans un cylindre avec des angles aléatoires. Le prisme, avec un angle aléatoire, donne une impression de particules et le placement aléatoire donne une impression de progression.<br/>
Le déplacement des particules est une illusion mais du fait de la nature de l'oeil humain l'impression de jet de feu fonctionne.

![fire2](../images/fire2.png)

Il suffit de donner le rayon de la pointe du nez pour que le rayon du feu soit de bonne taille
et de le translater aux bons endroits (ici on utilise le même principe que pour les yeux et les cornes).

#### Laser {#laser}

Le laser est juste un cylindre bleu mis au même endoit que le feu.<br/>
Nous trouvions notre laser ennuyeux comparé à notre feu pour cela nous avons rajouté des particules.<br/>
Pour cela nous avons dessinné des cercles bleus autour du laser puis nous avons rendu leur rayon et leur décallage du début du laser aléatoire.<br/>
ce qui signifit que tous les segments qui composent un cercle sont décallés donnant une impression de particules.

![laser](../images/laser.png)

#### Animation Corp {#mouvement_corp}

Nous avons décidé de faire une animation de chargement du laser et du feu qui serait visible sur le corps.<br/>
Pour cela, nous avons utilisé les striures entre les cylindres du corps en les faisant changer de couleur de façon progressive.<br/>
On change la couleur des cylindres de façon progressive de la queue à la tête.

![laser_action](../images/laser_action.png)

![feu_action](../images/feu_action.png)

#### Mouvement Cornes {#mouvement_cornes}

De la même manière, nous avons voulu donner une animation aux cornes lors du chargement du laser ou du feu.<br/>
Pour cela nous avons décidé de faire tourner les cornes sur elles même lors du chargement.<br/>

#### Mouvement Yeux {#mouvement_yeux}

De la même manière nous avons décidé de rajouter une animation lors du chargement pour les yeux.<br/>
Nous avons changé la couleur des yeux avec respectivement bleu pour le laser et rouge pour le feu.

![yeux_anim1](../images/yeux_anim1.png)  ![yeux_anim2](../images/yeux_anim2.png)

#### Mouvement Ailes {#mouvement_ailes}

L'animation des ailes se suffit a elle même. Elle se décompose en trois phases:
* déploiement
* rotation
* battement

Le déploiment consiste a augmenter la taille par un scaling. Une fois à la bonne taille, les ailes sont verticales.<br/>
Nous faisons une rotation de 90° pour les rendre horizontales.<br/>
La dernière étape est de faire le battement d'ailes. Nous utiliserons la fonction sinus qui permet d'éviter d'utiliser une fonction linéaire peu esthétique et plus simple qu'une fonction propriétaire. L'aile doit battre entre -90° et +90°.

$$90 \cdot sin(var)$$

Nous utilisons cette fonction dans la fonction appelée de façon passive par openGL.<br/>
Nous incrémentons var de 0.1 (valeur obtenue de facon empirique).<br/>
De facon plus mathématique, il est possible de calculer la période et la fréquence du battement.

$$sin(t \cdot T)$$

$$La\ \ période\ \ =\ \ \frac{T}{2\pi}$$

$$La\ \ Fréquence\ \ =\ \ \frac{1}{La\ \ période}\ \ =\ \ \frac{2\pi}{T}$$

![ailes_animation](../images/ailes_animation.png)

#### Camera {#camera}

Les animations de caméra sont celles demandées par le sujet, c'est à dire:
* rotation autour de l'objet
* zoom avant
* zoom arrière

### Lumières {#lumiere}

Notre choix s'est porté sur une lumière ambiante au centre de la scène ainsi qu'un spot sur le visage du dragon.
Pour se faire, nous avons commencé par déclarer les trois composantes d'une lumière pour pouvoir les créer, c'est à dire: ambient, diffuse et specular.
La lumière ambiante et le spot possédent une position et il y a encore une composante pour le spot pour sa direction.
