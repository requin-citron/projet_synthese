#ifndef LASER_H
#define LASER_H

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

#define LASER_RAYON 0.2
#define LASER_RESOLUTION 20
#define LASER_MAX_SIZE 4

#endif
