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
float animation3=0;
bool switch_anim = true;
size_t angle_magie = 0;
bool switch_laser_fire = false;
float angle_ailes = 0;
float angle_ailes_base=0.;
bool switch_ailes=true;

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
//! fonction d'acces a la variable de l'animation3
float get_animation3(){return animation3;}
//! fonction pour le changement feu laser
bool get_swich_anim(){return switch_anim;}
//! fonction pour la rotation des cornes
size_t get_angle_magie(){return angle_magie;}
//! fonction pour la rotation des ailes
float get_angle_ailes(){return angle_ailes;}

int main(int argc,char **argv){
  srand(time(NULL));
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
  glutIdleFunc(anim);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}
//!fonction appellé quand il ne ce passe rien
void anim(){
  angle_magie = (angle_magie +CORNE_RAPIDE) %360;
  if(switch_laser_fire==true){
    if(animation2<200) animation2 += 0.5;
  }else{
    if(animation2>0) animation2 -= 0.5;
  }
  //switch_ailes
  if(switch_ailes==true){
    if(animation3 <200)animation3+=1;
  }else{
    if(animation3>0)animation3-=1;
  }
  // si les ailes sont déployé elle fonts fap fap
  if(get_animation3() == 200){
    angle_ailes = sin(angle_ailes_base)*90.;
    angle_ailes_base+=0.1;
  }
  glutPostRedisplay();
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
        if(switch_laser_fire == true)switch_laser_fire = false;
        else switch_laser_fire = true;
        glutPostRedisplay();
        break;
    case 'b':
        if(switch_ailes == true) switch_ailes=false;
        else switch_ailes = true;
        glutPostRedisplay();
        break;
    case '!':
        if(switch_anim == true){
          switch_anim = false;
        }else{
          switch_anim = true;
        }
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
