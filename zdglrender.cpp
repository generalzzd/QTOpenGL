#include "zdglrender.h"
#include "sokol_gfx.h"
#include <iostream>
using namespace std;


#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

ZDGLRender::ZDGLRender()
{

}

ZDGLRender::~ZDGLRender()
{

}


void ZDGLRender::initialize()
{
    initializeOpenGLFunctions();

    auto glversion = glGetString(GL_VERSION);
    cout<<"GL: "<<glversion<<endl;
    QOpenGLContext* glctx = QOpenGLContext::currentContext();
    bool isgles = glctx->isOpenGLES();
    cout<<"GLES: "<<(isgles ? "True" : "False")<<endl;
    auto glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    cout<<"GLSL Version: "<<glslversion<<endl;

    sg_desc mDesc;
    sg_setup(&mDesc);
}

void ZDGLRender::render()
{


}



