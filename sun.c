// ssh-add ~/.ssh/github
#include "sun.h"
/*
void printSphere(GLfloat* pos) {
    glPushMatrix();
        glColor4f(0.8,0.0,1.0,1);
        glTranslatef(pos[0],pos[1],pos[2]);
        glutSolidSphere(0.02,50,50);
    glPopMatrix();
}

void printSquare(GLfloat* mid, GLfloat s) {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(2.0, 4.0, 0.0);
        glVertex3f(8.0, 4.0, 0.0);
        glVertex3f(8.0, 6.0, 0.0);
        glVertex3f(2.0, 6.0, 0.0);
    glEnd();
}*/

void sun() {
    glColor4f(0.0,0.1,1.0,1);
    glutSolidCube(0.5);

    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 0.0, .0, 1.0, 1.0 };
    GLfloat specular[] = { 0.0, .0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

    GLfloat posLight[] = { 1.0, 0.0, 0.0, 0.0 };
    GLfloat posSpot[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat dirSpot[] = { 1.0, 1.0, 1.0, 1.0 };

    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, posLight);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, posSpot);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, dirSpot);


/*_light_position[0] =  0.0;
_light_position[1] = 1.0;
_light_position[2] = 0.0;
_light_position[3] = 0.0;

_spotlight_position[0] = 0.0;
_spotlight_position[1] = -1.0;
_spotlight_position[2] = 0.0;*/





    //GLfloat pos[4] = {0, 0, 0, 1};

    //glPushMatrix();
    //GLfloat sun[4] = {.7,0.4,1.0,1};
    //glEnable(GL_LIGHTING);
    //glShadeModel(GL_SMOOTH);
    //glMaterialfv(GL_FRONT, GL_EMISSION, sun);
    //glutSolidSphere(0.4,50,50);
    //glPopMatrix();
    //sun[0] = 1;
    //sun[1] = 1;
    //sun[2] = 1;
    //glMaterialfv(GL_FRONT, GL_EMISSION, sun);
    //glDisable(GL_LIGHTING);
    /*GLfloat pos[3] = {0, 0, 0};
    GLfloat poss[6][4] = {{1,0,0,1},{0,1,0,1},{0,0,1,1},
        {-1,0,0,1},{0,-1, 0,1},{0, 0,-1,1}};
        float Light1Dif[4] = {1.0f, 0.2f, 0.2f, 1.0f};
    float Light1Spec[4] = {1.0f, 0.2f, 0.2f, 1.0f};
    float Light1Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    float MatSpec[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float MatDif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float MatAmb[4] = {0.3f, 0.3f, 0.3f, 1.0f};
    for (int t=0; t<6; t++)
        printSphere(poss[t]);

    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmb);
    glEnable(GL_LIGHTING);
    for (int t=0; t<3; t++){
       glLightfv(GL_LIGHT0+t, GL_POSITION, poss[t]);
       glLightfv(GL_LIGHT0+t, GL_DIFFUSE, Light1Dif);
       glLightfv(GL_LIGHT0+t, GL_SPECULAR, Light1Spec);
       glLightfv(GL_LIGHT0+t, GL_AMBIENT, Light1Amb);
       glLightfv(GL_LIGHT0+t, GL_SPOT_DIRECTION, pos);
       glLightf(GL_LIGHT0+t, GL_SPOT_EXPONENT, 3);
       glLightf(GL_LIGHT0+t, GL_SPOT_CUTOFF, 30);
   	   glEnable(GL_LIGHT0+t);
   }*/



    //GLfloat pos[4] = {0., 1, 1, 1};
    //GLfloat posPost[3] = {2, 2, 2};

	//glLightfv(GL_LIGHT0, GL_POSITION, pos);
    //glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, posPost);
    //


}
