#include "spring.h"


//!fonction de test pour le corp
/*!
  permet de bien sélectioner les paramétre des header avant de les tester avec tout le body
*/
void show_spring(){
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);

  glLoadIdentity();
  glRotatef(get_angle_y(),1.0,0.0,0.0);
  glRotatef(get_angle_x(),0.0,1.0,0.0);
  float increment = HAUTEUR/SPINE_NB;
  float increment_cercle= increment/CIRCULAR_RESOLUTION;
  matrix base, base_back;
  matrix_zero(&base_back);
  point p1,p2;
  float angle;
  point v1, v2, v1_b, v2_b;
  //cylindre
  float cyl = 0;
  float cyl_next;
  p1.x = 0;
  p1.y = - 0.5;
  p1.z = RAYON;
  for (size_t i = 1; i < (SPINE_NB+1); i++) {
    for (size_t d = 1; d < (CIRCULAR_RESOLUTION+1); d++) {
      angle = (d*(2.*M_PI))/CIRCULAR_RESOLUTION;
      p2.x = RAYON*sin(angle);
      p2.y = p1.y + increment_cercle;
      p2.z = RAYON*cos(angle);
      base = create_base(p1,p2);
      //DEBUG
      // glBegin(GL_LINES);
      //   glColor3f(1.0,0.0,0.0);
      // 	glVertex3f(p1.x, p1.y, p1.z);
      // 	glVertex3f(p2.x, p2.y, p2.z);
      // glEnd();
      //draw cylinder

      for (size_t m = 1; m < (PRECISION_CYLINDER+1); m++) {
        cyl_next = (m*M_PI*2)/PRECISION_CYLINDER;
        v1 = change_base(0,RAYON_CYLINDER*sin(cyl),RAYON_CYLINDER*cos(cyl),&base);
        v2 = change_base(0,RAYON_CYLINDER*sin(cyl_next),RAYON_CYLINDER*cos(cyl_next),&base);
        //rebouchage
        if(!(i==1 && d == 1)){
          v1_b = change_base(0,RAYON_CYLINDER*sin(cyl),RAYON_CYLINDER*cos(cyl),&base_back);
          v2_b = change_base(0,RAYON_CYLINDER*sin(cyl_next),RAYON_CYLINDER*cos(cyl_next),&base_back);
          glBegin(GL_POLYGON);
            glColor3f(0,0,0);glVertex3f(p1.x + v1_b.x, p1.y + v1_b.y, p1.z+ v1_b.z);
            glColor3f(0,0,0);glVertex3f(p1.x + v2_b.x, p1.y + v2_b.y, p1.z+ v2_b.z);
            glColor3f(0,0,0);glVertex3f(p1.x + v2.x, p1.y + v2.y, p1.z+ v2.z);
            glColor3f(0,0,0);glVertex3f(p1.x + v1.x, p1.y + v1.y, p1.z+ v1.z);
          glEnd();
        }
        glBegin(GL_POLYGON);
          glColor3f(1,0,0);glVertex3f(p1.x + v1.x, p1.y + v1.y, p1.z+ v1.z);
          glColor3f(0,1,0);glVertex3f(p1.x + v2.x, p1.y + v2.y, p1.z+ v2.z);
          glColor3f(0,0,1);glVertex3f(p2.x + v2.x, p2.y + v2.y, p2.z+ v2.z);
          glColor3f(0,0,0);glVertex3f(p2.x + v1.x, p2.y + v1.y, p2.z+ v1.z);
        glEnd();
        cyl= cyl_next;
      }
      p1 = p2;
      base_back = base;
    }
  }



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

  glFlush();

  //On echange les buffers
  glutSwapBuffers();
}

