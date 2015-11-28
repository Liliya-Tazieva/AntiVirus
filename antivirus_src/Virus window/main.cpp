#include "widget.h"
#include <QApplication>
#include "whattodowindow.h"
#include <string>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Creating main what to do window
    WhatToDoWindow w;
    if(strcmp(argv[1],"md5")==0||strcmp(argv[1],"MD5")==0)
    {
        w.put_adress_and_name_in(argv[2],argv[3]);
        w.layout2->addWidget(w.name);
        w.layout2->addWidget(w.adress);
    }
    else
    {
        w.put_adress_and_name_in_susp(argv[2],argv[3]);
        w.layout2->addWidget(w.adress);
        w.layout2->addWidget(w.name);
    }
    //Spot location for widgets
    w.layout2->addWidget(w.question);
    w.layout2->addLayout(w.layout1);
    w.layout2->addStretch();
    //Moving it from the screen's up-left and then showing
    w.move(100, 100);
    w.show();

    return a.exec();
}
