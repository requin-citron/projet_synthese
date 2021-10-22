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
  glOrtho(get_zoom(), -1*get_zoom(), get_zoom(), -1*get_zoom(), get_zoom(), -1*get_zoom());
  gluLookAt(0, 0, 0, cam.x, cam.y,cam.z, 0, -1, 0);
  glRotated(0,0,1,0);
  glRotated(0,0,1,0);

  //glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);


  point p1,p2,p3,p4;
  point p1_back;
  matrix m1;
  show_body(&p1_back, &m1);
  point p2_back;
  matrix m2;
  float angle, angle_back;
  float offset= (get_animation2()/100.)*3*2*M_PI*(RAYON*RAYON);
  angle_back = 0;
  glPushMatrix();
  glTranslatef(0.75+offset,0.4,0.6);
  glRotatef(180,0,1,0);
  head(&p2_back, &m2);
  glPopMatrix();
  p2_back.x *= -1;
  p2_back.z *= -1;

  //on prend en compte la translation
  p2_back.x += 0.75+offset;
  p2_back.y += 0.4;
  p2_back.z += 0.6;

  //patch pb de rotation pour la matrice cahngement de base
  //et surtout on regénére y aprés l'inversion de Z
  //car j'ai passé 1h en mode WTF ca marche po
  //puis j'ai allumé mon cerveau et j'ai compris
  // voila donc aprés avoir modifier un vecteur de la base
  //on check que ce soit toujours une base en refaisant un produit vectoriel
  //sur les deux vecteur que l'on a sinon ca casse tout
  //et ca me fais rager cf les commit
  inverse_z(&m2);
  for (size_t i = 1; i < (HEAD_CIRCULAR_RESOLUTION+1); i++) {
    angle = (i*2*M_PI)/HEAD_CIRCULAR_RESOLUTION;
    p1 = change_base(0, HEAD_RAYON*sin(angle_back), HEAD_RAYON*cos(angle_back), &m1);
    p2 = change_base(0, HEAD_RAYON*sin(angle), HEAD_RAYON*cos(angle), &m1);
    p3 = change_base(0, HEAD_RAYON*sin(angle_back), HEAD_RAYON*cos(angle_back), &m2);
    p4 = change_base(0, HEAD_RAYON*sin(angle), HEAD_RAYON*cos(angle), &m2);
    glBegin(GL_POLYGON);
      glColor3f(1,1,1);
      glTexCoord2f((i-1)*1.7/HEAD_CIRCULAR_RESOLUTION,0);glVertex3f(p1_back.x + p1.x, p1_back.y + p1.y, p1_back.z +p1.z);
      glTexCoord2f((i)*1.7/HEAD_CIRCULAR_RESOLUTION,0);glVertex3f(p1_back.x + p2.x, p1_back.y + p2.y, p1_back.z + p2.z);
      glTexCoord2f((i)*1.7/HEAD_CIRCULAR_RESOLUTION,0.15+offset*3);glVertex3f(p2_back.x + p4.x, p2_back.y + p4.y, p2_back.z + p4.z);
      glTexCoord2f((i-1)*1.7/HEAD_CIRCULAR_RESOLUTION,0.15+offset*3);glVertex3f(p2_back.x + p3.x, p2_back.y + p3.y, p2_back.z + p3.z);
    glEnd();
    angle_back = angle;

  }

  glFlush();
  //On echange les buffers
  glutSwapBuffers();
}

void tete_magie(){
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
  glOrtho(get_zoom(), -1*get_zoom(), get_zoom(), -1*get_zoom(), get_zoom(), -1*get_zoom());
  gluLookAt(0, 0, 0, cam.x, cam.y,cam.z, 0, -1, 0);
  glRotated(0,0,1,0);
  glRotated(0,0,1,0);
  glEnable(GL_DEPTH_TEST);
  point p2_back;
  matrix m2;
  head(&p2_back, &m2);
  //oeil gauche
  glPushMatrix();
  glTranslatef(-0.60,1,0.12);
  glRotatef(40,1,0,0);
  glRotatef(20,0,1,0);
  glRotatef(20,0,0,1);
  oeil(0.05);
  glPopMatrix();
  //oeil droite
  glPushMatrix();
  glTranslatef(-0.60,1,-0.12);
  glRotatef(-40,1,0,0);
  glRotatef(20,0,1,0);
  glRotatef(20,0,0,1);
  oeil(0.05);
  glPopMatrix();
  glFlush();
  //On echange les buffers
  glutSwapBuffers();
}
