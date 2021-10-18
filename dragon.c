#include "dragon.h"


void dragon(){
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_COLOR_MATERIAL);
  vector cam;
  cam.x = 0;
  cam.y = 0;
  cam.z = -1;
  glLoadIdentity();
  glRotatef(get_angle_y(),1.0,0.0,0.0);
  glRotatef(get_angle_x(),0.0,1.0,0.0);

  //gluLookAt(0.5,0,0,0,0,0.0,0.,0.,0.5);
  gluLookAt(0, 0, 0, cam.x, cam.y,cam.z, 0, 1, 0);
  glRotated(0,0,1,0);
  glRotated(0,0,1,0);

  int LightPos[4] = {0,0,0,1};
  int MatSpec [4] = {1,1,1,1};
  //glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);




  point p_back = show_body();
  glPushMatrix();
  glTranslatef(0.75,0.4,0.6);
  glRotatef(180,0,1,0);
  head(p_back);
  glPopMatrix();


  glFlush();
  //On echange les buffers
  glutSwapBuffers();
}
