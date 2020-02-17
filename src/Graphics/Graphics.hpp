#if !defined(GRAPHICS_HPP)
#define GRAPHICS_HPP

#include "../common.hpp"
#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include "Camera.hpp"
#include <chrono>
#include "../Game/Game.hpp"

namespace Graphics
{

    extern int mouse_x;
    extern int mouse_y;
    extern int window_width;
    extern int window_height;
    extern std::chrono::microseconds dt_ms;
    extern float frame_time;
    void setup(uint width, uint height);
    void render();
    void keyboard_handler(unsigned char key, int x, int y);
    void mouse_motion_handler(int x, int y);
    void reshape(GLsizei width, GLsizei height);
    void mouse_handler(int button, int state, int x, int y);
} // namespace Graphics

#endif // GRAPHICS_HPP
