
#include "sun.h"

void sun() {

    GLfloat pos[4] = {0, 0, 0, 1};
	//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_shininess[] = { 50.0 };
	//GLfloat light_position[] = { 0.0, 0.2, 0.2, 1.0 };
	//GLfloat light[] = { .8, 0.0, 1.0, 1 };
	//GLfloat lmodel_ambient[] = { 1, 1, 1, 1.0 };
	//GLfloat mat_emission[] = {0.5, 0.5, 0.0, 1.0};

	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_SMOOTH);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
    //GL_SPOT_CUTOFF

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	//glLightfv(GL_LIGHT0, GL_EMISSION, light);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, light);



	//glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_BLEND);//enable blend
	//glEnable(GL_DEPTH_TEST);//enable depth

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glShadeModel(GL_SMOOTH);



    //glBlendFunc (GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_KICKASS_GLOWING_EFFECT);
    glColor4f(.8,0.0,1.0,1);
    glutSolidSphere(.4,50,50);
}
