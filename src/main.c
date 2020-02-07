#include "common.h"
#include "camera.h"

const float VIEWPORT_RATIO = 16/9.f;
const float VIEWPORT_ASPECT = 45.f;

struct Camera cam;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3d(-0.5, -0.5, 0.0);
    glColor3f(0, 1.0, 0);
    glVertex3d(-0.5, 0.5, 0.0);
    glColor3f(0, 0, 1.0);
    glVertex3d(0.5, 0.5, 0.0);
    glColor3f(1.0, 1.0, 0);
    glVertex3d(0.5, -0.5, 0.0);
    glEnd();
    set_view_point(&cam);
    glutSwapBuffers();
}
void keyboard_handler(unsigned char key, int x, int y){
    switch (key) {
	case 'w':
		process_key(&cam, FORWARD, 0.05f);
        printf("w\n");
		break;
	case 's':
		process_key(&cam, BACKWARD, 0.05f);
        printf("s\n");
		break;
	case 'a':
		process_key(&cam, LEFT, 0.05f);
		break;
	case 'd':
		process_key(&cam, RIGHT, 0.05f);
		break;
	case 27:
		exit(0);
	}
	glutPostRedisplay();
}
void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport (x, y, w, h);
}

void initialize()
{
    init_cam(&cam);
    glutKeyboardFunc(keyboard_handler);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.58, 0.01, 0.9, 1.0);/*
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0.0, -3.0, // eye
        0.0, 0.0, 0.0, // look at
        0.0, 1.0, 0.0  // up
    );*/

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10.0);
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    int window = glutCreateWindow("Square example");
    glutSetWindow(window);

    initialize();

    glutMainLoop();

    return 0;
}
