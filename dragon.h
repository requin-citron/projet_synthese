#ifndef DRAGON_H
#define DRAGON_H

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
#include "spring.h"
#include "head.h"
#include "oeil.h"
#include "laser.h"
#include "fire.h"
#include "corne.h"
#include "ailes.h"

void dragon();
void affiche_test();

#endif
