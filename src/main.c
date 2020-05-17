#include "common.h"

const float VIEWPORT_RATIO = 16/9.f;
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

struct Camera cam;
struct timespec start;
struct World world;
struct Help help;
uint8_t keys_pressed[256];
float last_frame, curr_frame, delta_time;

void initialize();
void update(float dt);
void specialFunc(int key, int x, int y);
void idle();
void update(float dt){
    world.car->car_pos = add_vec3f(cam.Position, mult_vec3f(cam.Front, 2.0f));
    vec3f pp = {world.car->car_pos.x, 0.0f, world.car->car_pos.z};
    vec3f dif = sub_vec3f(world.ball->ball_pos, pp);
    float len = sqrtf(dif.x * dif.x + dif.y * dif.y + dif.z * dif.z);
    if(len < 2 && world.ball->nohit == 0){
        vec3f camxz = {cam.Front.x * cam.MovementSpeed*3.f, 10.0f, cam.Front.z * cam.MovementSpeed *3.f};
        world.ball->add = add_vec3f(world.ball->add, camxz);
        world.ball->nohit = 1;
    } else if (len > 2){
        world.ball->nohit = 0;
    }
    world.ball->add.y -= 10.0f * dt;
    world.ball->ball_pos = add_vec3f(world.ball->ball_pos, mult_vec3f(world.ball->add, dt));
    world.ball->add = sub_vec3f(world.ball->add, mult_vec3f(world.ball->add, dt));
    //ball_pos.y -= 10.f * dt;
    if(world.ball->ball_pos.y < 1) { 
        world.ball->add.y = -world.ball->add.y;
        world.ball->ball_pos.y = 1.0f;
    }
    if(abs(world.ball->ball_pos.x) > 19.f) world.ball->add.x = -world.ball->add.x;
    if(abs(world.ball->ball_pos.z) > 19.f) world.ball->add.z = -world.ball->add.z;

}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);     
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    int window = glutCreateWindow("game.exe");
    glutSetWindow(window);

    init_world(&world);
    init_help(&help);
    initialize();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    //scale_model(&m_car, 0.5f, 0.5f, 0.5f);
    glutMainLoop();
    return 0;
}

void keyboard_down_handler(unsigned char key, int x, int y){
   // printf("%d key pressed\n", key);
   keys_pressed[key] = 1;
}

void keyboard_up_handler(unsigned char key, int x, int y){
    keys_pressed[key] = 0;
}

void mouse_handler(int button, int state, int x, int y){
    printf("mouse button pressed. %d state: %d", button, state);
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
        if (world.light->ambient < 1)
			world.light->ambient += 0.01;
    }
    if(keys_pressed['y'] == 1){
       if (world.light->ambient > -0.51)
			world.light->ambient -= 0.01;
    }
        /*
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
    }*/
}
int changex, changey;
int warped = 1;
void mouse_motion_handler(int x, int y){
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

void display()
{   
    if(help.on == 1){
        draw_help();
    } else {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.f, VIEWPORT_RATIO, 0.01, 1000.0);
    curr_frame = get_delta_since_start(start);
    //printf("run time: %f ", curr_frame);
    delta_time = curr_frame - last_frame;
    last_frame = curr_frame;
    //printf("ball %f %f %f\nplayer%f %f %f", ball_pos.x, ball_pos.y, ball_pos.z, player_pos.x, player_pos.y, player_pos.z);
    update(delta_time);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    set_view_point(&cam);
    apply_actions();
    GLUquadric* a = gluNewQuadric();
    GLfloat ambient[4] = {world.light->ambient, world.light->ambient, world.light->ambient, world.light->ambient};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ambient);
    GLfloat lightPos0[] = {5.0f, 1.0f, 5.0f, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
    glEnable(GL_LIGHT1);
    /*
    //Light
    GLfloat lightColor0[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    
    //Material
    GLfloat mcolor[] = {0.8, 0.1, 0.8, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mcolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
    */
    //printf("frame time: %f\n", delta_time);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, world.floor->floor_tex);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 20.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.05f, 0.2f);
    glVertex3f(-20.0f, 0.0f, 20.0f);

    glTexCoord2f(0.f, 0.f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.05f, 0.2f);
    glVertex3f(-20.0f, 0.0f, -20.0f);
 
    glTexCoord2f(20.f, 20.f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.05f, 0.2f);
    glVertex3f(20.0f, 0.0f, -20.0f);

    glTexCoord2f(20.0f, 0.f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.05f, 0.2f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    //
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);

    //glVertex3f(0.f, 0.f, 0.0f);
    //glVertex3f(0.f, 2.f, 0.0f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(world.ball->ball_pos.x, world.ball->ball_pos.y, world.ball->ball_pos.z);
    glRotatef(cosf(curr_frame), 1.0f, 3.0f, -2.0f);
    gluQuadricDrawStyle(a, GLU_FILL);
    gluQuadricNormals(a, GLU_SMOOTH);
    gluQuadricTexture(a, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, world.ball->ball_tex);
    glEnable(GL_TEXTURE_2D);
    gluSphere(a, 1.0, 16.0, 16.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //render ground
    glPushMatrix();
    glPopMatrix();
        glTranslatef(world.car->car_pos.x, 0.0f, world.car->car_pos.z);
        glRotatef(-1*cam.Yaw-90.f, 0.0f, 1.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, world.car->car_tex);
        glEnable(GL_TEXTURE_2D);
        draw_model(world.car->m_car);
        glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
    }
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
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialFunc);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glClearColor(0.15, 0.01, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat ambient[4] = {world.light->ambient, world.light->ambient, world.light->ambient, world.light->ambient};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambient);
	glEnable(GL_LIGHTING);
    glClearDepth(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.f, VIEWPORT_RATIO, 0.01, 1000.0);
}

void specialFunc(int key, int x, int y){
    if(key == GLUT_KEY_F1){
        if(help.on == 1) { help.on = 0; } else { help.on = 1;}
    }
}
void draw_help() {

	GLfloat ones[] = { 1, 1, 1, 1 };
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ones);
				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ones);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, help.help_tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutSwapBuffers();
}
void idle()
{
	glutPostRedisplay();
}