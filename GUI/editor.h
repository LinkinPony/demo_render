#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "geometry.h"
#include "drawer.h"
#include "model.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>  // Will drag system OpenGL headers
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

class Editor{
    //TODO: In the current version, class Drawer seems to be useless. Delete it and integrate it into Editor.
protected:
    int image_width = 0;//
    int image_height = 0;
    GLuint image_texture;//render result
    /* use for drawer */
    Vec3f view_center = Vec3f(1, 1, 1);
    Vec3f camera_position = Vec3f(1000,1000,1000);
    Drawer * drawer;
    Model * model;
    /* use for OpenGL texture */
    GLuint raw_image_texture;
    int raw_image_width;
    int raw_image_height;
    unsigned char * image_data;


    void genTextureInit();
public:
    float * zbuffer;
    int run();
    bool loadTextureFromMemory();
    void nextFrame();
//    Editor(){}
    Editor(int width,int height,Drawer * _drawer,Model * _model){
        image_height = height;
        image_width = width;
        drawer = _drawer;
        model = _model;
    }
//    int image_width2,int image_height2,void * image_data2
};