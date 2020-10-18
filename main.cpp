#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include<iostream>
using namespace std;

#include"zdwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    ZDWindow mWindow;

    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("ZDWindow", &mWindow);



    engine.load(url);

    return app.exec();
}
