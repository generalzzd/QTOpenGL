#include "zdwindow.h"
#include <iostream>
using namespace std;
#include <QWindow>

ZDWindow::ZDWindow(QObject *parent) : QObject(parent)
{

}

bool ZDWindow::openWindow()
{
    cout<<"asdasdas"<<endl;

    QWindow* mchildWin = new QWindow();
    mchildWin->setWidth(640);
    mchildWin->setHeight(480);
    mchildWin->setVisible(true);
    mchildWin->setVisibility(QWindow::FullScreen);
    mchildWin->show();




}
