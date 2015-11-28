#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QProcess>
#include <QTextCodec>
#include "traverser.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    a.connect(&w, SIGNAL(quit_()), &a, SLOT(quit()));


    Traverser *traverser=new Traverser();
    a.connect(traverser, SIGNAL(listReady()),&w,SLOT(handleResults()));
    a.connect(&w,SIGNAL(giveList()),traverser, SLOT(giveMore()));

    if(argc>=3){
        if (strcmp(argv[2],"hex")==0)
         w.scantype="hex";
        if (strcmp(argv[2],"md5")==0)
         w.scantype="md5";


        w.activate();

         std::ofstream fout;
         fout.open("log_scanner.txt");
         fout <<argv[2];
         fout <<" scanning algorithm."<<std::endl;
         fout <<"Scan started at: ";
         std::string stds=std::string(argv[1]);
         fout <<stds<<std::endl;

          QTextCodec *codec = QTextCodec::codecForName("UTF8");

          QByteArray ba(stds.c_str());                  // Convert to QByteArray
          QString msg = codec->toUnicode(ba);          // Qt magic !!!


         traverser->initTraversing(QString::fromLocal8Bit(argv[1]),&w);

         traverser->giveMore();

         fout.close();



    }else{
        std::ofstream fout;
        fout.open("log_scanner.txt");

        fout <<"not enough arguments."<<std::endl;
        fout <<"scanner_quit."<<std::endl;

        fout.close();

        qDebug()<<"argc<3";

        QTimer *timer = new QTimer();
            a.connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
            timer->start(300);

    }

    return a.exec();
}



