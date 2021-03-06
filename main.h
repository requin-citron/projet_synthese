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
#include <time.h>
#include "vector_util.h"

double get_zoom();
int get_angle_y();
int get_angle_x();
float get_animation1();
float get_animation2();
float get_animation3();
bool get_swich_anim();
void anim();
size_t get_angle_magie();
float get_angle_ailes();

#endif
