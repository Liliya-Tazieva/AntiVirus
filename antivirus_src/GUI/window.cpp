#include "window.h"
#include <QFont>
#include <QDebug>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <sstream>
#include <string>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QCloseEvent>

void Window::closeEvent(QCloseEvent *event)
{
    if(process_rtp!=nullptr)
        if(process_rtp->state() == QProcess::Running)
            try{
                process_rtp->close();
            }catch(std::exception e){};
    if(process!=nullptr)
        if(process->state() == QProcess::Running)
            try{
                process->close();
            }catch(std::exception e){};
    //logging
    log_process = new QProcess();
    QString program = "Logger.exe";
    QString msg = "GUI closed";
    log_process->start(program, QStringList() << msg);

    event->accept();

}
void Window::requestVersion(){
    QNetworkAccessManager *m = new QNetworkAccessManager(this);
    connect(m,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));
    m->get(QNetworkRequest(QUrl("http://pmpu-prject.ru/pmpufile.txt")));
}

void Window::requestReceived(QNetworkReply* reply){
    QByteArray rawData = reply->readAll();
    QString textData(rawData);
    QFile f("version.txt");
    QString data;
    if (f.open(QFile::ReadOnly | QFile::Text)){
            QTextStream in(&f);
            data=in.readAll();

            if(data!=textData)
                QDesktopServices::openUrl (QUrl( "http://pmpu-prject.ru/outdated.html") );
    }
}


Window::Window(QWidget *parent) : QWidget(parent)
{
    //Font kinds in the window
    QFont font_kind1("Calibri", 14);
    QFont font_kind2("Calibri", 26);
    QFont font_kind3("Calibri", 48);
    QFont font_kind4("Calibri", 20);

    //link to html-file
    link = new QLabel("<a href=\""+QCoreApplication::applicationDirPath()+"/use_PMAV/using.html\">Know more</a>");
    link->setFont(font_kind4);
    link->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    link->setOpenExternalLinks(false);

    //Everything for scaning particular directory
    ask_dir = new QLabel("You want to scan only one particular directory?");
    funny_joke = new QLabel("We have the solution specially for you!");
    ask_dir->setFont(font_kind4);
    funny_joke->setFont(font_kind4);

    //Space to enter the name of the directory, which you want to scan
    line = new QLineEdit;
    line->setText("Enter full name of the directory");
    line->selectAll();
    line->setFont(font_kind4);
    line->setFixedHeight(48);
    choose = new QPushButton("&Choose");
    choose->setFont(font_kind2);

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
    box1->addItem("High");
    box1->setFont(font_kind1);
    box1->setCurrentIndex(0);
    box2->addItem("md5+heuristic");
    box2->addItem("md5");
    box2->setFont(font_kind1);
    lb1->setBuddy(box1);
    lb2->setBuddy(box2);
    box2->setCurrentIndex(0);


    //LayOut
    layout0 = new QHBoxLayout;
    layout0->addWidget(line);
    layout0->addWidget(choose);
    layout1 = new QVBoxLayout;
    layout1->addWidget(ask_dir);
    layout1->addWidget(funny_joke);
    layout1->addLayout(layout0);
    layout1->addWidget(scanit);
    layout1->addWidget(passive_def);
    layout1->addWidget(link);
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
    setWindowTitle("PM defender");
    setMinimumSize(800, 300);
    setLayout(layout3);

   //Signal-slot connection
    connect(scanit, SIGNAL(clicked()), this, SLOT(scan_dir()), Qt::DirectConnection);
    connect(scanall, SIGNAL(clicked()), this, SLOT(scan_all()), Qt::DirectConnection);
    connect(passive_def, SIGNAL(toggled(bool)), this, SLOT(pass_def()), Qt::DirectConnection);
    connect(link, SIGNAL(linkActivated(QString)), this, SLOT(link_clicked(QString)), Qt::DirectConnection);
    connect(choose, SIGNAL(clicked()), this, SLOT(choosing_file()), Qt::DirectConnection);
}


//open instrucion for installing in browser(html-file)
void Window::link_clicked(QString html_adress)
{
    //logging
    log_process = new QProcess();
    QString program = "Logger.exe";
    QString msg = "Link clicked";
    log_process->start(program, QStringList() << msg);
    //create local URL from the path to file
    QUrl fileurl = QUrl::fromUserInput(html_adress);
    //open the file
    QDesktopServices::openUrl(fileurl);
}

