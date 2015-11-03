#include "widget.h"
#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Creating main antivirus window
    Window w;
    //Moving it from the screen's up-left and then showing
    w.move(100, 100);
    w.show();

    return a.exec();
}
