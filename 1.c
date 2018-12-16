#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#define TIMER_ID 1
#define TIMER_INTERVAL 8
#define MAX 1000
static void display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void key(int k, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int id);
static void init_lights();
static void on_timer(int id);

float animation_parameter, a=0;
int animation_ongoing, animation_ongoing2=0;
void platforma(float x);
float p=0;
float x_curr=0, y_curr=0;
int n=0;
int xKoordinate[] = {-6, -3, 0, 3, 6};
float x1=0;
int k=0;

int ukupno=0;
float zL=5.9;

typedef struct {
    float xP, yP, zP;
    float lP, dP, nP;
}Platforma;

void postavi_platformu();
Platforma nizP[MAX];

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 300);
	glutCreateWindow(argv[0]);
	

	glutDisplayFunc(display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
    	glutSpecialFunc(key);
	glClearColor( 0.737255, 0.560784, 0.560784, 0);
	
	glEnable(GL_DEPTH_TEST);
    	glEnable(GL_CULL_FACE);
    	glCullFace(GL_BACK);

	
	animation_parameter = -1.5;
	animation_ongoing = 0;
	animation_ongoing=0;
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

    animation_parameter += 0.2;
    k++;
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

static void on_timer2(int id)
{
    if (TIMER_ID != id)
        return;

    a += 0.13;

    glutPostRedisplay();

    if (animation_ongoing2) {
        glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
    }
}



static void key(int k, int x, int y)
{
	
	switch(k){
		case GLUT_KEY_LEFT:
			x1-=0.15;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			x1+=0.15;
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			if (!animation_ongoing2) {
            			animation_ongoing2 = 1;
            			glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            		}
			break;
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
	GLfloat no_material[] = { 1, 1.0, 1.0, 1 };
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
void postavi_platformu(){

	int br = rand()%3+2;
	
	int i;
	for(i=0; i<br; i++){
		Platforma p;
		p.xP = xKoordinate[rand()%5];
		p.yP = 0;
		p.zP = -k-5;
		p.lP = p.xP - 1;
		p.dP = p.xP + 1;
		p.nP = p.zP;
		nizP[ukupno]=p;
		ukupno++;
	}
		
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
	if(k%10==0)
		postavi_platformu();
		
	
    	int j;
	for(j=0; j<ukupno; j++)
	{
		glPushMatrix();
			glTranslatef(0+nizP[j].xP, 0, nizP[j].zP+animation_parameter);
			material();
			material2();
			glColor3f(0, 1, 1);
    		glBegin(GL_POLYGON);
        		glVertex3f(nizP[j].xP, -5, -nizP[j].xP);
        		glVertex3f(nizP[j].xP-6, -5, -nizP[j].xP);
        		glVertex3f(nizP[j].xP-6, -5, -(nizP[j].xP-6));
        		glVertex3f(nizP[j].xP, -5, -(nizP[j].xP-6));
    		glEnd();	
  		glPopMatrix();	
  		
	}
	glPushMatrix();
        	glTranslatef(0+x1, 0, 6);
       		if(a<5)
			glTranslatef(0, a, 0);
		if(a>=5 && 10-a>0)
			glTranslatef(0, 5+5-a, 0);
		else if(a>=5 && animation_ongoing2==1){
			a=0;
			animation_ongoing2=0;
		}
       		glRotatef(animation_parameter*10, 1, 0, 0);
		material();
		glutSolidSphere(1, 22, 22);
    	glPopMatrix();	
	
	glutSwapBuffers();

}
