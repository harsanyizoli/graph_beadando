#include "common.h"
#include "camera.h"
#include "util.h"

const float VIEWPORT_RATIO = 16/9.f;
const float VIEWPORT_ASPECT = 45.f;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

struct Camera cam;
int mouse_x = WINDOW_WIDTH / 2;
int mouse_y = WINDOW_HEIGHT / 2;
struct timespec start;
float last_frame, curr_frame;
float delta_time;

void display()
{   
    curr_frame = get_delta_since_start(start);
    //printf("run time: %f ", curr_frame);
    delta_time = curr_frame - last_frame;
    last_frame = curr_frame;
    //printf("frame time: %f\n", delta_time);
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
		process_key(&cam, FORWARD, delta_time);
        printf("w\n");
		break;
	case 's':
		process_key(&cam, BACKWARD, delta_time);
        printf("s\n");
		break;
	case 'a':
		process_key(&cam, LEFT, delta_time);
		break;
	case 'd':
		process_key(&cam, RIGHT, delta_time);
		break;
	case 27:
		exit(0);
        break;
    case 't':
        break;
	}
}

int changex, changey;
int warped = 1;
void mouse_motion_handler(int x, int y){
	    changex = x - WINDOW_WIDTH/2;
	    changey = WINDOW_HEIGHT/2 - y;
    
        if(changex != 0 || changey != 0){
	        mouse_x = x;
	        mouse_y = y;
	        process_mouse_movement(&cam, changex, changey);
            glutWarpPointer(WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2);
        }
}
void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    float ratio;

    ratio = (float)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((float)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((float)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport (x, y, w, h);
}

void mouse_handler(int button, int state, int x, int y){
    printf("mouse button pressed. %d state: %d", button, state);
}

void initialize()
{   
    clock_gettime(CLOCK_REALTIME, &start);
    init_cam(&cam);
    glutKeyboardFunc(keyboard_handler);
    glutMouseFunc(mouse_handler);
    glutPassiveMotionFunc(mouse_motion_handler);
    glutSetCursor(GLUT_CURSOR_NONE);
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
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 1000.0);
}

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    int window = glutCreateWindow("best gam ever");
    glutSetWindow(window);

    initialize();
    printf("start ns: %d\n", start.tv_nsec);
    glutMainLoop();

    return 0;
}
