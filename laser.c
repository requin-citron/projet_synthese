#include "laser.h"

//! crée un cylindre
/*!
  \param rayon rayon du cylindre
  crée un cylindre bleu de rayon du parametre
  la longeur du cylindre dépend de animation2
*/
void draw_laser(float rayon){
  glDisable(GL_TEXTURE_2D);
  float angle_back = 0;
  float angle;
  float size = 0;
  if(get_animation2()>140){
    size = (get_animation2()-140)/60.;
    size *= LASER_MAX_SIZE;
  }
  glColor3f(0,0,1);
  for (size_t i = 1; i < (LASER_RESOLUTION+1); i++) {
    angle = (2*i*M_PI)/(LASER_RESOLUTION);
    glBegin(GL_POLYGON);
      glVertex3f(0, rayon*sin(angle_back), rayon*cos(angle_back));
      glVertex3f(0, rayon*sin(angle), rayon*cos(angle));
      glVertex3f(size, rayon*sin(angle), rayon*cos(angle));
      glVertex3f(size, rayon*sin(angle_back), rayon*cos(angle_back));
    glEnd();
    //rebouchage extremité
    glBegin(GL_POLYGON);
      glVertex3f(size, rayon*sin(angle), rayon*cos(angle));
      glVertex3f(size, 0, 0);
      glVertex3f(size, rayon*sin(angle_back), rayon*cos(angle_back));
    glEnd();
    glBegin(GL_POLYGON);
      glVertex3f(0, rayon*sin(angle), rayon*cos(angle));
      glVertex3f(0, rayon*sin(angle_back), rayon*cos(angle_back));
      glVertex3f(0, 0, 0);
    glEnd();
    angle_back = angle;
  }

  //cercle
  float r;
  float s;
  angle_back = 0;
  for (size_t d = 0; d < NB_CERCLE; d++) {
    for (size_t i = 1; i < (LASER_RESOLUTION+1); i++) {
      angle = (2*i*M_PI)/(LASER_RESOLUTION);
      r = rayon+0.05 + 0.3*rayon*(rand()/(float)RAND_MAX);
      s = (float)size*(rand()/(float)RAND_MAX);
      glBegin(GL_LINES);
      glVertex3f(s, r*sin(angle_back), r*cos(angle_back));
      glVertex3f(s, r*sin(angle), r*cos(angle));
      glEnd();
      angle_back = angle;
    }
  }

  glEnable(GL_TEXTURE_2D);
}
