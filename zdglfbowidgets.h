#ifndef ZDGLFBOWIDGETS_H
#define ZDGLFBOWIDGETS_H

#include <QObject>
#include <QtQuick/QQuickFramebufferObject>


class ZDGLFBOWidgets: public QQuickFramebufferObject
{
    Q_OBJECT
public:
    Renderer *createRenderer() const;
};

#endif // ZDGLFBOWIDGETS_H
