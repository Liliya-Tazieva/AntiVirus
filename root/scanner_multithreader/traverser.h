#ifndef TRAVERSER
#define TRAVERSER

#endif // TRAVERSER
#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QProcess>
class Traverser:public QObject{
    Q_OBJECT
public:

    QList<std::string> privateList;
    MainWindow* w;
    void initTraversing(const char* s,MainWindow* w0){
        w=w0;
        w->stack.push(s);
    }
signals:
    void listReady();
public slots:

    void continueTraversing(){
        std::ofstream fout;
        fout.open("log_scanner.txt", std::ios::app);
            while (w->stack.size()!=0&&privateList.length()<100){
                std::string st =  w->stack.top();
                fout <<"Scanning directory: ";
                fout <<st<< std::endl;
                 w->stack.pop();
                QDir start(st.c_str());
                start.setNameFilters(QStringList() << "*");
                std::string currentString;
                if (!start.exists())
                {
                   fout <<"error"<< std::endl;
                }
                QStringList  dir_list = start.entryList(QDir::AllDirs);
                //qDebug()<<dir_list;
                for (int i = 0; i < dir_list.size(); ++i){
                    if (dir_list.at(i) != "."&&dir_list.at(i) != ".."){
                        currentString = st;
                        currentString.append("\\");
                        currentString.append(dir_list.at(i).toStdString());
                         w->stack.push(currentString);
                    }
                }

                QStringList file_list = start.entryList(QDir::Files);
                for (int i = 0; i < file_list.size(); ++i){
                    currentString = st;
                    currentString.append("\\");
                    currentString.append(file_list.at(i).toStdString());
                    privateList.append(currentString);

                }

                fout.close();
            }
        if(w->stack.size()==0)
            w->traverserFinished=true;



    }

    void giveMore(){
        privateList.clear();
        if(!w->traverserFinished)continueTraversing();
        w->filesToScan=QList<std::string>(privateList);
        emit listReady();

    }
};
