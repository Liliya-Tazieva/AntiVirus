#include "window.h"
#include <QFont>
#include <QLabel>
#include <sstream>
#include <string>
#include <QTimer>


Window::Window(QWidget *parent) : QWidget(parent)
{
    timer=new QTimer;
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




    std::string s09 = QSysInfo::prettyProductName().toStdString();
    if (s09 == "Windows 8" || s09 == "Windows 8.1"){
        antivirus = new Antivirus8();
    }
    else if (s09 == "Windows 10"){
        antivirus = new Antivirus10();
    }
   //

    //QPushButton button0(s.c_str());
    //button0.show();





    //Signal-slot connection
    connect(scanit,SIGNAL(clicked()),this,SLOT(wait_window1()),Qt::DirectConnection);
    connect(scanall,SIGNAL(clicked()),this,SLOT(wait_window2()),Qt::DirectConnection);
    connect(passive_def,SIGNAL(toggled(bool)),this,SLOT(pass_def()),Qt::DirectConnection);
}

//waiting window for "Scan it" button
void Window::wait_window1()
{
    //showing waiting window while it's scanning
    scanit->setVisible(false);//hiding "Scan it" button while scaner works
    waiting_window = new QLabel ("Please, wait");
    QFont FontKind("Calibri",36);
    waiting_window->setFont(FontKind);
    waiting_window->setWindowTitle("Scanning");
    waiting_window->setMinimumHeight(200);
    waiting_window->show();
    timer = new QTimer(this);
    timer->start(1);
    connect(timer, SIGNAL(timeout()), this, SLOT(scan_dir()),Qt::DirectConnection);
}

//waiting window for "Scan root" button
void Window::wait_window2()
{
    //showing waiting window while it's scanning
    scanall->hide();//hiding "Scan root" button while scaner works
    waiting_window = new QLabel ("Please, wait");
    QFont FontKind("Calibri",36);
    waiting_window->setFont(FontKind);
    waiting_window->setWindowTitle("Scanning");
    waiting_window->setMinimumHeight(200);
    waiting_window->show();
    timer = new QTimer(this);
    timer->start(1);
    connect(timer, SIGNAL(timeout()), this, SLOT(scan_all()),Qt::DirectConnection);
}

//Scaning directory
 void Window::scan_dir()
 {

     //scanning
     timer->stop();
     s = line->text();
     this->antivirus->scanner->traverseForScanning(s.toStdString().c_str());
     timer = new QTimer(this);
     timer->start(1);
     connect(timer, SIGNAL(timeout()), this, SLOT(close_waiting_window1()),Qt::DirectConnection);

 }

//Scanning root
void Window::scan_all()
{
    /*Logger* logger=new Logger();

    //QString QDir::homePath()
    for(long i=0;i<19999;i++)
            logger->writeToLog("34363473");*/

    //scanning
    timer->stop();
    s=QDir::rootPath();
    this->antivirus->scanner->traverseForScanning(s.toStdString().c_str());
    timer = new QTimer(this);
    timer->start(1);
    connect(timer, SIGNAL(timeout()), this, SLOT(close_waiting_window2()),Qt::DirectConnection);
 }

//Closing waiting window for "Scan it" button
void Window::close_waiting_window1()
{
    waiting_window->close();
    scanit->show();//showing "Scan it" button again
    timer->stop();
    QFont f("Calibri",36);
    SW = new QLabel("Scanned");
    SW->setWindowTitle("Done");
    SW->setMinimumHeight(200);
    SW->setFont(f);
    SW->show();
    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(close_the_window()),Qt::DirectConnection);
}

//Closing waiting window for "Scan root" button
void Window::close_waiting_window2()
{
    waiting_window->close();
    scanall->show();//showing "Scan root" button again
    timer->stop();
    QFont f("Calibri",36);
    SW = new QLabel("Scanned");
    SW->setWindowTitle("Done");
    SW->setMinimumHeight(200);
    SW->setFont(f);
    SW->show();
    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(close_the_window()),Qt::DirectConnection);
}

void Window::pass_def()
{
    if(passive_def->isChecked())
    {
       bool t2=true;
       this->antivirus->passiveProtection->turnOnProtection();
       //popup
       QFont f("Calibri",25);
       SW = new QLabel("Passive defence's activated");
       SW->setWindowTitle("Done");
       SW->setMinimumHeight(200);
       SW->setFont(f);
       SW->show();
       timer = new QTimer(this);
       timer->start(2000);
       connect(timer, SIGNAL(timeout()), this, SLOT(close_the_window()),Qt::DirectConnection);

    }
    else
    {
        bool t2=false;
        this->antivirus->passiveProtection->turnOffProtection();
        //popup
        QFont f("Calibri",25);
        SW = new QLabel("Passive defence's deactivated");
        SW->setWindowTitle("Done");
        SW->setMinimumHeight(200);
        SW->setFont(f);
        SW->show();
        timer = new QTimer(this);
        timer->start(2000);
        connect(timer, SIGNAL(timeout()), this, SLOT(close_the_window()),Qt::DirectConnection);
    }
}
void Window::close_the_window()
{
    SW->close();
    timer->stop();
}
