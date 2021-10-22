#ifndef OEIL_H
#define OEIL_H

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector_util.h"

//! nombre de segment du cercle
#define OEIL_CIRCULAR_RESOLUTION 50
//! nombre de segment vertical de la demi sphere
#define OEIL_VERTICAL_RESOLUTION 50
void oeil(float);
#endif
