#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "zdglfbowidgets.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ZDGLFBOWidgets>("SceneGraphRendering", 1, 0, "Renderer");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
