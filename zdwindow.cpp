#include "zdwindow.h"
#include <iostream>
using namespace std;
#include <QWindow>
#include "zdqwindow.h"

ZDWindow::ZDWindow(QObject *parent) : QObject(parent)
{

}

bool ZDWindow::openWindow()
{
    cout<<"asdasdas"<<endl;

    ZDQWindow* mchildWin = new ZDQWindow();
    mchildWin->setWidth(640);
    mchildWin->setHeight(480);
    mchildWin->setVisible(true);
    //mchildWin->setVisibility(QWindow::FullScreen);


    mchildWin->show();
    mchildWin->requestUpdate();

    return true;
}
