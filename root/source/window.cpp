#include "window.h"
#include <QFont>
#include <QLabel>

#include <sstream>
#include <string>



Window::Window(QWidget *parent) : QWidget(parent)
{
    //Font kinds in the window
    QFont font_kind1("Calibri", 14);
    QFont font_kind2("Calibri", 26);
    QFont font_kind3("Calibri", 48);

    //Everything for scaning perticular directory
    ask_dir = new QLabel("You want to scan only one particular directory?");
    funny_joke = new QLabel("We have the solution specially for you!");
    ask_dir->setFont(font_kind1);
    funny_joke->setFont(font_kind1);

    //Space to enter the name of the directory, which you want to scan
    line = new QLineEdit;
    line->setText("Enter full name of the directory");
    line->selectAll();
    line->setFont(font_kind1);

    //"Scan it" button
    scanit = new QPushButton("&Scan it");
    scanit->setFont(font_kind2);

    //Passive-defence switch
    passive_def = new QCheckBox ("Passive defenсe");
    passive_def->setFont(font_kind2);

    //"Scan all" button
    scanall = new QPushButton("&Scan root");
    scanall->setFont(font_kind3);

    //LayOut
    layout1 = new QVBoxLayout;
    layout1->addWidget(ask_dir);
    layout1->addWidget(funny_joke);
    layout2 = new QVBoxLayout;
    layout2->addWidget(line);
    layout2->addWidget(scanit);
    layout3 = new QHBoxLayout;
    layout3->addLayout(layout2);
    layout3->addWidget(scanall);
    layout4 = new QVBoxLayout;
    layout4->addLayout(layout1);
    layout4->addLayout(layout3);
    layout4->addWidget(passive_def);
    layout4->addStretch();


    //Window's head name and other features
    setWindowTitle("Antivirus v 2.0");
    setMinimumSize(650, 200);
    setLayout(layout4);



    //Signal-slot connection
    connect(scanit,SIGNAL(clicked()),this,SLOT(scan_dir()),Qt::DirectConnection);
    connect(scanall,SIGNAL(clicked()),this,SLOT(scan_all()),Qt::DirectConnection);
    connect(passive_def,SIGNAL(toggled(bool)),this,SLOT(pass_def()),Qt::DirectConnection);
}
 void Window::scan_dir()
 {
     s = line->text();

     QProcess *process = new QProcess();
     QString program = "Scanner.exe";
     process->start(program, QStringList() << s);



     QLabel *indicator1 = new QLabel("Scanning is started!");
     QFont FontKind1("Calibri",36);
     indicator1->setFont(FontKind1);
     indicator1->show();
 }
void Window::scan_all()//actually, not all. just a root path.
{

    s=QDir::rootPath();

    QProcess *process = new QProcess();
    QString program = "Scanner.exe";
    process->start(program, QStringList() << s);




    QLabel *indicator2 = new QLabel("Scanning is started!");
    QFont FontKind2("Calibri",36);
    indicator2->setFont(FontKind2);
    indicator2->show();
}
void Window::pass_def()
{

    if(passive_def->isChecked())
    {
        bool t2=true;
        //this->antivirus->passiveProtection->turnOnProtection();
        //Нужно как-то передать булево значение экземпляру класса Пассивный защитник,
        //который, в свою очередь нужно создать, так, чтобы Qt не ругался.
        //И когда Защитник включится, появится окно, оповещающее о его активации
        QLabel *indicator3 = new QLabel("Activate passive defence? Done!");
        QFont FontKind3("Calibri",36);
        indicator3->setFont(FontKind3);
        indicator3->show();
    }
    else
    {
        bool t2=false;
        //this->antivirus->passiveProtection->turnOffProtection();
        //Нужно как-то передать булево значение экземпляру класса Пассивный защитник,
        //который, в свою очередь нужно создать, так, чтобы Qt не ругался.
        //И когда Защитник выключится, появится окно, оповещающее о его деактивации
        QLabel *indicator3 = new QLabel("Deactivate passive defence? Done!");
        QFont FontKind3("Calibri",36);
        indicator3->setFont(FontKind3);
        indicator3->show();
    }
}
