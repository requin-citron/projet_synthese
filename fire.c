#include "fire.h"

static void create_particule(float size){
  glPushMatrix();
  glScalef(size,size,size);
  //base
  glBegin(GL_POLYGON);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(0.5,0,-0.5);
    glColor3f(245./255., 184./255., 28./255.);glVertex3f(-0.5,0,-0.5);
    glColor3f(199./255., 24./255., 113./255.);glVertex3f(-0.5,0,0.5);
    glColor3f(215./255., 181./255., 34./255.);glVertex3f(0.5,0,0.5);
  glEnd();
  //face 1
  glBegin(GL_TRIANGLES);
    glColor3f(245./255., 184./255., 28./255.);glVertex3f(0,0.8,0);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(0.5,0,0.5);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(-0.5,0,0.5);
  glEnd();
  //face 2
  glBegin(GL_TRIANGLES);
    glColor3f(245./255., 184./255., 28./255.);glVertex3f(0,0.8,0);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(-0.5,0,-0.5);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(0.5,0,-0.5);
  glEnd();
  //face 3
  glBegin(GL_TRIANGLES);
    glColor3f(245./255., 184./255., 28./255.);glVertex3f(0,0.8,0);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(-0.5,0,0.5);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(-0.5,0,-0.5);
  glEnd();
  //face 4
  glBegin(GL_TRIANGLES);
    glColor3f(245./255., 184./255., 28./255.);glVertex3f(0,0.8,0);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(0.5,0,-0.5);
    glColor3f(199./255., 49./255., 29./255.);glVertex3f(0.5,0,0.5);
  glEnd();
  glPopMatrix();
}

void draw_fire(size_t nb, float r){
  float angle_1;
  float rayon;
  float length;
  float angle_2;
  float angle_3;
  float angle_4;
  float len;
  if(get_animation2()>140){
    len = (get_animation2()-140)/60.;
    len *= FIRE_MAX_SIZE;
  }
  for (size_t i = 0; i < nb; i++) {
    angle_1 = (2.0*M_PI)*(rand()/(float)RAND_MAX);
    angle_2 = 360*(rand()/(float)RAND_MAX);
    angle_3 = 360*(rand()/(float)RAND_MAX);
    angle_4 = 360*(rand()/(float)RAND_MAX);
    rayon = r*(rand()/(float)RAND_MAX);
    length = len*(rand()/(float)RAND_MAX);
    glPushMatrix();
    glTranslatef(length, rayon*cos(angle_1), rayon*sin(angle_1));
    glRotatef(angle_2, 1,0,0);
    glRotatef(angle_3, 0,1,0);
    glRotatef(angle_4, 0,0,1);
    create_particule(0.01);
    glPopMatrix();
  }
}
