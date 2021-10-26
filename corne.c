#include "corne.h"


static void draw_cube(float x, float y, float z){
  glBegin(GL_POLYGON);
    glColor3f(1,0,0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glColor3f(0,0,1);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glColor3f(0,1,0);glVertex3f(-1*(x/2.), -1*(y/2.), -1*(z/2.));
    glColor3f(1,1,1);glVertex3f(-1*(x/2.), -1*(y/2.), (z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glColor3f(0,0,1);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glColor3f(1,0,0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glColor3f(1,0,0);glVertex3f((x/2.), y/2., (z/2.));
    glColor3f(0,0,1);glVertex3f((x/2.), y/2., -1*(z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glColor3f(0,0,1);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glColor3f(1,0,0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glColor3f(1,0,0);glVertex3f((x/2.), y/2., (z/2.));
    glColor3f(0,0,1);glVertex3f((x/2.), y/2., -1*(z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glColor3f(1,0,0);glVertex3f((x/2.), -1*(y/2.), (z/2.));
    glColor3f(0,0,1);glVertex3f(-1*(x/2.), -1*(y/2.), (z/2.));
    glColor3f(0,0,1);glVertex3f(-1*(x/2.), y/2., (z/2.));
    glColor3f(1,0,0);glVertex3f((x/2.), y/2., (z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glColor3f(0,0,1);glVertex3f(-1*(x/2.), -1*(y/2.), -1*(z/2.));
    glColor3f(1,0,0);glVertex3f((x/2.), -1*(y/2.), -1*(z/2.));
    glColor3f(1,0,0);glVertex3f((x/2.), y/2., -1*(z/2.));
    glColor3f(0,0,1);glVertex3f(-1*(x/2.), y/2., -1*(z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glColor3f(0,0,1);glVertex3f(-1*(x/2.), -1*(y/2.), (z/2.));
    glColor3f(1,0,0);glVertex3f(-1*(x/2.), -1*(y/2.), -1*(z/2.));
    glColor3f(1,0,0);glVertex3f(-1*(x/2.), y/2., -1*(z/2.));
    glColor3f(0,0,1);glVertex3f(-1*(x/2.), y/2., (z/2.));
  glEnd();
  glBegin(GL_POLYGON);
    glColor3f(1,0,0);glVertex3f((x/2.), (y/2.), (z/2.));
    glColor3f(0,0,1);glVertex3f((x/2.), (y/2.), -1*(z/2.));
    glColor3f(0,1,0);glVertex3f(-1*(x/2.), (y/2.), -1*(z/2.));
    glColor3f(1,1,1);glVertex3f(-1*(x/2.), (y/2.), (z/2.));
  glEnd();
}

static void draw_corne_as_chevalo(float x,float y, size_t prof, float size_midle){
  if(prof==0) return;
  glPushMatrix();
    //glScalef(size,size,size);
    glTranslatef(x,y,0);
    draw_cube(size_midle,0.1,0.1);
    glPushMatrix();
      glTranslatef((size_midle/2.)-0.05,(size_midle/2.)/2 + 0.05,0);
      draw_cube(0.1,(size_midle/2.),0.1);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-1*(size_midle/2.)+0.05,(size_midle/2.)/2 + 0.05,0);
      draw_cube(0.1,(size_midle/2.),0.1);
    glPopMatrix();
  glPopMatrix();
  draw_corne_as_chevalo(x - (size_midle/2.)+0.05,y +(size_midle/2.) + 0.05*2, prof-1, size_midle/1.5);
  draw_corne_as_chevalo(x + (size_midle/2.)-0.05,y + (size_midle/2.) + 0.05*2, prof-1, size_midle/1.5);
  return;
}

void draw_corne(){
  /* effacement de l'image avec la couleur de fond */
  unsigned char *texture = get_texture();


  /* Parametrage du placage de textures */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  //glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
  //       GL_RGB,GL_UNSIGNED_BYTE,image);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
         GL_RGB,GL_UNSIGNED_BYTE,texture);
  glEnable(GL_TEXTURE_2D);


  draw_corne_as_chevalo(0,0,10,2);

  // glPushMatrix();
  //     glTranslatef(0.5,0.6/2 + 0.05 +2*0.1,0);
  //     draw_cube(0.6,0.1,0.1);
  //     glPushMatrix();
  //       glTranslatef(0.3-0.05,0.3/2 + 0.05,0);
  //       draw_cube(0.1,0.3,0.1);
  //     glPopMatrix();
  //     glPushMatrix();
  //       glTranslatef(-0.3+0.05,0.3/2 + 0.05,0);
  //       draw_cube(0.1,0.3,0.1);
  //     glPopMatrix();
  // glPopMatrix();
  //
  //
  // glPushMatrix();
  //     glTranslatef(-0.5,0.5,0);
  //     draw_cube(0.6,0.1,0.1);
  //     glPushMatrix();
  //       glTranslatef(0.3-0.05,0.3/2 + 0.05,0);
  //       draw_cube(0.1,0.3,0.1);
  //     glPopMatrix();
  //     glPushMatrix();
  //       glTranslatef(-0.3+0.05,0.3/2 + 0.05,0);
  //       draw_cube(0.1,0.3,0.1);
  //     glPopMatrix();
  // glPopMatrix();



  //Repère
  //axe x en rouge
  glBegin(GL_LINES);
      glColor3f(1.0,0.0,0.0);
    glVertex3f(0, 0,0.0);
    glVertex3f(1, 0,0.0);
  glEnd();
  //axe des y en vert
  glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0, 0,0.0);
    glVertex3f(0, 1,0.0);
  glEnd();
  //axe des z en bleu
  glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0, 0,0.0);
    glVertex3f(0, 0,1.0);
  glEnd();
}
