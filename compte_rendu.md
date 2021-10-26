## Compte rendu


<!-- TABLE OF CONTENTS -->
  <summary>Sommaire</summary>
  <ol>
    <li>
        <a href="#math">Les Maths</a>
    </li>
    <li>
        <a href="">Modélisation</a>
        <ul>
          <li><a href="">Corps</a></li>
          <li><a href="">Tête</a></li>
          <li><a href="">Yeux</a></li>
          <li><a href="">Cornes</a></li>
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
