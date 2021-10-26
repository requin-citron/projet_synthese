#ifndef CORNE_H
#define CORNE_H

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
#include "loadJpeg.h"
#include "main.h"


void draw_corne(size_t);
void draw_corne_as_chevalo(float,float, size_t, float);

#endif
