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
          <li><a href="">Yeux</a></li>
          <li><a href="">Cornes</a></li>
          <li><a href="">Assemblage</a></li>
        </ul>
    </li>
    <li><a href="">Animation</a></li>
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

Nous pouvons maintenant tracer tout ce qu'on veut qui suit une courbe de bézier par example:
![normalize](../images/normalise_exemple1.png)\ \ ![normalize](../images/normalise_exemple2.png)

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
