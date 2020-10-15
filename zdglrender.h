#ifndef ZDGLRENDER_H
#define ZDGLRENDER_H

#include <QObject>

#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include <QTime>
#include <QVector>

class ZDGLRender : public QOpenGLFunctions
{
public:
    ZDGLRender();
    ~ZDGLRender();

    void render();
    void initialize();

private:

    void paintQtLogo();

    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QOpenGLShaderProgram shader1;
    int vertexAttr1;
    int normalAttr1;
    int matrixUniform1;
};

#endif // ZDGLRENDER_H
