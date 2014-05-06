#include "window.h"
#include <GL/freeglut.h>
#include <functional>

window* window::s_instance = nullptr;

window::window(const std::string& title, int w, int h):
    m_width(w),
    m_height(h)
{
    if (s_instance != nullptr) {
        throw std::string("Can be only used once !");
    }
    s_instance = this;
    glutInit(0, 0);
    glutInitContextVersion(1, 4);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("game-of-life");
    glutReshapeFunc([](int w, int h){
        window::s_instance->onResize(w, h);
    });
    glutDisplayFunc([](){
        window::s_instance->onRender();
    });
    glutMouseFunc([](int button, int state, int x, int y) {
        if ((button == 3) || (button == 4)) {
            if (state == GLUT_UP) {
                return;
            }
            window::s_instance->onScroll((button == 3)?1:-1);
        } else {
            window::s_instance->onMouse(button, state, x, y);
        }
    });
    glutMotionFunc([](int x, int y) {
        window::s_instance->onMouseMotion(x, y);
    });
}

void window::loop() {
    glutMainLoop();
}

int window::width() const {
    return m_width;
}

int window::height() const {
    return m_height;
}
