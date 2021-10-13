/********************************************************/
/*                     cube.cpp                                                 */
/********************************************************/
/*                Affiche a l'ecran un cube en 3D                      */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vector_util.h"
#define BEZIER_PRESSISION 20.

char presse;
int anglex,angley,x,y,xold,yold;

float c = (3.-sqrt(5.))/4.;


/* Prototype des fonctions */
void affichage1();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);




void bezier1(float t, float *x, float *y){
    if(t<0 || t>1){
      fprintf(stderr, "Error: Bezier1 t must be between 0 and 1\n");
      exit(0);
    }
    float coeff1 = pow(1-t, 3);
    float coeff2 = 3.*pow(1-t,2)*t;
    float coeff3 = 3.*pow(1-t,2)*pow(t,2);
    float coeff4 = pow(t,3);
    *x = coeff1 * 0.2 + coeff2*0.3+coeff3*0.51+ coeff4*0.85;
    *y = coeff1 * 0.2 + coeff2*0.0+coeff3*(-0.16)+ coeff4*(-0.16);
}



int main(int argc,char **argv){

  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(500,500);
  glutCreateWindow("corp");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage1);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}


void affichage1(){
  int i,j;
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);

  glLoadIdentity();
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);
  point p1={0,0,0};
  float t;
  point p2={0,0,0};
  float t1;
  matrix_base tmp;
  point test;
  vecteur vect_test;
  //cercle variable
  float z_c;
  float y_c;
  float curr_angle = 0;
  float curr_angle_next;
  bezier1(0.,&(p1.x),&(p1.y));
  for (size_t i = 1; i < (BEZIER_PRESSISION+1.); i++) {
    t1 = (float)i / BEZIER_PRESSISION;
    bezier1(t1,&(p2.x),&(p2.y));
    printf("bezier(%f) = (%f,%f)\n",t,p1.x,p1.y);
    printf("bezier@1(%f) = (%f,%f)\n",t1,p2.x,p2.y);
    tmp = create_base(p1,p2);
    printf("v1=(%f,%f,%f)\n",tmp.v[0].x, tmp.v[0].y, tmp.v[0].z);
    printf("v2=(%f,%f,%f)\n",tmp.v[1].x, tmp.v[1].y, tmp.v[1].z);
    printf("v3=(%f,%f,%f)\n",tmp.v[2].x, tmp.v[2].y, tmp.v[2].z);
    //DEBUG
    glBegin(GL_LINES);
        glColor3f(1.,0,0);
        glVertex3f(p1.x, p1.y,0.0);
        glVertex3f(p2.x, p2.y,0.0);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(1.,0,0);
        glVertex3f(p1.x, p1.y,0.0);
        glVertex3f(p2.x + tmp.v[0].x*0.1, p2.y + tmp.v[0].y*0.1,tmp.v[0].z*0.1);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0,1.,0);
        glVertex3f(p1.x, p1.y,0.);
        glVertex3f(p1.x+tmp.v[1].x*0.1, p1.y+tmp.v[1].y*0.1,tmp.v[1].z*0.1);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.,0,1.);
        glVertex3f(p1.x, p1.y , 0.0);
        glVertex3f(p2.x+ tmp.v[2].x*0.1 , p2.y + tmp.v[2].y*0.1,tmp.v[2].z*0.1);
    glEnd();
    //test
    glBegin(GL_LINES);
        glColor3f(1.,1.,1.);
        vect_test = add_vect(tmp.v[1], tmp.v[2]);

        glVertex3f(p1.x, p1.y , p1.z);
        glVertex3f(p1.x + vect_test.x*0.1, p1.y +vect_test.y*0.1, p1.z + vect_test.z*0.1);
    glEnd();
    curr_angle = 0;
    for (size_t j = 1; j < 11; j++) {
      curr_angle_next = ((float)(j)*2*M_PI)/10.;
      // glBegin(GL_POLYGON);
      //   glColor3f(1,1,1);glVertex3f(x,y+0.2*sin(curr_angle),0.2*cos(curr_angle));
      //   glColor3f(1,1,1);glVertex3f(x,y+0.2*sin(curr_angle_next),0.2*cos(curr_angle_next));
      //   glColor3f(1,1,1);glVertex3f(x1,y1+0.2*sin(curr_angle_next),0.2*cos(curr_angle_next));
      //   glColor3f(1,1,1);glVertex3f(x1,y1+0.2*sin(curr_angle),0.2*cos(curr_angle));
      // glEnd();
      curr_angle = curr_angle_next;
    }
    t=t1;
    p1.x=p2.x;
    p1.y=p2.y;
  }
   // Dessin du cube
  for (i=0;i<6;i++)
    {
      glBegin(GL_POLYGON);
      for (j=0;j<4;j++){
        //glColor3f(1,1,1);
      }
      glEnd();
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

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'a':
      glPolygonMode(GL_FRONT, GL_FILL);
      glPolygonMode(GL_BACK, GL_LINE);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}

void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }
