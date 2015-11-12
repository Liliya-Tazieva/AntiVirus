#include "window.h"
#include <QFont>
#include <QLabel>

#include <sstream>
#include <string>
#include <QCryptographicHash>


Window::Window(QWidget *parent) : QWidget(parent)
{
    //Font kinds in the window
    QFont font_kind1("Calibri", 14);
    QFont font_kind2("Calibri", 26);
    QFont font_kind3("Calibri", 48);
    QFont font_kind4("Calibri", 20);

    //Everything for scaning perticular directory
    ask_dir = new QLabel("You want to scan only one particular directory?");
    funny_joke = new QLabel("We have the solution specially for you!");
    ask_dir->setFont(font_kind4);
    funny_joke->setFont(font_kind4);

    //Space to enter the name of the directory, which you want to scan
    line = new QLineEdit;
    line->setText("Enter full name of the directory");
    line->selectAll();
    line->setFont(font_kind1);

    //"Scan it" button
    scanit = new QPushButton("&Scan it");
    scanit->setFont(font_kind2);

    //Passive-defence switch
    passive_def = new QCheckBox ("Real-time protection");
    passive_def->setFont(font_kind2);

    //"Scan all" button
    scanall = new QPushButton("&Scan root");
    scanall->setFont(font_kind3);

    //Combo boxes and their titles
    lb1 = new QLabel("Consumption of resources");
    lb1->setFont(font_kind1);
    lb2 = new QLabel("Scan method");
    lb2->setFont(font_kind1);
    box1 = new QComboBox;
    box2 = new QComboBox;
    box1->addItem("Low");
    box1->addItem("Medium");
    box1->addItem("High");
    box1->setFont(font_kind1);
    box1->setCurrentIndex(2);
    box2->addItem("HEX");
    box2->addItem("MD5");
    box2->setFont(font_kind1);
    lb1->setBuddy(box1);
    lb2->setBuddy(box2);
    box2->setCurrentIndex(1);


    //LayOut
    layout1 = new QVBoxLayout;
    layout1->addWidget(ask_dir);
    layout1->addWidget(funny_joke);
    layout1->addWidget(line);
    layout1->addWidget(scanit);
    layout1->addWidget(passive_def);
    layout1->addStretch();
    layout2 = new QVBoxLayout;
    layout2->addWidget(lb1);
    layout2->addWidget(box1);
    layout2->addWidget(lb2);
    layout2->addWidget(box2);
    layout2->addWidget(scanall);
    layout2->addStretch();
    layout3 = new QHBoxLayout;
    layout3->addLayout(layout1);
    layout3->addLayout(layout2);
    layout3->addStretch();


    //Window's head name and other features
    setWindowTitle("Antivirus v 2.0");
    setMinimumSize(800, 250);
    setLayout(layout3);

   //Signal-slot connection
    connect(scanit,SIGNAL(clicked()),this,SLOT(scan_dir()),Qt::DirectConnection);
    connect(scanall,SIGNAL(clicked()),this,SLOT(scan_all()),Qt::DirectConnection);
    connect(passive_def,SIGNAL(toggled(bool)),this,SLOT(pass_def()),Qt::DirectConnection);
    connect(box1, SIGNAL(currentIndexChanged(QString)), this, SLOT(box1_change()), Qt::DirectConnection);
    connect(box2, SIGNAL(currentIndexChanged(QString)), this, SLOT(box2_change()), Qt::DirectConnection);
    connect(this, SIGNAL(box1_s1()),this, SLOT(low()), Qt::DirectConnection);
    connect(this, SIGNAL(box1_s2()),this, SLOT(medium()), Qt::DirectConnection);
    connect(this, SIGNAL(box1_s3()),this, SLOT(high()), Qt::DirectConnection);
    connect(this, SIGNAL(box2_s1()),this, SLOT(hex()), Qt::DirectConnection);
    connect(this, SIGNAL(box2_s2()),this, SLOT(md5()), Qt::DirectConnection);
}

