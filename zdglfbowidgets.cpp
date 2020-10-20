#include "zdglfbowidgets.h"

#include <QtGui/QOpenGLFramebufferObject>
#include "zdglrender.h"

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>

class LogoInFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    LogoInFboRenderer()
    {
        logo.initialize(fbo);
    }

    void render() override {
        logo.render();
        update();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        fbo = new QOpenGLFramebufferObject(size, format);
        return fbo;
    }

    ZDGLRender logo;
    QOpenGLFramebufferObject* fbo;
};

QQuickFramebufferObject::Renderer *ZDGLFBOWidgets::createRenderer() const
{
    return new LogoInFboRenderer();
}
