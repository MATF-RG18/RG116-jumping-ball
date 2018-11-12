#include<GL/glut.h>

static void display(void);
static void on_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 300);
	glutCreateWindow(argv[0]);
	

	glutDisplayFunc(display);
	glutKeyboardFunc(on_keyboard);
	glClearColor(0.5, 0, 1, 0);
	
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

static void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

}
