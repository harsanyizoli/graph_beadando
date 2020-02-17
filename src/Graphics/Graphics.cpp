#include "Graphics.hpp"

namespace Graphics
{
    int window_width;
    int window_height;
    int mouse_x;
    int mouse_y;
    Game* game;
    std::chrono::microseconds dt_ms;
    float frame_time;
    auto frame_last = std::chrono::high_resolution_clock::now();
    void setup(uint width, uint height){
        window_width = width;
        window_height = height;
        mouse_x = window_width / 2;
        mouse_y = window_height / 2;
        int argc = 1;
        char *argv[1] = {(char*)""};
        game = new Game(width, height);
        glutInit(&argc, argv);
        glutInitWindowSize(width, height);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        int window = glutCreateWindow("GLUT Window");
        glutSetWindow(window);
        //
        glutDisplayFunc(render);
        glutReshapeFunc(NULL);
        glutKeyboardFunc(keyboard_handler);
        glutMouseFunc(mouse_handler);
        glutPassiveMotionFunc(mouse_motion_handler);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glClearColor(0.58, 0.01, 0.9, 1.0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_AUTO_NORMAL);
        glClearDepth(1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.f, (float)width/height, 0.01f, 1000.0f);
        glutMainLoop();
    }

    void render(){
        //std::cout << "render()\n";
        auto frame_curr = std::chrono::high_resolution_clock::now();

        dt_ms = std::chrono::duration_cast<std::chrono::microseconds>(frame_curr - frame_last);
        frame_last = frame_curr;
        frame_time = (float)dt_ms.count()/1000/1000;
        std::cout << "frametime: " << frame_time << "\n";
        game->update(frame_time);
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
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glm::mat3 v = game->cam->GetViewMatrix();
        //std::cout << "v[0].x: " << v[0].x << " v[0].y: " << v[0].y << " v[0].z: " << v[0].z << "\n";
        //std::cout << "v[1].x: " << v[1].x << " v[1].y: " << v[1].y << " v[1].z: " << v[1].z << "\n";
        //std::cout << "v[2].x: " << v[2].x << " v[2].y: " << v[2].y << " v[2].z: " << v[2].z << "\n";
        gluLookAt(v[0].x, v[0].y, v[0].z,
                  v[1].x, v[1].y, v[1].z,
                  v[2].x, v[2].y, v[2].z);/*
        gluLookAt(0.0f, 0.0f, -3.0f, 
                    0.0f, 0.0f, 0.0f, 
                    0.0f, 1.0f, 0.0f);*/
        glutSwapBuffers();
        glutPostRedisplay();
    }

    void keyboard_handler(unsigned char key, int x, int y){
        switch (key) {
        case 'w':
            std::cout << "w\n";
            game->cam->ProcessKeyboard(FORWARD, frame_time);
            break;
        case 's':
            std::cout << "s\n";
            game->cam->ProcessKeyboard(BACKWARD, frame_time);
            break;
        case 'a':
            std::cout << "a\n";
            game->cam->ProcessKeyboard(LEFT, frame_time);
            break;
        case 'd':
            std::cout << "d\n";
            game->cam->ProcessKeyboard(RIGHT, frame_time);
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
            changex = x - window_width/2;
            changey = window_height/2 - y;
        
            if(changex != 0 || changey != 0){
                mouse_x = x;
                mouse_y = y;
                game->cam->ProcessMouseMovement(changex, changey, true);
                glutWarpPointer(window_width / 2, window_height / 2);
            }
    }
    void reshape(GLsizei width, GLsizei height)
    {
        int x, y, w, h;
        float ratio;

        ratio = (float)width / height;
        float viewport_ratio = (float)(window_width/window_height);
        if (ratio > viewport_ratio) {
            w = (int)((float)height * viewport_ratio);
            h = height;
            x = (width - w) / 2;
            y = 0;
        }
        else {
            w = width;
            h = (int)((float)width / viewport_ratio);
            x = 0;
            y = (height - h) / 2;
        }

        glViewport (x, y, w, h);
    }

    void mouse_handler(int button, int state, int x, int y){
        printf("mouse button pressed. %d state: %d", button, state);
    }

} // namespace Graphics
