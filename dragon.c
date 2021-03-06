#include "dragon.h"


//! modelisation du dragon
/*!
  on cree le corps
  et la tete on fait une rotation a la tete et une translation
  on inverse l'axe z de sa matrice de changement de base
  puis on fait un cylindre qui relie les deux morceaux
*/
void dragon(){
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_COLOR_MATERIAL);


  /* Parametrage du placage de textures */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  //glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
	//       GL_RGB,GL_UNSIGNED_BYTE,image);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
         GL_RGB,GL_UNSIGNED_BYTE,get_texture());
  glEnable(GL_TEXTURE_2D);


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

  //sun();

  point p1,p2,p3,p4;
  point p1_back;
  matrix m1;
  show_body(&p1_back, &m1);
  point p2_back;
  matrix m2;
  float angle, angle_back;
  float offset= 0;//(get_animation2()/100.)*3*2*M_PI*(RAYON*RAYON);
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
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
         GL_RGB,GL_UNSIGNED_BYTE,get_texture());
  //patch pb de rotation pour la matrice changement de base
  //et surtout on regenere y apres l'inversion de Z
  //car j'ai pass?? 1h en mode WTF ca marche po
  //puis j'ai allum?? mon cerveau et j'ai compris
  // voila donc apr??s avoir modifier un vecteur de la base
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
  //laser
  float x_b;
  float y_b;
  //calcule pas
  bezier(0.03,&x_b, &y_b);
  //lumi??re
  GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat posSpot[] = { 1, 0.4+y_b, 0.6, 1.0 };
  GLfloat dirSpot[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat posLight[] = { 1.0, 0.0, 0.0, 0.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, posLight);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT1, GL_POSITION, posSpot);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, dirSpot);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  if(get_animation2()>140){
    glPushMatrix();
      glTranslatef(0.75+offset-x_b,0.4+y_b,0.6);
      if(get_swich_anim() == true){
        draw_laser((0.03 * 30.0)*HEAD_RAYON-0.04);
      }else{
        draw_fire(800, (0.03 * 30.0)*HEAD_RAYON-0.04);
      }
    glPopMatrix();
      //glEnable(GL_LIGHTING);
      glDisable(GL_LIGHT0);
      glEnable(GL_LIGHT1);
  }else{
    //glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
  }
  glFlush();
  //On echange les buffers
  glutSwapBuffers();
}

void affiche_test(){
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_COLOR_MATERIAL);


  /* Parametrage du placage de textures */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
         GL_RGB,GL_UNSIGNED_BYTE,get_texture());
  glEnable(GL_TEXTURE_2D);
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

  //draw_fire(800, (0.03 * 30.0)*HEAD_RAYON-0.04);
  //draw_laser(0.2);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
         GL_RGB,GL_UNSIGNED_BYTE,get_texture1());
  glEnable(GL_TEXTURE_2D);
  draw_corne(5);
  //draw_ailes();
  //point p2_back;
  //matrix m2;
  //head(&p2_back, &m2);
  //Rep??re
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

  glFlush();
  //On echange les buffers
  glutSwapBuffers();
}
