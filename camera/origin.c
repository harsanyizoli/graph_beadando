#include "camera.h"

#include <GL/glut.h>

#include <stdio.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

#define CAMERA_SPEED 1.0

int mouse_x, mouse_y;

struct Camera camera;

struct Action
{
    int move_forward;
    int move_backward;
    int step_left;
    int step_right;
};

struct Action action;
int time;

void draw_origin()
{
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);

	glEnd();
}

void update_camera_position(struct Camera* camera, double elapsed_time)
{
    double distance;

    distance = elapsed_time * CAMERA_SPEED;

    if (action.move_forward == TRUE) {
		move_camera_forward(camera, distance);
    }

    if (action.move_backward == TRUE) {
		move_camera_backward(camera, distance);
    }

    if (action.step_left == TRUE) {
	    step_camera_left(camera, distance);
    }

    if (action.step_right == TRUE) {
		step_camera_right(camera, distance);
    }
}

double calc_elapsed_time()
{
    int current_time;
    double elapsed_time;
    
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - time) / 1000.0;
    time = current_time;

    return elapsed_time;
}

void display()
{
    double elapsed_time;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    elapsed_time = calc_elapsed_time();
    update_camera_position(&camera, elapsed_time);
	set_view_point(&camera);
    draw_origin();
	glutSwapBuffers();
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}

void mouse_handler(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

void motion_handler(int x, int y)
{
	double horizontal, vertical;

	horizontal = mouse_x - x;
	vertical = mouse_y - y;

	rotate_camera(&camera, horizontal, vertical);

	mouse_x = x;
	mouse_y = y;

    glutPostRedisplay();
}

void key_handler(int key, int x, int y)
{
	switch (key) {
	case 'w':
        action.move_forward = TRUE;
		break;
	case 's':
        action.move_backward = TRUE;
		break;
	case 'a':
        action.step_left = TRUE;
		break;
	case 'd':
        action.step_right = TRUE;
		break;
	}

	glutPostRedisplay();
}

void key_up_handler(int key, int x, int y)
{
	switch (key) {
	case 'w':
        action.move_forward = FALSE;
		break;
	case 's':
        action.move_backward = FALSE;
		break;
	case 'a':
        action.step_left = FALSE;
		break;
	case 'd':
        action.step_right = FALSE;
		break;
	}

	glutPostRedisplay();
}

void idle()
{
    glutPostRedisplay();
}

void initialize()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	int window = glutCreateWindow("GLUT Window");
	glutSetWindow(window);

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key_handler);
    glutKeyboardUpFunc(key_up_handler);
    glutMouseFunc(mouse_handler);
    glutMotionFunc(motion_handler);
    glutIdleFunc(idle);

    init_camera(&camera);

    action.move_forward = FALSE;
    action.move_backward = FALSE;
    action.step_left = FALSE;
    action.step_right = FALSE;

    glutMainLoop();

    return 0;
}

