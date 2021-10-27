#include "ailes.h"

//!fonction de calcule de l'equation parametrique d'une connique
/*
  \param[in] in t compris entre 0 et 2*PI
  \param[out] x_t pointeur sur un float pour la coord x
  \param[out] y_t pointeur sur un float pour la coord y
  dessine une conique a partir de ca representation paramétrique (merci geogebra)
!*/
static void conique(float t, float *x_t, float *y_t){
  *x_t = 1.43 + (-1.39)*cos(t) + 0.21*sin(t);
  *y_t = 1.13 + (-1.08)*cos(t) + -0.26*sin(t);
  return;
}

void draw_ailes(){
  glDisable(GL_TEXTURE_2D);
  float t;
  float x_t;
  float y_t;
  float x_t_b;
  float y_t_b;
  for (size_t d = 0; d < AILES_OCURRENCES; d++) {
    glPushMatrix();
    glScalef((float)(d)*(1./AILES_OCURRENCES),(float)(d)*(1./AILES_OCURRENCES),(float)(d)*(1./AILES_OCURRENCES));
      conique(0,&x_t_b, &y_t_b);
      for(size_t i=0; i<(AILES_RESOLUTION+2); i++){
        t= (float)i*2.*M_PI/(AILES_RESOLUTION+1.);
        conique(t,&x_t, &y_t);
        glBegin(GL_LINES);
          glColor3f(1,1,1);glVertex3f(x_t_b, y_t_b,0);
          glColor3f(1,1,1);glVertex3f(x_t, y_t,0);
        glEnd();
        x_t_b = x_t;
        y_t_b = y_t;
      }
    glPopMatrix();
  }

  // glBegin(GL_LINES);
  //     glColor3f(1.0,0.0,0.0);
  //   glVertex3f(0, 0,0.0);
  //   glVertex3f(0.3, 0,0.0);
  // glEnd();
  // //axe des y en vert
  // glBegin(GL_LINES);
  //   glColor3f(0.0,1.0,0.0);
  //   glVertex3f(0, 0,0.0);
  //   glVertex3f(0, 0.3,0.0);
  // glEnd();
  // //axe des z en bleu
  // glBegin(GL_LINES);
  //   glColor3f(0.0,0.0,1.0);
  //   glVertex3f(0, 0,0.0);
  //   glVertex3f(0, 0,0.3);
  // glEnd();

  glEnable(GL_TEXTURE_2D);
}
