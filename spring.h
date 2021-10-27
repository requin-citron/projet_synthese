#ifndef SPRING_H
#define SPRING_H

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "main.h"
#include "vector_util.h"
#include "loadJpeg.h"
#include "ailes.h"

//! hauteur du corp
#define HAUTEUR 1.
//! nombre de revolution du corp
#define SPINE_NB 4
//si il manque des polygon il faut incrementé la constante
// associer de 1 le pb viens des arondie fais pas les division en c
//! nombre de segment du cercle
#define CIRCULAR_RESOLUTION 32.
//! rayon du corp
#define RAYON 0.6
//! rayon du tube qui suis la spirale
#define RAYON_CYLINDER 0.1
//! nombre de segments du cercle qui permet de gérer le tube
#define PRECISION_CYLINDER 30.
//!increment du rayon du corp jusqu'a RAYON_CYLINDER
/*!
  increment du rayon du corp jusqu'a RAYON_CYLINDER
  qui permet de gérer l'affinement du corp
*/
#define QUEUE_INCREMENT 0.005

void show_spring();

void show_body(point *, matrix *);

#endif
