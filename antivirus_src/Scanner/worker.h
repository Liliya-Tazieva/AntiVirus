#ifndef WORKER
#define WORKER

#endif // WORKER
#include <string>
#include <QString>
#include <QDebug>
#include <QProcess>
#include <iostream>
#include <fstream>
#include <QCryptographicHash>
#include <QFile>
#include <QThread>
#include "heuristicable.h"

using namespace pe_bliss;

class Worker : public QObject,public Heuristicable
{
    Q_OBJECT
public:
    std::string* database;
    std::string* namebase;
    long databaseLength=0;

    bool heuristic=false;



    /*
    Scan is a function that can be applied to FILES ONLY.	directories' analog of scan is traverseForScanning function
    does signature search on a given file
    if finds something, then it opens whattodowithvirus.exe window, if not, does nothing
    requires the database to be loaded before to work correctly
    */

    bool scan(std::string s, QString& param1, QString& param2){
        param1="";
        param2="";
        QString fileName= QString::fromStdString(s);
        QCryptographicHash crypto(QCryptographicHash::Md5);
        QFile file(fileName);
        file.open(QFile::ReadOnly);
        while(!file.atEnd()){
          crypto.addData(file.read(8192));
        }
        QByteArray buf2 = crypto.result().toHex();

                for(long i=0;i<databaseLength;i++){
                    bool containsAt0=true;
                    long elementLength=database[i].length();
                    long ii=0;
                    while((40000>ii)&&(elementLength>ii)){
                        if(buf2.at(ii)!=database[i][ii])
                            containsAt0=false;
                        ii++;
                    }
                    if(containsAt0){
                        qDebug()<<"Virus found!";

                            std::ofstream fout;
                            fout.open("log_scanner.txt", std::ios::app);
                            fout << "suspicious file found at: ";
                            fout <<s<< std::endl;
                            fout << "the name of virus is: ";
                            fout <<'#'<<i<< std::endl;
                            fout << "the md5 hash of virus is: ";
                            fout <<database[i]<< std::endl;
                            param1=QString::fromStdString(s);
                            param2=QString::number(i).prepend('#');
                            return true;
                    }
                }
                return false;
    }

    /*
    is quite self-explanatory.
        it loads in operative memory all the known virus signatures. //in database string array, namebase is names array
        we dont use file reading from base because it will slow the scanning greatly.
        really fast, makes me proud.
    */

    void loadDB(){

        QFile f("viruses_md5.db");
        QString data;
            if (f.open(QFile::ReadOnly | QFile::Text)){
                QTextStream in(&f);
                data=in.readAll();
            }
            long long l=data.length();
            long ncounter=0;
            long niterator=0;

            for(long long i=0;i<l;++i)
                if (data.at(i)=='\n')
                   ++ncounter;


            database=new std::string[ncounter];
            namebase=new std::string[ncounter];
            QString str="";
            for(long long i=0;i<l;i++){
                if (data.at(i)!='\n'){
                    if(data.at(i)!='\r')
                     str+=data.at(i);
                }else{
                     database[niterator]=str.toStdString();
                     str="";
                     ++niterator;
                }

            }
            databaseLength=niterator;
                    std::ofstream fout;
                    fout.open("log_scanner.txt", std::ios::app);
                    fout <<"signature base loaded."<< std::endl;
                    fout.close();

        }






public slots:
    void doWork(const QString &parameter) {
        QString param1;
         QString param2;
        if(scan(parameter.toStdString(),param1,param2)){
          emit virusFound("md5",param1,param2);
        }else if(heuristic){
            std::string param3="";
            if(scanHeuristic_c(parameter,param1,param3)){
                emit virusFound("euristic",param1,QString::fromStdString(param3));
            }
        }
        emit resultReady();
    }

signals:
    void resultReady();
    void virusFound(QString type,QString adress,QString name);
};






