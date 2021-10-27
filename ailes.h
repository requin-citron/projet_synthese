#ifndef AILES_H
#define AILES_H

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

#define AILES_RESOLUTION 100
#define AILES_OCURRENCES 15

void draw_ailes();

#endif
