### projet synthese d'image

<!-- TABLE OF CONTENTS -->
  <summary>Sommaire</summary>
  <ol>
    <li>
      <a href="#getting-started">Installation</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#utilisation">Utilisation</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
  </ol>

<!-- GETTING STARTED -->
## Installation

Set up du projet

### Installation

1. Install requirement
  `apt install git build-essential`
2. Cloner le repos
  `git clone https://github.com/requin-citron/projet_synthese.git`
3. Initialiser les modules
  `git submodule init`
4. Mettre à jour les modules
  `git submodule update`
5. make
  `make`
6. Générer la doc (Optional)
  `make doc`

> <span style="color:red"> Attention vous avez besoin de doxygen 1.9.2 pour générer la doc</span>


<!-- USAGE EXAMPLES -->
## Utilisation

affiche un dragon avec des animations

| Touche  | Action          |
| :--------------- |:---------------:|
| B  |   Active/Désactive les ailes  |
| Y  | Active/Désactive Laser/Feu             |
| !  | Change le mode de tire Laser/Feu          |
| Z  | Zoom avant          |
| W  | Zoom arrière          |
| M  | Rotation a droite          |
| K  | Rotation a Gauche          |
| O  | Rotation en Haut           |
| L  | Rotation en Bas          |
| T  | Baisser la tête          |
| G  | Monter la tête          |

<!-- ROADMAP -->
## Roadmap

- [x] Création du Corps
- [x] Création de la Tête
- [x] Création des Yeux
- [x] Création Cornes
- [x] Création Animation Tête
- [x] Création Animation Feu
- [x] Création Animation Laser
- [x] Création Animation Corne
- [x] Création Ails
- [x] Création Animation Ails
- [x] Création Lumières
- [x] Possiblement ajout de lumière dans le feu et le laser
