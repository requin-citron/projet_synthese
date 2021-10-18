#ifndef LOADJPEG_H
#define LOADJPEG_H

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
#include <string.h>


#include <jpeglib.h>
#include <jerror.h>


void loadJpegImage(char *);

unsigned char *get_texture();

#endif
