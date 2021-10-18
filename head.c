#include "head.h"

bool head_first = true;


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
    *x = coeff1 * (-1.20) + coeff2*(0.55)+coeff3*(-0.71)+ coeff4*(0.70);
    *y = coeff1 * 0.9 + coeff2*0.95+coeff3*(0.20)+ coeff4*(0.10);
}

static float calcule_rayon(float *x){
  //printf("t = %f\n", *x);
  float ret = 0.;
  if(*x<0.03){
    ret = (*x * 30) * (HEAD_RAYON-0.04) ;
  }else if (*x<(0.06)){
    ret = (0.03 * 30)* HEAD_RAYON-0.04;
  }else if(*x < (0.12)){
    ret = (*x * 18)* (HEAD_RAYON-0.02);
  }else if(*x < (0.16)){
    ret = (0.12 * 18) * (HEAD_RAYON-0.02);
  }else if (*x < (0.55)){
    ret = (0.12 * 18) * (HEAD_RAYON) -  ((*x - 0.16) * 3) * (HEAD_RAYON);
  }else{
    ret = HEAD_RAYON;
  }
  return ret;
}

void head(point *p_back, matrix *m){
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


  //texture init
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
    t= ((float)i/HEAD_BEZIER_PRECISION);
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
    rayon = calcule_rayon(&t);
    for(int j=1; j < (HEAD_CIRCULAR_RESOLUTION+1); j++){
      angle1 = (j*2*M_PI)/HEAD_CIRCULAR_RESOLUTION;
      p3 = change_base(0, rayon*sin(angle_back), rayon*cos(angle_back), &base);
      p4 = change_base(0, rayon*sin(angle1), rayon*cos(angle1), &base);
      p5 = change_base(0, rayon_back*sin(angle_back), rayon_back*cos(angle_back), &base_back);
      p6 = change_base(0, rayon_back*sin(angle1), rayon_back*cos(angle1), &base_back);

      //draw cylinder
      glBegin(GL_POLYGON);
          glColor3f(1,1,1);
          glTexCoord2f((j-1)*1.7/HEAD_CIRCULAR_RESOLUTION,0);glVertex3f(p1.x + p6.x, p1.y + p6.y, p1.z + p6.z);
          glTexCoord2f((j)*1.7/HEAD_CIRCULAR_RESOLUTION,0);glVertex3f(p1.x + p5.x, p1.y + p5.y, p1.z + p5.z);
          glTexCoord2f((j)*1.7/HEAD_CIRCULAR_RESOLUTION,0.072);glVertex3f(p2.x + p3.x, p2.y + p3.y, p2.z + p3.z);
          glTexCoord2f((j-1)*1.7/HEAD_CIRCULAR_RESOLUTION,0.072);glVertex3f(p2.x + p4.x, p2.y + p4.y, p2.z + p4.z);
      glEnd();
      angle_back = angle1;
    }
    p1 = p2;
    rayon_back = rayon;
    base_back = base;
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
  *m = base;
  *p_back = p1;
}
