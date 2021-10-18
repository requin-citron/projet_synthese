#include "spring.h"



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
          glColor3f(1.,1.,increment*m);
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



void show_body(point *p_back, matrix *m){
  /* Parametrage du placage de textures */
  unsigned char *texture = get_texture();
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  //glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
	//       GL_RGB,GL_UNSIGNED_BYTE,image);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
	       GL_RGB,GL_UNSIGNED_BYTE,texture);
  glEnable(GL_TEXTURE_2D);





  /* Parametrage du placage de textures */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  //glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
	//       GL_RGB,GL_UNSIGNED_BYTE,image);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
	       GL_RGB,GL_UNSIGNED_BYTE,texture);
  glEnable(GL_TEXTURE_2D);

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
          glBegin(GL_POLYGON);
            glColor3f(40./255., 40./255., 40./255.);glVertex3f(p1.x + v1_b.x, p1.y + v1_b.y, p1.z+ v1_b.z);
            glColor3f(40./255., 40./255., 40./255.);glVertex3f(p1.x + v2_b.x, p1.y + v2_b.y, p1.z+ v2_b.z);
            glColor3f(40.0/255., 40.0/255., 40/255.);glVertex3f(p1.x + v2.x, p1.y + v2.y, p1.z+ v2.z);
            glColor3f(40.0/255., 40.0/255., 40/255.);glVertex3f(p1.x + v1.x, p1.y + v1.y, p1.z+ v1.z);
          glEnd();
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

void Draw(){
  /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    // glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    // glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
    // glMatrixMode(GL_MODELVIEW);
    // glEnable(GL_COLOR_MATERIAL);
    //
    // glLoadIdentity();
    // glRotatef(get_angle_y(),1.0,0.0,0.0);
    // glRotatef(get_angle_x(),0.0,1.0,0.0);
    //
    // gluLookAt(0.5,0,0,0,0,0.0,0.,0.,0.5);
    // glRotated(a,0,1,0);
    // glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    // glRotated(-a,0,1,0);
    // glColor3f(1,0,1);glutSolidSphere(0.4,50,50);
    // a=+1;
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_DEPTH_TEST);


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
