#include "head.h"



static void bezier(float t, float *x, float *y){
    if(t<0 || t>1){
      fprintf(stderr, "Error: Bezier1 t must be between 0 and 1\n");
      exit(0);
    }
    float multi  = 1;
    float coeff1 = pow(1-t, 3)/multi;
    float coeff2 = 3.*pow(1-t,2)*t/multi;
    float coeff3 = 3.*pow(1-t,2)*pow(t,2)/multi;
    float coeff4 = pow(t,3)/multi;
    *x = coeff1 * (-1.20+0.4) + coeff2*(0.55+0.4)+coeff3*(-0.71+0.4)+ coeff4*(0.70+0.4);
    *y = coeff1 * 0.9 + coeff2*0.95+coeff3*(0.20)+ coeff4*(0.10);
}

static float calcule_rayon(float *x){

}

void affichage2(){
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  float t;
  float angle_back, angle1;
  point p1, p2, p3, p4,p5, p6;
  float x,y;
  matrix base, base_back;
  float rayon, rayon_back;
  rayon_back = 0;
  bool first_time = true;
  //init
  bezier(0,&x,&y);
  p1.x = x;
  p1.y = y;
  p1.z = 0;
  for (size_t i = 1; i < (HEAD_BEZIER_PRECISION+1); i++) {
    t=(float)i/HEAD_BEZIER_PRECISION;
    bezier(t, &x, &y);
    p2.x = x;
    p2.y = y;
    p2.z = 0;

    //draw line
    glBegin(GL_LINES);
      glColor3f(1,0,0); glVertex3f(p1.x, p1.y, p1.z);
      glColor3f(1,0,0); glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
    //draw cercle
    base = create_base(p2, p1);
    if(first_time == true){
      first_time = false;
      base_back =base;
    }
    angle_back = 0;
    // ici on gère le rayon de la tete
    rayon = rayon_back + 0.01;
    if(rayon > HEAD_RAYON) rayon = HEAD_RAYON;
    for(int j=1; j < (HEAD_CIRCULAR_RESOLUTION+1); j++){
      angle1 = (j*2*M_PI)/HEAD_CIRCULAR_RESOLUTION;
      p3 = change_base(0, rayon*sin(angle_back), rayon*cos(angle_back), &base);
      p4 = change_base(0, rayon*sin(angle1), rayon*cos(angle1), &base);
      p5 = change_base(0, rayon_back*sin(angle_back), rayon_back*cos(angle_back), &base_back);
      p6 = change_base(0, rayon_back*sin(angle1), rayon_back*cos(angle1), &base_back);

      //draw cylinder
      glBegin(GL_POLYGON);
          glColor3f(0,0,1); glVertex3f(p1.x + p5.x, p1.y + p5.y, p1.z + p5.z);
          glColor3f(0,1,0); glVertex3f(p1.x + p6.x, p1.y + p6.y, p1.z + p6.z);
          glColor3f(1,0,0); glVertex3f(p2.x + p4.x, p2.y + p4.y, p2.z + p4.z);
          glColor3f(1,1,0); glVertex3f(p2.x + p3.x, p2.y + p3.y, p2.z + p3.z);
      glEnd();
      angle_back = angle1;
      glEnd();
    }
    p1 = p2;
    rayon_back = rayon;
    base_back = base;
  }

  glLoadIdentity();
  glRotatef(get_angle_y(),1.0,0.0,0.0);
  glRotatef(get_angle_x(),0.0,1.0,0.0);
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
