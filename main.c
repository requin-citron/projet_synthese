/********************************************************/
/*                     cube.cpp                                                 */
/********************************************************/
/*                Affiche a l'ecran un cube en 3D                      */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */
#include "main.h"
#include "spring.h"
#include "head.h"
#include "dragon.h"

char presse;
int anglex,angley,x,y,xold,yold;
double zoom=1;
float animation1=0;
float animation2=0;

float c = (3.-sqrt(5.))/4.;
/* Prototype des fonctions */
void affichage1();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
//! fonction d'acces a l'angle x de la souris
int get_angle_x(){return anglex;}
//! fonction d'acces a l'angle y de la souris
int get_angle_y(){return angley;}
//! fonction d'acces aux zoom
double get_zoom(){return zoom;}
//! fonction d'acces a la variable de l'animation1
float get_animation1(){return animation1;}
//! fonction d'acces a la variable de l'animation2
float get_animation2(){return animation2;}

int main(int argc,char **argv){
  loadJpegImage("./dragon.jpg");
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(1000,1000);
  glutCreateWindow("corp");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */

  glutDisplayFunc(dragon);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}

//!fonction de gestion du clavier
/*!
  gestion des touche pour faire :
  modification de la camera
  modification de la position de la tete
  modification du zoom
*/
void clavier(unsigned char touche,int x,int y){
  //printf("touche : %c\n", touche);
  //printf("zoom: %f\n", zoom);
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
      break;
    case 'l':
        angley+= 4;
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
        break;
    case 'm':
        anglex += 4;
        glutPostRedisplay();
       break;
    case 'k':
        anglex -= 4 ;
        glutPostRedisplay();
        break;
    case 'o':
        angley -= 4;
        glutPostRedisplay();
        break;
    case 'z':
        zoom /= 1.1;
      glutPostRedisplay();
      break;
    case 'w':
        zoom *= 1.1;
      glutPostRedisplay();
      break;
    case 't':
        if(animation1 < 100)animation1 +=1;
        glutPostRedisplay();
        break;
    case 'g':
        if(animation1 > 0)animation1 -= 1;
        glutPostRedisplay();
        break;
    case 'y':
        if(animation2 < 200)animation2 +=1;
        glutPostRedisplay();
        break;
    case 'h':
        if(animation2 > 0)animation2 -= 1;
        glutPostRedisplay();
        break;
    }
}

void reshape(int x,int y){
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}

//! gestion de la souris quand on clic
void mouse(int button, int state,int x,int y){
  //printf("x:%d, y:%d\n", x, y);
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

//! gestion de la souris
void mousemotion(int x,int y){
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      //printf("anglex:%d\nangley:%d\n", anglex, angley);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }
