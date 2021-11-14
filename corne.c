#include "corne.h"


static void draw_cube(float x, float y, float z){
  glColor3f(1,1,1);
  glBegin(GL_POLYGON);
    glTexCoord2f(0,0.0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glTexCoord2f(0.2,0.0);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glTexCoord2f(0.2,4);glVertex3f(-1*(x/2.), -1*(y/2.), -1*(z/2.));
    glTexCoord2f(0,4);glVertex3f(-1*(x/2.), -1*(y/2.), (z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glTexCoord2f(0,0.0);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glTexCoord2f(0.2,0.0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glTexCoord2f(0.2,1);glVertex3f((x/2.), y/2., (z/2.));
    glTexCoord2f(0,1);glVertex3f((x/2.), y/2., -1*(z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glTexCoord2f(0,0.0);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glTexCoord2f(0.2,0.0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glTexCoord2f(0.2,1);glVertex3f((x/2.), y/2., (z/2.));
    glTexCoord2f(0,1);glVertex3f((x/2.), y/2., -1*(z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glTexCoord2f(0,0.0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glTexCoord2f(0.2,0.0);glVertex3f(-1*(x/2.), -1*(y/2.), (z/2.));
    glTexCoord2f(0.2,1);glVertex3f(-1*(x/2.), y/2., (z/2.));
    glTexCoord2f(0,1);glVertex3f((x/2.), y/2., (z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glTexCoord2f(0,0.0);glVertex3f(-1*(x/2.), -1*(y/2.), -1*(z/2.));
    glTexCoord2f(0.2,0.0);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glTexCoord2f(0.2,1);glVertex3f((x/2.), y/2., -1*(z/2.));
    glTexCoord2f(0,1);glVertex3f(-1*(x/2.), y/2., -1*(z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glTexCoord2f(0,0.0);glVertex3f(-1*(x/2.), -1*(y/2.), (z/2.));
    glTexCoord2f(0.2,0.0);glVertex3f(-1*(x/2.), -1*(y/2.), -1*(z/2.));
    glTexCoord2f(0.2,1);glVertex3f(-1*(x/2.), y/2., -1*(z/2.));
    glTexCoord2f(0,1);glVertex3f(-1*(x/2.), y/2., (z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glTexCoord2f(0,0.0);glVertex3f((x/2.), (y/2.), (z/2.));
    glTexCoord2f(0.2,0.0);glVertex3f((x/2.), (y/2.), -1*(z/2.));
    glTexCoord2f(0.2,4);glVertex3f(-1*(x/2.), (y/2.), -1*(z/2.));
    glTexCoord2f(0,4);glVertex3f(-1*(x/2.), (y/2.), (z/2.));
  glEnd();
}

//!fonction recursive pour les cornes
/*!
  \param x[in] centre en x
  \param y[in] centre en y
  \param deep[in] nb de parternes empilés
  \param size_midle[in] taille de la brique initiale horizontale

*/
void draw_corne_as_chevalo(float x,float y, size_t deep, float size_midle){
  if(deep==0) return;
  glPushMatrix();
    //translation en x et y;
    glTranslatef(x,y,0);
    //pave horizontal
    draw_cube(size_midle,0.1,0.1);
    glPushMatrix();
    //translation pour les espacer en x et les faire monter de y
      glTranslatef((size_midle/2.)-0.05,(size_midle/2.)/2 + 0.05,0);
      //pave vertical
      draw_cube(0.1,(size_midle/2),0.1);
    glPopMatrix();
    glPushMatrix();
    //translation pour les espacer en x et les faire monter de y
      glTranslatef(-1*(size_midle/2.)+0.05,(size_midle/2.)/2 + 0.05,0);
      //pave vertical
      draw_cube(0.1,(size_midle/2),0.1);
    glPopMatrix();
  glPopMatrix();
  //on dessine la corne
  draw_corne_as_chevalo(x - (size_midle/2.)+0.05,y +(size_midle/2.) + 0.05*2, deep-1, size_midle/1.3);
  //on dessine la deuxieme corne
  draw_corne_as_chevalo(x + (size_midle/2.)-0.05,y + (size_midle/2.) + 0.05*2, deep-1, size_midle/1.3);
  return;
}

//!dessine une corne avec nb iteraction
/*!
  \param nb[in] nombre d'iterations
  permet de dessiner une corne avec des valeurs hardcoder de la fonction recursive
*/
void draw_corne(size_t nb){
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
         GL_RGB,GL_UNSIGNED_BYTE,get_texture1());
  glEnable(GL_TEXTURE_2D);
  //float deep=3;
  float deep=3;
  float angle = 360/nb;
  for (size_t i = 0; i < nb; i++) {
    glPushMatrix();
      glRotatef(angle*i,0,1,0);
      draw_corne_as_chevalo(0,0,deep,2);
    glPopMatrix();
  }
  glPushMatrix();
    glTranslatef(0,-0.25,0);
    draw_cube(0.1,0.5,0.1);
  glPopMatrix();
}
