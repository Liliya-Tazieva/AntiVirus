#include "ask_window.h"
#include <QFont>
#include <QDebug>

ask_window::ask_window(QWidget *parent) : QWidget(parent)
{
    //Fonts
    QFont f0("Calibri",16);
    QFont f1("Calibri",20);
    QFont f2("Calibri", 25);
    s0="undefined";
    s1="undefined";
    s2="undefined";

    //Labels
    situation = new QLabel(s0);
    something = new QLabel(s1);
    question = new QLabel(s2);
    situation->setFont(f2);
    something->setFont(f0);
    question->setFont(f2);

    //Buttons
    yes_but = new QPushButton("&Yes");
    yes_but->setFont(f1);
    no_but = new QPushButton("&No");
    no_but->setFont(f1);

    //Layout
    lo1 = new QHBoxLayout;
    lo1->addWidget(yes_but);
    lo1->addWidget(no_but);
    lo2 = new QVBoxLayout;
    lo2->addWidget(situation);
    lo2->addWidget(something);
    lo2->addWidget(question);
    lo2->addLayout(lo1);

    //Window Settings
    setWindowTitle("Real-time protection");
    setLayout(lo2);

    //Signal-slot connection
    connect(yes_but,SIGNAL(clicked()),this,SLOT(yes()),Qt::DirectConnection);
    connect(no_but,SIGNAL(clicked()),this,SLOT(no()),Qt::DirectConnection);

}

void ask_window::activate()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(invoke()));
    timer->start(5000);

/*

    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &MainWindow::handleResults);
    workerThread.start();
    QString ssf="f";
    emit operate(ssf);
     emit operate(ssf);
     emit operate(ssf);*/
}


void ask_window::yes()
{
    if(mode=="registry_changed"){
        c_r[reserved_registry_parameter_changed_int].push_front(reserved_registry_parameter_changed);
    }
     this->hide();
}


