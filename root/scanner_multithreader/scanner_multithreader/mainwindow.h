#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include  <Stack>
#include <QDir>
#include "QThread"
#include "emitter.h"
#include "worker.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::string scantype;
    std::stack<QString, std::list<QString>> stack;
    QList<QString> filesToScan;

    bool traverserFinished=false;
    int itc;
    QThread* workerThread;

    Emitter* emitters;
    /*
        does some needed computations and loadings before scan starts.
        creates workers and their threads and emitters,
        connects them to each other, loads db to workers and moves them to different thread.
    */
    void activate(){
        itc=QThread::idealThreadCount();
        if (itc<1)itc=1;
        workerThread=new QThread[itc];
        emitters=new Emitter[itc];
        for(int i=0;i<itc;i++){
            Worker *worker;
            if(scantype=="md5")
              worker = new Worker_md5();
            if(scantype=="hex")
              worker = new Worker_hex();
            worker->loadDB();
            connect(worker, &Worker::resultReady,&(emitters[i]), &Emitter::finishSlot);
            connect(worker, SIGNAL(resultReady()),this, SLOT(handleResults()));
            connect(worker, SIGNAL(virusFound(QString,QString)),this, SLOT(openVirusFoundWindow(QString,QString)));

            worker->moveToThread(&(workerThread[i]));            

            connect(&(workerThread[i]), &QThread::finished, worker, &QObject::deleteLater);
            connect(&(emitters[i]), &Emitter::operate, worker, &Worker::doWork);

            workerThread[i].start(QThread::HighPriority);
        }
    }


private:
    Ui::MainWindow *ui;
public slots:
    /*
        the first arg is adress of found suspicious file, the second one is optional parameter (it's virus name/number for signature search)
    */
    void openVirusFoundWindow(QString adress,QString name){
        QProcess *process = new QProcess();
        QString program = "WhatToDoWithVirus.exe";
        QString arg1 = adress;
        QString arg2 = name;
        process->start(program, QStringList() << arg1<<arg2);
    }
    /*
        takes the result of traversing from filesToScan and gives emitters tasks from it.
        if filesToScan is empty, asks for more.
        continues until traverser gives more.
        if all threads are finished and traverser doesn't give more, ends scan.
    */
    void handleResults(){
        if(!filesToScan.isEmpty()){
            for(int i=0;i<itc;i++)
               if(!emitters[i].isWorking){
                   QString h=filesToScan.last();
                   filesToScan.removeLast();
                    emitters[i].em(h);
                    if(filesToScan.isEmpty())break;
                }

        }else{
            if(traverserFinished){
                bool work=false;
                for(int i=0;i<itc;i++)
                   if(emitters[i].isWorking){
                       work=true;
                       break;
                    }
                if(!work){
                    qDebug()<<"exit";

                    std::ofstream fout;
                    fout.open("log_scanner.txt", std::ios::app);
                    fout <<"scanner_quit."<<std::endl;
                    fout.close();

                    emit quit_();
                    QTimer *timer = new QTimer(this);
                        connect(timer, SIGNAL(timeout()), this, SLOT(q()));
                        timer->start(300);
                }
            }else{
                emit giveList();
            }
        }
    }
    void q(){
        emit quit_();
    }
signals:
    void giveList();
    void quit_();
};

#endif // MAINWINDOW_H
