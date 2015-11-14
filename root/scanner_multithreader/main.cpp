#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QProcess>
#include "traverser.h"
/*
    std::ofstream fout;
    fout.open("log_scanner.txt");
    fout.open("log_scanner.txt", std::ios::app);
    fout << std::endl;
    fout.close();
*/


/*
void callVirusFoundWindow(std::string adress, std::string name) {
    QProcess *process = new QProcess();
    QString program = "WhatToDoWithVirus.exe";
    QString arg1 = QString::fromStdString(adress);
    QString arg2 = QString::fromStdString(name);
    process->start(program, QStringList() << arg1<<arg2);

}*/



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
         fout <<argv[1]<<std::endl;


         traverser->initTraversing(argv[1],&w);
         traverser->giveMore();

        // if(w.filesToScan.isEmpty())
         //    return 1;

         //w.handleResults();

         fout <<"scanner_quit."<<std::endl;

         fout.close();



    }else{
        std::ofstream fout;
        fout.open("log_scanner.txt");

        fout <<"not enough arguments."<<std::endl;
        fout <<"scanner_quit."<<std::endl;

        fout.close();
/*
        w.scantype="hex";


        w.activate();

        traverser->initTraversing("C:\\Qt\\Qt5.5.10\\5.5\\msvc2013\\include\\QtCore\\5.5.1\\QtCore",&w);
        traverser->giveMore();


       // for(int i=0;i<w.filesToScan.length();i++)
       //     qDebug()<<(QString::fromStdString(w.filesToScan[i]));
         qDebug()<<"----";

       //  if(w.filesToScan.isEmpty())
        //     return 1;

        //w.handleResults();

*/

    }


    return a.exec();
}



