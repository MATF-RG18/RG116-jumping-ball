#include<GL/glut.h>
#include<stdlib.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 8

static void display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int id);
static void init_lights();


float animation_parameter;
int animation_ongoing;


int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
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

	animation_parameter = -1.5;
	animation_ongoing = 0;
	
	glutMainLoop();
	return 0;
}

static void material()
{
    GLfloat no_material[] = { 0, 0, 0, 1 };
	GLfloat material_ambient[] = { 1, 0.5, 0.8, 1 };
	GLfloat material_diffuse[] = { 0.8, 0.1, 0.1, 1 };
	GLfloat material_specular[] = { 1, 1, 1, 1 };
	GLfloat shine = 100;
	 
	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
}

static void on_timer(int id)
{
    if (TIMER_ID != id)
        return;

    animation_parameter += 0.08;

    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
     case 27:
         exit(0);
         break;
     case 'g':
     case 'G':
        if (!animation_ongoing) {
            animation_ongoing = 1;
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        }
        break;
     case 's':
     case 'S':
     	animation_ongoing=0;
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


static void init_lights()
{
    GLfloat light_ambient[] = { 0, 0, 0, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };
	
	
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	glShadeModel(GL_SMOOTH);
}

static void material2()
{
    GLfloat no_material[] = { 1.0, 1.0, 1.0, 1 };
	GLfloat material_ambient[] = { 0.8, 0.9, 0.5, 1 };
	GLfloat material_diffuse[] = { 0.2, 0.6, 0.3, 1 };
	GLfloat material_specular[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat shine = 10;
	 
	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
}	



static void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLfloat light_position[] = { 1, 1, 1, 0 };
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 10, 30,
		  	  0, 0, 0,
	    	  0, 1, 0);
	
	init_lights();
	
		material2();
		glColor3f(0, 1, 1);
    	glBegin(GL_POLYGON);
        	glVertex3f(3, -1, -3);
        	glVertex3f(-3, -1, -3);
        	glVertex3f(-3, -1, 3);
        	glVertex3f(3, -1, 3);
    	glEnd();
    
    
    material2();
		glColor3f(0, 1, 1);
    	glBegin(GL_POLYGON);
        	glVertex3f(10, -1, -10);
        	glVertex3f(4, -1, -10);
        	glVertex3f(4, -1, -4);
        	glVertex3f(10, -1, -4);
    	glEnd();
    
	glPushMatrix();
		glRotatef(animation_parameter * 80, 1, 0, 0);
		material();
		glutSolidSphere(1, 22, 22);
    glPopMatrix();	
	
	glutSwapBuffers();

}
