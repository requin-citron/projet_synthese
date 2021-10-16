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
#include "corp.h"
#include "vector_util.h"

#define HEAD_BEZIER_PRECISION 50
#define HEAD_CIRCULAR_RESOLUTION 10
#define HEAD_CYLINDER_RESOLUTION 10
#define HEAD_RAYON 0.05
#define HEAD_OFFSET 2


void affichage2();

static void bezier(float , float *, float *);
static float calcule_rayon(float *);

#endif
