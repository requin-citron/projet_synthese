#include "laser.h"

void draw_laser(){
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
      glVertex3f(0, LASER_RAYON*sin(angle_back), LASER_RAYON*cos(angle_back));
      glVertex3f(0, LASER_RAYON*sin(angle), LASER_RAYON*cos(angle));
      glVertex3f(-1*size, LASER_RAYON*sin(angle), LASER_RAYON*cos(angle));
      glVertex3f(-1*size, LASER_RAYON*sin(angle_back), LASER_RAYON*cos(angle_back));
    glEnd();
    //rebouchage extremité
    glBegin(GL_POLYGON);
      glVertex3f(-1*size, LASER_RAYON*sin(angle), LASER_RAYON*cos(angle));
      glVertex3f(-1, 0, 0);
      glVertex3f(-1*size, LASER_RAYON*sin(angle_back), LASER_RAYON*cos(angle_back));
    glEnd();
    angle_back = angle;
  }
  glEnable(GL_TEXTURE_2D);
}
