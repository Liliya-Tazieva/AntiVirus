#include "ask_window.h"
#include <QFont>

ask_window::ask_window(QWidget *parent) : QWidget(parent)
{
    //Fonts
    QFont f1("Calibri",20);
    QFont f2("Calibri", 25);

    //Labels
    situation = new QLabel("Attempt to change autoloads has been detected");
    something = new QLabel("Empty string");
    question = new QLabel("Allow it?");
    situation->setFont(f2);
    something->setFont(f2);
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
    setWindowTitle("Some name");
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
}

void ask_window::no()
{
}
