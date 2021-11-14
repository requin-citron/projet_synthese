#ifndef HEAD_H
#define HEAD_H

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
#include "oeil.h"
#include "corne.h"
//! nombre de segment de la courbe de bezier
#define HEAD_BEZIER_PRECISION 80
//! nombre de segment de chaque cercle
#define HEAD_CIRCULAR_RESOLUTION 30
//! rayon de base de la tete
#define HEAD_RAYON 0.1
//!vitesse d'increment de l'angle des cornes
#define CORNE_RAPIDE 2

void head(point *, matrix *, unsigned char[256][256][3]);
void bezier(float , float *, float *);

#endif