//Asking user what he wants to scan: file or directory
void Window::choosing_file()
{
    file_or_directory = new QDialog;
    QFont fk1("Calibri", 22);
    QFont fk2("Calibri", 18);
    what = new QLabel("What do you want to scan: file or folder?");
    what->setFont(fk1);
    fi=new QPushButton("&File");
    fi->setFont(fk2);
    fo=new QPushButton("&Folder");
    fo->setFont(fk2);
    connect(fi, SIGNAL(clicked()), this, SLOT(explorer_creator1()), Qt::DirectConnection);
    connect(fi, SIGNAL(clicked()), file_or_directory, SLOT(accept()), Qt::DirectConnection);
    connect(fo, SIGNAL(clicked()), this, SLOT(explorer_creator2()), Qt::DirectConnection);
    connect(fo, SIGNAL(clicked()), file_or_directory, SLOT(reject()), Qt::DirectConnection);
    QHBoxLayout *l1 = new QHBoxLayout;
    l1->addWidget(fi);
    l1->addWidget(fo);
    QVBoxLayout *l2 = new QVBoxLayout;
    l2->addWidget(what);
    l2->addLayout(l1);
    file_or_directory->setLayout(l2);
    file_or_directory->setWindowTitle("Choose what to scan");
    file_or_directory->exec();
}

//Creating explorer to choose file
void Window::explorer_creator1()
{
    explorer = new QFileDialog;
    s = explorer->getOpenFileName(this, "Choosing file", QDir::rootPath());
    line->clear();
    line->clear();
    line->setText(s);
}

//Creating explorer to choose folder
void Window::explorer_creator2()
{
    explorer = new QFileDialog;
    s = explorer->getExistingDirectory(this, "Choosing folder", QDir::rootPath(),QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    line->clear();
    line->setText(s);
}

void Window::on_scanner_finished(int x0, QProcess::ExitStatus x1)
{
    //logging
    log_process = new QProcess();
    QString program = "Logger.exe";
    QString msg = "Scanning finished";
    log_process->start(program, QStringList() << msg);

    scanall->setEnabled(true);    scanall->repaint();
    scanit->setEnabled(true);     scanit->repaint();
    line->setText("");
    line->setEnabled(true);       line->repaint();
    choose->setEnabled(true);     choose->repaint();
    box1->setEnabled(true);       box1->repaint();
    box2->setEnabled(true);       box2->repaint();

    QLabel *indicator_scanner_finished = new QLabel("Scanning is finished!");
    QFont FontKind2("Calibri",36);
    indicator_scanner_finished->setFont(FontKind2);
    indicator_scanner_finished->show();
}

void Window::disable_all(){
    scanall->setEnabled(false);    scanall->repaint();
    scanit->setEnabled(false);     scanit->repaint();
    line->setText("Scanning is in progress...");
    line->setEnabled(false);       line->repaint();
    choose->setEnabled(false);     choose->repaint();
    box1->setEnabled(false);       box1->repaint();
    box2->setEnabled(false);       box2->repaint();
}



//scans certain dir
//gets dir's with line->text();
void Window::scan_dir()
 {
     s = line->text();

     disable_all();

     QString arg2= box2->currentText();

     //logging
     log_process = new QProcess();
     QString program = "Logger.exe";
     QString msg = "Scanning directory started";
     log_process->start(program, QStringList() << msg);

     process = new QProcess();

     connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_scanner_finished(int,QProcess::ExitStatus)));

     program= "Scanner.exe";

     process->start(program, QStringList() << s<<arg2<<box1->currentText());


 }



void Window::scan_all()//actually, not all. just a root path.
{

    disable_all();

    //logging
    log_process = new QProcess();
    QString program = "Logger.exe";
    QString msg = "Scanning root started";
    log_process->start(program, QStringList() << msg);

    s=QDir::rootPath();
    QString f="Windows";

    std::string s0 = QSysInfo::prettyProductName().toStdString();
    if (s0 == "Windows 8" || s0 == "Windows 8.1"||s0 == "Windows 10")
        s.append(f);
   // qDebug()<<s;

    QString arg2= box2->currentText();

    process = new QProcess();

    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_scanner_finished(int,QProcess::ExitStatus)));
    program= "Scanner.exe";

    process->start(program, QStringList() << s<<arg2<<box1->currentText());


}

void Window::on_rtp_finished(int x0, QProcess::ExitStatus x1){
    //logging
    log_process = new QProcess();
    QString program = "Logger.exe";
    QString msg = "Real-time protection is deactivated";
    log_process->start(program, QStringList() << msg);
    passive_def->setChecked(false);
    QLabel *indicator3 = new QLabel("Real-time protection is deactivated");
    QFont FontKind3("Calibri",36);
    indicator3->setFont(FontKind3);
    indicator3->show();

}


//creates passive defence process,
//it is also becomes connected to on_rtp_finish slot so we dont have multiple passive defence processes at once
void Window::pass_def()
{


    if(passive_def->isChecked())
    {
        //logging
        log_process = new QProcess();
        QString program = "Logger.exe";
        QString msg = "Real-time protection is activated";
        log_process->start(program, QStringList() << msg);
        process_rtp = new QProcess();
        connect(process_rtp, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(on_rtp_finished(int,QProcess::ExitStatus)));
        program = "rtp_new.exe";

        process_rtp->start(program, QStringList());
        QLabel *indicator3 = new QLabel("Real-time protection is activated");
        QFont FontKind3("Calibri",36);
        indicator3->setFont(FontKind3);
        indicator3->show();
    }else{
        process_rtp->close();
    }

}

