#ifndef ZDGLRENDER_H
#define ZDGLRENDER_H

#include <QObject>

#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/QOpenGLFramebufferObject>

#include <QTime>
#include <QVector>

class ZDGLRender : public QOpenGLFunctions
{
public:
    ZDGLRender();
    ~ZDGLRender();

    void render();
    void initialize(QOpenGLFramebufferObject *fbo);


};

#endif // ZDGLRENDER_H
