#include "whattodowindow.h"
#include <QLabel>
#include <QFont>

WhatToDoWindow::WhatToDoWindow(QWidget *parent) : QWidget(parent)
{
    //Font kind in the window
    QFont font_kind1("Calibri", 30);
    QFont font_kind2("Calibri", 23);

    //Virus detected, asking what to do line
    question = new QLabel("Virus has been detected! What to do now?");
    question->setFont(font_kind1);

    //"Delete it?" button
    delbut = new QPushButton("&Delete it?");
    delbut->setFont(font_kind2);

    //"Ignore it?" button
    ignbut = new QPushButton("&Ignore it?");
    ignbut->setFont(font_kind2);

    //"Quarantine it?" button
    quarbut = new QPushButton("&Quarantine it?");
    quarbut->setFont(font_kind2);

    //LayOut
    layout1 = new QHBoxLayout;
    layout1->addWidget(delbut);
    layout1->addWidget(ignbut);
    layout1->addWidget(quarbut);
    layout2 = new QVBoxLayout;
    layout2->addWidget(question);
    layout2->addLayout(layout1);
    layout2->addStretch();

    //Window's head name and other features
    setWindowTitle("Virus detecter");
    setLayout(layout2);

    //Signal-slot connection
    connect(delbut,SIGNAL(clicked()),this,SLOT(delete_it()),Qt::DirectConnection);
    connect(ignbut,SIGNAL(clicked()),this,SLOT(ignore_it()),Qt::DirectConnection);
    connect(quarbut,SIGNAL(clicked()),this,SLOT(quarantine_it()),Qt::DirectConnection);

}
void WhatToDoWindow::delete_it()
{
    bool t=true;
    //Нужно как-то передать булево значение экземпляру класса Сканер в функцию удаления вирусов,
    //который, в свою очередь нужно создать, так, чтобы Qt не ругался.
    //И когда Сканер закончит свою работу, появится окно, оповещающее об удалении угрозы
    QLabel *indicator1 = new QLabel("Deleted");
    QFont FontKind1("Calibri",36);
    indicator1->setFont(FontKind1);
    indicator1->move(250, 250);
    indicator1->show();
}

void WhatToDoWindow::ignore_it()
{
    bool t=true;
    //Нужно как-то передать булево значение экземпляру класса Сканер в функцию игнорирования вирусов,
    //который, в свою очередь нужно создать, так, чтобы Qt не ругался.
    //И когда Сканер закончит свою работу, появится окно, оповещающее об успешном игнорировании угрозы
    QLabel *indicator2 = new QLabel("Ignored");
    QFont FontKind2("Calibri",36);
    indicator2->setFont(FontKind2);
    indicator2->move(250, 250);
    indicator2->show();
}

void WhatToDoWindow::quarantine_it()
{
    bool t=true;
    //Нужно как-то передать булево значение экземпляру класса Сканер в функцию, помещающую вирусы в карантин,
    //который, в свою очередь нужно создать, так, чтобы Qt не ругался.
    //И когда Сканер закончит свою работу, появится окно, оповещающее о помещении угрозы в карантин
    QLabel *indicator3 = new QLabel("Quarantined");
    QFont FontKind3("Calibri",36);
    indicator3->setFont(FontKind3);
    indicator3->move(250, 250);
    indicator3->show();
}