void Window::on_scanner_finished(int x0, QProcess::ExitStatus x1){
    scanall->setEnabled(true);
    scanall->repaint();
    scanit->setEnabled(true);
    scanit->repaint();
    line->setEnabled(true);
    line->repaint();
    QLabel *indicator_scanner_finished = new QLabel("Scanning is finished!");
    QFont FontKind2("Calibri",36);
    indicator_scanner_finished->setFont(FontKind2);
    indicator_scanner_finished->show();
}

void Window::scan_dir()
 {
    // connect(process, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(on_scanner_finished(int , QProcess::ExitStatus )));
     //connect(process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
     //    [=](int exitCode, QProcess::ExitStatus exitStatus){ /* ... */ });

     s = line->text();

     scanall->setEnabled(false);
     scanall->repaint();
     scanit->setEnabled(false);
     scanit->repaint();
     line->setEnabled(false);
     line->repaint();

     QString arg2="md5";

     process = new QProcess();

     connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_scanner_finished(int,QProcess::ExitStatus)));

     QString program = "Scanner.exe";
     process->start(program, QStringList() << s<<arg2);



     QLabel *indicator1 = new QLabel("Scanning is started!");
     QFont FontKind1("Calibri",36);
     indicator1->setFont(FontKind1);
     indicator1->show();
 }
void Window::scan_all()//actually, not all. just a root path.
{

    scanall->setEnabled(false);
    scanall->repaint();
    scanit->setEnabled(false);
    scanit->repaint();
    line->setEnabled(false);
    line->repaint();

    s=QDir::rootPath();
    QString f="Windows";

    std::string s0 = QSysInfo::prettyProductName().toStdString();
    if (s0 == "Windows 8" || s0 == "Windows 8.1"||s0 == "Windows 10")
        s.append(f);
   // qDebug()<<s;

    QString arg2="md5";

    process = new QProcess();

    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_scanner_finished(int,QProcess::ExitStatus)));


    QString program = "Scanner.exe";
    process->start(program, QStringList() << s<<arg2);




    QLabel *indicator2 = new QLabel("Scanning is started!");
    QFont FontKind2("Calibri",36);
    indicator2->setFont(FontKind2);
    indicator2->show();
}
void Window::on_rtp_finished(int x0, QProcess::ExitStatus x1){
    passive_def->setChecked(false);
    QLabel *indicator3 = new QLabel("Real-time protection is deactivated");
    QFont FontKind3("Calibri",36);
    indicator3->setFont(FontKind3);
    indicator3->show();

}
void Window::pass_def()
{


    if(passive_def->isChecked())
    {
        process_rtp = new QProcess();
        connect(process_rtp, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_rtp_finished(int,QProcess::ExitStatus)));
        QString program = "rtp_new.exe";

        process_rtp->start(program, QStringList());
        QLabel *indicator3 = new QLabel("Real-time protection is activated");
        QFont FontKind3("Calibri",36);
        indicator3->setFont(FontKind3);
        indicator3->show();
    }else{
        process_rtp->close();
    }

}

void Window::box1_change()
{
    QLabel *l = new QLabel("box1_change");
    l->move(1200,400);
    l->show();
    QString s = box1->currentText();
    if(s == "Low") emit box1_s1();
    else if(s == "Medium") emit box1_s2();
    else emit box1_s3();
}

void Window::box2_change()
{
    QLabel *l = new QLabel("box2_change");
    l->move(1200,400);
    l->show();
    QString s = box2->currentText();
    if(s == "HEX") emit box2_s1();
    else emit box2_s2();
}

void Window::low()
{
    QString s = box1->currentText();
    QLabel *l= new QLabel(s);
    l->move(1050,400);
    l->show();
}

void Window::medium()
{
    QString s = box1->currentText();
    QLabel *l= new QLabel(s);
    l->move(1050,400);
    l->show();
}

void Window::high()
{
    QString s = box1->currentText();
    QLabel *l= new QLabel(s);
    l->move(1050,400);
    l->show();
}

void Window::hex()
{
    QString s = box2->currentText();
    QLabel *l= new QLabel(s);
    l->move(900,400);
    l->show();
}

void Window::md5()
{
    QString s = box2->currentText();
    QLabel *l= new QLabel(s);
    l->move(900,400);
    l->show();
}
