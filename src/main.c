#include "model.h"
#include "common.h"
#include "camera.h"
#include "util.h"
#include "draw.h"

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
uint8_t keys_pressed[256];
Object weapon;

void update(){
    //
    apply_actions();
}
void keyboard_down_handler(unsigned char key, int x, int y){
   keys_pressed[key] = 1;
}

void keyboard_up_handler(unsigned char key, int x, int y){
    keys_pressed[key] = 0;
}

void apply_actions(){
    if(keys_pressed['w'] == 1)
        process_key(&cam, FORWARD, delta_time);
        
    if(keys_pressed['a'] == 1)
        process_key(&cam, LEFT, delta_time);

    if(keys_pressed['s'] == 1)
        process_key(&cam, BACKWARD, delta_time);

    if(keys_pressed['d'] == 1)
        process_key(&cam, RIGHT, delta_time);

    if(keys_pressed[27] == 1)
        exit(0);
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
void initialize_texture(const char* filename)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	

    int width;
    int height;

    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
            (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

void display()
{   
    curr_frame = get_delta_since_start(start);
    //printf("run time: %f ", curr_frame);
    delta_time = curr_frame - last_frame;
    last_frame = curr_frame;
    //printf("frame time: %f\n", delta_time);
    update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //objs

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0, 0);
    glVertex3d(-0.5, -0.5, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glColor3f(0, 1.0, 0);
    glVertex3d(-0.5, 0.5, 0.0);
    glTexCoord2f(0.0f, 1.0f);
    glColor3f(0, 0, 1.0);
    glVertex3d(0.5, 0.5, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glColor3f(1.0, 1.0, 0);
    glVertex3d(0.5, -0.5, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glEnd();
    set_view_point(&cam);
    glutSwapBuffers();
}

void initialize()
{   
    clock_gettime(CLOCK_REALTIME, &start);
    memset(keys_pressed, 0, 256);
    init_cam(&cam);
    glutKeyboardFunc(keyboard_down_handler);
    glutKeyboardUpFunc(keyboard_up_handler);
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
    initialize_texture("assets/swordtex.png");
    weapon.m = malloc(sizeof(struct Model));
    if (load_model("assets/letstry.obj", weapon.m) == TRUE) {
    	print_model_info(weapon.m);
        weapon.scale = 0.1f;
    }
    else {
        printf("Unable to load the model!\n");
    }

    glutMainLoop();

    return 0;
}
