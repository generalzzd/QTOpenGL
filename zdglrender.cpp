#include "zdglrender.h"

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
    program1.enableAttributeArray(normalAttr1);
    program1.enableAttributeArray(vertexAttr1);
    program1.setAttributeArray(vertexAttr1, vertices.constData());
    program1.setAttributeArray(normalAttr1, normals.constData());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    program1.disableAttributeArray(normalAttr1);
    program1.disableAttributeArray(vertexAttr1);
}


void ZDGLRender::initialize()
{
    initializeOpenGLFunctions();

    vertices.push_back(QVector3D(0.0f,0.0f,1.0f));
    vertices.push_back(QVector3D(1.0f,0.0f,1.0f));
    vertices.push_back(QVector3D(0.0f,1.0f,1.0f));

    vertices.push_back(QVector3D(1.0f,0.0f,1.0f));
    vertices.push_back(QVector3D(1.0f,1.0f,1.0f));
    vertices.push_back(QVector3D(0.0f,1.0f,1.0f));

    auto glversion = glGetString(GL_VERSION);
    cout<<"GL: "<<glversion<<endl;
    QOpenGLContext* glctx = QOpenGLContext::currentContext();
    bool isgles = glctx->isOpenGLES();
    cout<<"GLES: "<<(isgles ? "True" : "False")<<endl;
    auto glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    cout<<"GLSL Version: "<<glslversion<<endl;

    const char *vsrc1 =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec3 normal;\n"
        "uniform mediump mat4 matrix;\n"
        "varying mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
        "    float angle = max(dot(normal, toLight), 0.0);\n"
        "    vec3 col = vec3(0.40, 1.0, 0.0);\n"
        "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
        "    color = clamp(color, 0.0, 1.0);\n"
        "    gl_Position = matrix * vertex;\n"
        "}\n";

    const char *fsrc1 =
        "varying mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = vec4(1.0,0.0,0.0,1.0);\n"
        "}\n";

    program1.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vsrc1);
    program1.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fsrc1);
    program1.link();

    vertexAttr1 = program1.attributeLocation("vertex");
    normalAttr1 = program1.attributeLocation("normal");
    matrixUniform1 = program1.uniformLocation("matrix");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    m_fAngle = 0;
    m_fScale = 1;

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
    modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
    modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
    modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
    modelview.scale(m_fScale);
    modelview.translate(0.0f, 0.0f, 0.0f);
    //modelview.perspective(90.0f, 1.0f,0.0f,100.0f);

    program1.bind();
    program1.setUniformValue(matrixUniform1, modelview);
    paintQtLogo();
    program1.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_fAngle += 1.0f;
}



