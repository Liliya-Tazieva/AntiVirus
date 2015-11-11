#include "widget.h"
#include <QApplication>
#include "whattodowindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Creating main what to do window
    WhatToDoWindow w;
    //Spot location for widgets
    w.put_adress_and_name_in(argv[1],argv[2]);
    w.layout2->addWidget(w.name);
    w.layout2->addWidget(w.adress);
    w.layout2->addWidget(w.question);
    w.layout2->addLayout(w.layout1);
    w.layout2->addStretch();
    //Moving it from the screen's up-left and then showing
    w.move(100, 100);
    w.show();

    return a.exec();
}
