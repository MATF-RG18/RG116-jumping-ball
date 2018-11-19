#include<GL/glut.h>
#include<stdlib.h>

static void display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);


int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
    	GLfloat light_ambient[] = { 0, 0, 0, 1 };
    	GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    	GLfloat light_specular[] = { 1, 1, 1, 1 };
    	GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };
	
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 300);
	glutCreateWindow(argv[0]);
	

	glutDisplayFunc(display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
	glClearColor( 0.737255, 0.560784, 0.560784, 0);
	
	
	glEnable(GL_DEPTH_TEST);
    	glEnable(GL_CULL_FACE);
    	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	
	glutMainLoop();
	return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}


static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (float) width / height, 1, 100);
}


static void display(void){
	
	GLfloat light_position[] = { 1, 1, 1, 0 };
	
	GLfloat no_material[] = { 0, 0, 0, 1 };
	GLfloat material_ambient[] = { 0.9, 0.1, 0.9, 1 };
	GLfloat material_diffuse[] = { 0.6, 0.1, 0.1, 1 };
	GLfloat material_specular[] = { 1, 1, 1, 1 };
	GLfloat high_shininess[] = { 100 };
	  
	  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30,
              0, 1, 0,
	    	  0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
	glutSolidSphere(1, 18, 18);
	glPopMatrix();
	
	
	glutSwapBuffers();

}
