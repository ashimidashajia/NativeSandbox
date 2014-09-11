
#ifndef GL_ENGINE_H
#define GL_ENGINE_H

#include <EGL/egl.h>

class GLEngine {

private :

    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    int32_t m_width;
    int32_t m_height;

public:

    GLEngine();
    ~GLEngine();

    void init_display(ANativeWindow* window);
    void terminate_display();

    void draw_frame();
};

#endif