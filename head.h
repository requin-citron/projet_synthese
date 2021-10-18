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

#define HEAD_BEZIER_PRECISION 80
#define HEAD_CIRCULAR_RESOLUTION 30
#define HEAD_RAYON 0.1
#define HEAD_OFFSET 2


void head(point *, matrix *);


#endif
