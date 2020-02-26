#include "model.h"
#include "common.h"
#include "camera.h"
#include "util.h"
#include "draw.h"
#include "world.h"

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
struct World world;
GLuint grass_tex;
GLfloat light_position[] = {1.0f, 1.0f, 0.0f, 0};
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse[] = { 1, 1, 1, 1 };
GLfloat light_specular[] = { 1, 1, 1, 1 };

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
    if(keys_pressed[32] == 1){
        cam.MovementSpeed = 15.0f;
    } else {
        cam.MovementSpeed = 3.0f;
    }
    if(keys_pressed[27] == 1)
        exit(0);
    if(keys_pressed['t'] == 1){
        printf("pressed t\n");
        world.objects[0].rotatex += 2.f;
    }
    if(keys_pressed['z'] == 1){
        printf("pressed z\n");
        world.objects[0].rotatey += 2.f;
    }
    if(keys_pressed['u'] == 1){
        printf("pressed z\n");
        world.objects[0].rotatez += 2.f;
    }
    if(keys_pressed['i'] == 1){
        move_object(&world, 2, 0.0f, 0.0f, 0.05f);
        printf("road height %f\n", world.objects[2].position.z);
    }
    if(keys_pressed['o'] == 1){
        move_object(&world, 2, 0.0f, 0.0f, -0.05f);
        printf("road height %f\n", world.objects[2].position.z);
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

// DISPLAY FUNC
void display()
{   
    //grass plane
    curr_frame = get_delta_since_start(start);
    //printf("run time: %f ", curr_frame);
    delta_time = curr_frame - last_frame;
    last_frame = curr_frame;
    //printf("frame time: %f\n", delta_time);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update();
    set_view_point(&cam);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, light_ambient);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.078f, 0.4f, 0.1647f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glColor3f(0.078f, 0.4f, 0.1647f);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glColor3f(0.078f, 0.4f, 0.1647f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glColor3f(0.078f, 0.4f, 0.1647f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glEnd();
    
    //objs
    for(int i = 0; i < world.num_of_objs ; i++){
        glBindTexture(GL_TEXTURE_2D, world.objects[i].texture);
        draw_obj(&world.objects[i]);
    }
    glutSwapBuffers();
}
/*
-100-100    100-100
    +-------+
    |       |
    |       |
    |       |
    +-------+
-100 100    100 100

*/
void initialize()
{   
    world.num_of_objs = 0;
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
     glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearDepth(1.0);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(0.58, 0.01, 0.9, 1.0);/*
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0.0, -3.0, // eye
        0.0, 0.0, 0.0, // look at
        0.0, 1.0, 0.0  // up
    );*/
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 1000.0);
}


/**
 * Main function
 */
int main(int argc, char* argv[])
{
    char buildings[][64] = {
        ""
    };
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    int window = glutCreateWindow("best gam ever");
    glutSetWindow(window);

    initialize();
    init_world(&world);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    Pixel* grass_image;
    grass_tex = load_texture("assets/grass.png", grass_image);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glEnable(GL_TEXTURE_2D);
    int o = add_obj_with_text(&world, "4Story_Wide_2Doors.obj", "Texture_DarkPurple.png");
    move_object(&world, o, 0.0f, 0.0f, 0.0f);
    world.objects[o].rotatey = 180.0f;
    scale_object(&world, o, 2.0f);
    //printf("%d id of obj\n", o);
    //printf("w->num_of_objs %d\n", world.num_of_objs);
    o = add_obj_with_text(&world, "6Story_Stack.obj", "Texture_Red.png");
    move_object(&world, o, -13.5f, 0.0f, 0.0f);
    world.objects[o].rotatey = 180.0f;
    scale_object(&world, o, 2.0f);
    o = add_obj_with_text(&world, "road.obj", "road.png");
    move_object(&world, o, 0.0f, -1.70f, -6.6f);
    scale_object(&world, o, 0.5f);
    o = add_obj_with_text(&world, "Streetlight_Single.obj", "Texture_Light2.png");
    move_object(&world, o, -2.0f, 0.0f, -11.0f);
    scale_object(&world, o, 3.0f);
    //world.objects[o].rotatey = 180.0f;
    //printf("%d id of obj\n", o);
    //add_obj_with_text(&world, "Street_straight.obj", "");
    //o = add_obj_with_text(&world, "Street_Straight.obj", "Texture_DarkPurple.png");
    //move_object(&world, o, 2.0f, -0.2f, 0.0f);
    //printf("%d num of obj\n", world.num_of_objs);
    //for (int i = 0; i <= world.num_of_objs; i++)
    //{
    //    printf("%d num of obj, name of obj %s", world.num_of_objs, world.objects[world.num_of_objs].name);
    //}
    
    glutMainLoop();

    return 0;
}