//! affiche le corp
/*!
  \param[out] p_back pointeur du point d'extremité du corp
  \param[out] m pointeur de la matrice de changement de base du corp

  affiche le corp et renvois le dernier point avec sa matrice
*/
void show_body(point *p_back, matrix *m){


  float increment = HAUTEUR/SPINE_NB;
  float increment_cercle= increment/CIRCULAR_RESOLUTION;
  matrix base, base_back;
  matrix_zero(&base_back);
  point p1,p2;
  float angle;
  point v1, v2, v1_b, v2_b;
  //cylindre
  float cyl = 0;
  float cyl_next;
  //retressisement
  float rayon = 0;
  float rayon_back=0;

  p1.x = 0;
  p1.y = - 0.5;
  p1.z = RAYON;
  for (size_t i = 1; i < (SPINE_NB+1); i++) {
    for (size_t d = 1; d < (CIRCULAR_RESOLUTION+1); d++) {
      angle = (d*(2.*M_PI))/CIRCULAR_RESOLUTION;
      p2.x = RAYON*sin(angle);
      p2.y = p1.y + increment_cercle;
      p2.z = RAYON*cos(angle);
      base = create_base(p1,p2);
      //DEBUG
      // glBegin(GL_LINES);
      //   glColor3f(1.0,0.0,0.0);
      // 	glVertex3f(p1.x, p1.y, p1.z);
      // 	glVertex3f(p2.x, p2.y, p2.z);
      // glEnd();
      //draw cylinder
      for (size_t m = 1; m < (PRECISION_CYLINDER+1); m++) {
        cyl_next = (m*M_PI*2)/PRECISION_CYLINDER;
        v1 = change_base(0,rayon*sin(cyl),rayon*cos(cyl),&base);
        v2 = change_base(0,rayon*sin(cyl_next),rayon*cos(cyl_next),&base);
        //rebouchage
        if(!(i==1 && d == 1)){
          v1_b = change_base(0,(rayon_back)*sin(cyl),(rayon_back)*cos(cyl),&base_back);
          v2_b = change_base(0,(rayon_back)*sin(cyl_next),(rayon_back)*cos(cyl_next),&base_back);
          //glDisable(GL_TEXTURE_2D);
          glBegin(GL_POLYGON);
            if((CIRCULAR_RESOLUTION+1)*(SPINE_NB+1)*(get_animation2()/100.) > i*(CIRCULAR_RESOLUTION)+d){
              if(get_swich_anim() == true)glColor3f(0,0,1);
              else glColor3f(1,0,0);
            }else{
              glColor3f(40./255., 40./255., 40./255.);
            }
            glVertex3f(p1.x + v1_b.x, p1.y + v1_b.y, p1.z+ v1_b.z);
            glVertex3f(p1.x + v2_b.x, p1.y + v2_b.y, p1.z+ v2_b.z);
            glVertex3f(p1.x + v2.x, p1.y + v2.y, p1.z+ v2.z);
            glVertex3f(p1.x + v1.x, p1.y + v1.y, p1.z+ v1.z);
          glEnd();
          //glEnable(GL_TEXTURE_2D);
        }
        glBegin(GL_POLYGON);
          glColor3f(1.,1.,1);
          //glColor3f(1,0,0);
          glTexCoord2f((m-1)*1.7/PRECISION_CYLINDER,0.0);glVertex3f(p1.x + v1.x, p1.y + v1.y, p1.z+ v1.z);
          //glColor3f(0,1,0);
          glTexCoord2f(m*1.7/PRECISION_CYLINDER,0.0);glVertex3f(p1.x + v2.x, p1.y + v2.y, p1.z+ v2.z);
          //glColor3f(0,0,1);
          glTexCoord2f(m*1.7/PRECISION_CYLINDER,0.5);glVertex3f(p2.x + v2.x, p2.y + v2.y, p2.z+ v2.z);
          //glColor3f(0,0,0);
          glTexCoord2f((m-1)*1.7/PRECISION_CYLINDER,0.5);glVertex3f(p2.x + v1.x, p2.y + v1.y, p2.z+ v1.z);
        glEnd();
        cyl= cyl_next;
      }
      //ailes

      if(i>2 && (d%4) == 0){
        glPushMatrix();
          glTranslatef(p1.x,p1.y,p1.z);
          glRotatef((angle*180.)/M_PI  -90,0,1,0);
          glTranslatef(RAYON_CYLINDER,0,0);
          if(get_animation3() < 100.0){
            glScalef(0.005+get_animation3()/100.,0.005+get_animation3()/100.,0.005+get_animation3()/100.);
          }else{
            glScalef(1,1,1);
            glRotatef(((get_animation3()-100)/100.)*90,1,0,0);
            if(get_animation3() == 200){
              glRotatef(get_angle_ailes(),0,1,0);
            }
          }

          draw_ailes();
        glPopMatrix();
      }
      p1 = p2;
      base_back = base;
      rayon_back = rayon;
      if(rayon<RAYON_CYLINDER){
        rayon += QUEUE_INCREMENT;
      }
    }
  }

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
    *p_back=p1;
    *m = base_back;
}
