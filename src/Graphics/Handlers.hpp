#if 0
#if !defined(INPUT_HPP)
#define INPUT_HPP

#include "../common.hpp"
#include "Graphics.hpp"

namespace Graphics {
static int mouse_x = window_width / 2;
static int mouse_y = window_height / 2;

void keyboard_handler(unsigned char key, int x, int y){
    switch (key) {
	case 'w':
        std::cout << "w\n";
		break;
	case 's':
        std::cout << "s\n";
		break;
	case 'a':
        std::cout << "a\n";
		break;
	case 'd':
		std::cout << "d\n";
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
	        //process_mouse_movement(&cam, changex, changey);
            //glutWarpPointer(window_width / 2, window_height / 2);
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

}

#endif // INPUT_HPP
#endif