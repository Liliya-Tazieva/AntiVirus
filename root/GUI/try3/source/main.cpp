
#include "widget.h"
#include <QApplication>
#include "window.h"
#include <QApplication>
#include <QPushButton>
#include <string>
#include <QDir>
#include <QStringList>
#include <fstream>
#include <stack>
#include <QThread>
#include <QObject>
#include  <QFile>
#include  <QTextStream>
#include <QDebug>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Creating main GUI window
    //action is happening somewhere else

    Window w;
    //Moving it from the screen's up-left and then showing
    w.move(100, 100);
    w.show();




    return a.exec();
}
