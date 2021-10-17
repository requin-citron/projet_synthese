#ifndef CORP_H
#define CORP_H

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "vector_util.h"
#define BEZIER_PRESSISION 60.
#define CIRCULAR_PRESSISION 20.

double get_zoom();
int get_angle_y();
int get_angle_x();

#endif
