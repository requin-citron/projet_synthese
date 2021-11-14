#include "oeil.h"

//!genere l'heure
/*!
  \param rayon rayon de l'oeil

  cree une sphere blanche avec un cercle noir pour faire l'oeil
*/
void oeil(float rayon){
    glDisable(GL_TEXTURE_2D);
    point p1, p2;
    point p3, p4;
    float angle1= 0;
    float hauteur=0;
    float hauteur1=0;
    float increment1 = rayon/(OEIL_VERTICAL_RESOLUTION/2.);
    for(size_t d=0; d< ((OEIL_VERTICAL_RESOLUTION/2)); d++){
      p1.x = rayon - (increment1*d);
      hauteur = sqrt(pow(rayon,2) - pow(p1.x,2));
      p1.y =  hauteur;//sqrt(pow(rayon,2) + pow(p1.x,2));
      p1.z = 0;


      p3.x = rayon - (increment1*(d+1));
      hauteur1 = sqrt(pow(rayon,2) - pow(p3.x,2));
      p3.y =  hauteur1;
      p3.z = 0;
      for(size_t i=1; i <(OEIL_CIRCULAR_RESOLUTION+1); i++){
        angle1 = i*(2*M_PI)/OEIL_CIRCULAR_RESOLUTION;
        p2.x =( rayon - (increment1*d))*cos(angle1);
        p2.y = hauteur;//sqrt(pow(rayon,2) - pow(p2.x,2));
        p2.z = (rayon - (increment1*d))*sin(angle1);

        p4.x =( rayon - (increment1*(d+1)))*cos(angle1);
        p4.y = hauteur1;//sqrt(pow(rayon,2) - pow(p2.x,2));
        p4.z = (rayon - (increment1*(d+1)))*sin(angle1);

        //DEBUG
        // glBegin(GL_LINES);
        //   glColor3f(1,1,1); glVertex3f(p1.x, p1.y, p1.z);
        //   glColor3f(1,1,1); glVertex3f(p2.x, p2.y, p2.z);
        // glEnd();
        // glBegin(GL_LINES);
        //   glColor3f(1,0,1); glVertex3f(p1.x, p1.y, p1.z);
        //   glColor3f(1,0,1); glVertex3f(p3.x, p3.y, p3.z);
        // glEnd();
        // glBegin(GL_LINES);
        //   glColor3f(0,1,1); glVertex3f(p2.x, p2.y, p2.z);
        //   glColor3f(0,1,1); glVertex3f(p4.x, p4.y, p4.z);
        // glEnd();
        glBegin(GL_POLYGON);
        //dessin couleurs oeil
        if(d <(OEIL_VERTICAL_RESOLUTION/2)/3 || d > (OEIL_VERTICAL_RESOLUTION/2)/1.2){
          if(get_animation2()<110)glColor3f(1,1,1);
          else{
            if(get_swich_anim()) glColor3f(0,0,1);
            else glColor3f(1,0,0);
          }
        }else{
          glColor3f(0,0,0);
        }
          glVertex3f(p1.x, p1.y, p1.z);
          glVertex3f(p2.x, p2.y, p2.z);
          glVertex3f(p4.x, p4.y, p4.z);
          glVertex3f(p3.x, p3.y, p3.z);
        glEnd();
        glBegin(GL_POLYGON);
          glColor3f(1,1,1); glVertex3f(p3.x, -p3.y, p3.z);
          glColor3f(1,1,1); glVertex3f(p4.x, -p4.y, p4.z);
          glColor3f(1,1,1); glVertex3f(p2.x, -p2.y, p2.z);
          glColor3f(1,1,1); glVertex3f(p1.x, -p1.y, p1.z);
        glEnd();
        p1 = p2;
        p3= p4;
      }
    }
  glEnable(GL_TEXTURE_2D);
}
