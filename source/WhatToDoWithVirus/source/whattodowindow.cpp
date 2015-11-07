#include "whattodowindow.h"
#include <QLabel>
#include <QString>
#include <QFont>

WhatToDoWindow::WhatToDoWindow(QWidget *parent) : QWidget(parent)
{
    //Font kind in the window
    QFont font_kind1("Calibri", 30);
    QFont font_kind2("Calibri", 23);

    //Virus detected, asking what to do line
    question = new QLabel("What to do now?");
    question->setFont(font_kind1);

    //"Delete it?" button
    delbut = new QPushButton("&Delete");
    delbut->setFont(font_kind2);

    //"Ignore it?" button
    ignbut = new QPushButton("&Ignore");
    ignbut->setFont(font_kind2);

    //"Quarantine it?" button
    quarbut = new QPushButton("&Quarantine");
    quarbut->setFont(font_kind2);

    //LayOut
    layout1 = new QHBoxLayout;
    layout1->addWidget(delbut);
    layout1->addWidget(ignbut);
    layout1->addWidget(quarbut);
    layout2 = new QVBoxLayout;

    //Window's head name and other features
    setWindowTitle("Virus detector");
    setLayout(layout2);

    //Signal-slot connection
    connect(delbut,SIGNAL(clicked()),this,SLOT(delete_it()),Qt::DirectConnection);
    connect(ignbut,SIGNAL(clicked()),this,SLOT(ignore_it()),Qt::DirectConnection);
    connect(quarbut,SIGNAL(clicked()),this,SLOT(quarantine_it()),Qt::DirectConnection);

}
//adding type of virus name and adress of file, where it has been located
void WhatToDoWindow::put_adress_and_name_in(char *s1, char *s2)
{
    QString s = QString::fromLocal8Bit(s1,-1);
    adress = new QLabel("in the file " + s);
    s = QString::fromLocal8Bit(s2,-1);
    name = new QLabel("Virus "+s+" has been detected");
    QFont f("Calibri", 30);
    adress->setFont(f);
    name->setFont(f);
}


void WhatToDoWindow::delete_it()
{
    /* Можно будет продумать концепцию всплывающих окон при удалении, но они,
      наверное, не вписываются в архитектуру с процессами, так что я пока просто оставлю место*/
    this->close();
}

void WhatToDoWindow::ignore_it()
{
    /* Можно будет продумать концепцию всплывающих окон при удалении, но они,
      наверное, не вписываются в архитектуру с процессами, так что я пока просто оставлю место*/
    this->close();
}

void WhatToDoWindow::quarantine_it()
{
    /* Можно будет продумать концепцию всплывающих окон при удалении, но они,
      наверное, не вписываются в архитектуру с процессами, так что я пока просто оставлю место*/
    this->close();
}

