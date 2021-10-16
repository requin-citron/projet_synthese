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
#include "corp.h"
#include "vector_util.h"

#define HAUTEUR 1.
#define SPINE_NB 4
//si il manque des polygon il faut incrementé la constante
// associer de 1 le pb viens des arondie fais pas les division en c
#define CIRCULAR_RESOLUTION 31.
#define RAYON 0.6
#define RAYON_CYLINDER 0.1
#define PRECISION_CYLINDER 10.
#define QUEUE_INCREMENT 0.005


void show_spring();
void show_body();

#endif
