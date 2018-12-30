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
static void on_reshape(int width, int height);
static void on_timer(int id);
static void init_lights();
static void on_timer(int id);
void mouse( int x, int y );
void check();
void set_platform();

typedef struct {
    float xP, yP, zP;
}Platform;

Platform whiteP[MAX];
Platform pinkP[MAX];
float animation_parameter,animation_parameter2=0; 
int animation_ongoing;
void platform(float x);
int xPlatform[] = {-5, 0, 5};
float x1=0;
float t=0;
int k=0;
int total1=0,total2=0;
float fall=0;
int ch=0;
float X=0,Z=0;

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 300);
	glutCreateWindow(argv[0]);
	srand(time(NULL));

	glutDisplayFunc(display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
	glutMotionFunc(mouse);
	glClearColor( 0.737255, 0.560784, 0.560784, 0);
	
	
    	glEnable(GL_CULL_FACE);
    	glCullFace(GL_BACK);
	glutMainLoop();
	return 0;
}
/*Fukncija koja nam daje informacije o koordinatama lopte prilikom pomeranja njene pozicije,
ogranicava kretanje loptice po x koordinatama*/
void mouse( int x, int y ){
	x1=(x-300);
	if(x1/50<-7.5)
		x1=-7.5*50;
	if(x1/50>7.5)
		x1=7.5*50;
	if(x1>300)
		x1=300;
	else if(x1<-300)
		x1=-300;
	
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
	check();
	animation_parameter += 0.2;
	animation_parameter2+=0.063;
	k++;
  
	if(ch==1)
    		fall+=0.5;
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
	gluPerspective(30, (float) width / height, 1, 1000);
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
/*Materijal koji odredjuje izgled belih platformi.*/
static void material2()
{
	GLfloat no_material[] = { 0.51643, 0.5, 0.3, 1 };
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

/*Materijal koji odredjuje izgled roze platformi.*/
static void material3()
{
	GLfloat no_material[] = { 0.9, 0.1, 0.3, 1 };
	GLfloat material_ambient[] = { 0.9, 0.1, 0.5, 1 };
	GLfloat material_diffuse[] = { 0.9, 0.2, 0.1, 1 };
	GLfloat material_specular[] = { 0.9, 0, 0, 1 };
	GLfloat shine = 10;
	 
	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_material);
}


/*Postavljanje belih platformi.	*/
void set_platform(){

		int r=rand()%3;
		Platform p;
		p.xP = xPlatform[r];
		p.yP = 0;
		p.zP = -k-3;
		whiteP[total1]=p;
		if(k%60==0)
		{
			X=whiteP[total1].xP;
			Z=whiteP[total1].zP;
		}
		total1++;

		
}

/*Postavljanje roze platformi.*/
void set_platform2(float x, float z){

	Platform p;
	if(x==-5)
		p.xP=5;
	else if(x==5)
		p.xP=-5;
	else
		p.xP=-6;
	p.yP = 0;
	p.zP = z;
	pinkP[total2]=p;
	total2++;
		
}

/*Funkcija koja proverava da li je loptica skocila na platformu.*/
void check(){
	
	if(animation_ongoing && t==0){
		int i;
		
		for(i=0; i<total1; i++){ 
			if((whiteP[i].zP+animation_parameter)>=2.5 && (whiteP[i].zP+animation_parameter)<=8.5){
           		 	if((((x1/50)  > (whiteP[i].xP+2.5)) || ((x1/50)  < (whiteP[i].xP-2.5)))){ 
                			ch=1;
                		}
                	}
   		}
	}
}



static void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 10-fall/10, 30+fall,
		  0, 0, 0,
	    	  0, 1, 0);
	
	init_lights();
	if(k%10==0){
		set_platform();
	}
	
	if(k%60==0){
		set_platform2(X,Z);
	}
	
    	int j;
    	/*Postavljanje belih platformi*/
	for(j=0; j<total1; j++)
	{
		glPushMatrix();
			glTranslatef(0+whiteP[j].xP, -1, (whiteP[j].zP+animation_parameter));
			material2();
			glScalef(1,0.2,1);
			glutSolidCube(5);
  		glPopMatrix();	
  		
	}
	/*Postavljanje roze platformi*/
	for(j=0; j<total2; j++)
	{
		glPushMatrix();
			glTranslatef(0+pinkP[j].xP, -1, (pinkP[j].zP+animation_parameter));
			material3();
			glScalef(1,0.2,1);
			glutSolidCube(5);
  		glPopMatrix();	
  		
	}
	
	glPushMatrix();
       		/*Podesavanje skokova*/
		float bottom=sin(animation_parameter2)*6;
		if(bottom<0){   
			animation_parameter2=0;
			bottom=0;
		}
		glTranslatef(0+x1/50, (bottom-fall), 6);
		/*Podesavanje da posle pada igrica moze opet da se igra priitiskom na 'g' ili 'G'*/
		if(fall>20){
			animation_ongoing=0;
			animation_parameter=0;
			animation_parameter2=0;
			x1=0;
			fall=0;
			total1=0;
			total2=0;
			bottom=0;
			ch=0;
			k=-10;
		}
		t=bottom;
       		glRotatef(animation_parameter*10, 1, 0, 0);
		material();
		glutSolidSphere(1, 22, 22);
    	glPopMatrix();	
	
	glutSwapBuffers();

}
