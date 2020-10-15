#include "zdglrender.h"
#include "sokol_gfx.h"
#include <iostream>
using namespace std;

ZDGLRender::ZDGLRender()
{

}

ZDGLRender::~ZDGLRender()
{

}

void ZDGLRender::paintQtLogo()
{
    shader1.enableAttributeArray(normalAttr1);
    shader1.enableAttributeArray(vertexAttr1);
    shader1.setAttributeArray(vertexAttr1, vertices.constData());
    shader1.setAttributeArray(normalAttr1, normals.constData());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    shader1.disableAttributeArray(normalAttr1);
    shader1.disableAttributeArray(vertexAttr1);
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

    const char *vsrc1 =
            "in vec4 vPosition;           \n"\
            "in vec4 vColor;              \n"\
            "out vec4 color;              \n"\
            "void main()                  \n"\
            "{                            \n"\
            "    color = vColor;          \n"\
            "    gl_Position = vPosition; \n"\
            "}                            \n";

    const char *fsrc1 =
                "#version 300                              \n"
                "precision mediump float;                     \n"
                "out vec4 fragColor;                          \n"
                "void main()                                  \n"
                "{                                            \n"
                "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
                "}                                            \n";

    shader1.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vsrc1);
    shader1.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fsrc1);
    shader1.link();

//    vertexAttr1 = shader1.attributeLocation("vertex");
//    normalAttr1 = shader1.attributeLocation("normal");
//    matrixUniform1 = shader1.uniformLocation("matrix");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

}

void ZDGLRender::render()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 modelview;
    modelview.translate(0.0f, -0.2f, 0.0f);

    shader1.bind();
    shader1.setUniformValue(matrixUniform1, modelview);
    //paintQtLogo();
    shader1.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


}



