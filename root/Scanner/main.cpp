#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QString>
#include <fstream>
#include <QFile>
#include  <QTextStream>
#include  <QDebug>
#include  <Stack>
#include <QDir>
#include <QProcess>
#include <QCryptographicHash>



/*
for each module it must have a separate log file.

NOT WORKING AS STATED. MUST REFACTOR SO IT WILL WORK AS IS SAID BELOW
and so it will take all 3 string types in printing function



When programm starts, it creates output file stream once and you can write with writeToLog() function
*/

class Logger{
public:
    void writeToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;                 fout.close();
    }
    void writeToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;                 fout.close();
    }
    void writelnToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;    fout.close();
    }
    void writelnToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;    fout.close();
    }
    void writelnToLog(){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << std::endl;         fout.close();
    }
    Logger(){
        std::ofstream fout; fout.open("log_scanner.txt"); fout.close();
    }

};




/*
Implements roaming through files and directories, scanning files.
*/
class Scanner{
public:
    Logger* logger;
    std::string* database;
    std::string* namebase;
    long databaseLength=0;

    /*
    is quite self-explanatory.
        it loads in operative memory all the known virus signatures. //in database string array, namebase is names array
        we dont use file reading from base because it will slow the scanning greatly.
        really fast, makes me proud.
    */

    virtual void loadDB()=0;

    /*
    Scan is a function that can be applied to FILES ONLY.	directories' analog of scan is traverseForScanning function

    does signature search on a given file

    */
    virtual void scan(std::string s)=0;

    /*
    Traverses the given directory and all the subdirectories
    and applies scan() to all files that a found.

    */
    void traverseForScanning(const char* s){


        std::stack<std::string, std::list<std::string>> stack;
        std::string st = s;
        stack.push(st);
        while (stack.size() != 0){
            std::string st = stack.top();
            logger->writeToLog("Scanning directory: ");
            logger->writelnToLog(st);
            stack.pop();
            QDir start(st.c_str());
            start.setNameFilters(QStringList() << "*");
            std::string currentString;
            if (!start.exists())
            {
               logger->writelnToLog("error");
            }
            QStringList  dir_list = start.entryList(QDir::AllDirs);
            //qDebug()<<dir_list;
            for (int i = 0; i < dir_list.size(); ++i){
                if (dir_list.at(i) != "."&&dir_list.at(i) != ".."){
                    currentString = st;
                    currentString.append("/");
                    currentString.append(dir_list.at(i).toStdString());
                    stack.push(currentString);
                }
            }

            QStringList file_list = start.entryList(QDir::Files);
            for (int i = 0; i < file_list.size(); ++i){
                currentString = st;
                currentString.append("/");
                currentString.append(file_list.at(i).toStdString());
                scan(currentString);
            }


        }


    };


    void callVirusFoundWindow(std::string adress, std::string name) {
        QProcess *process = new QProcess();
        QString program = "WhatToDoWithVirus.exe";
        QString arg1 = QString::fromStdString(adress);
        QString arg2 = QString::fromStdString(name);
        process->start(program, QStringList() << arg1<<arg2);

    }




};






class Scanner_hex:public Scanner{
public:
    Scanner_hex(){
        logger= new Logger();
        this->loadDB();
    }
    /*
    is quite self-explanatory.
        it loads in operative memory all the known virus signatures. //in database string array, namebase is names array
        we dont use file reading from base because it will slow the scanning greatly.
        really fast, makes me proud.
    */

    virtual void loadDB(){
        //there is endl sign at the end of file, so -1.
        QFile f("viruses_hex.db");
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
                    // qDebug() <<  str;
                     long symbolPos=str.indexOf('=');
                     namebase[niterator]=str.left(symbolPos).toStdString();
                     database[niterator]=str.mid(symbolPos+1).toStdString();
                     str="";
                     ++niterator;
                }

            }
            databaseLength=niterator;
            logger->writelnToLog("Signature base loaded. ");
    }

    /*
    Scan is a function that can be applied to FILES ONLY.	directories' analog of scan is traverseForScanning function

    does signature search on a given file

    */
    virtual void scan(std::string s){

        //logger->writeToLog("Scanning:  ");
        //logger->writelnToLog(s);

        std::ifstream::pos_type size;
            char * memblock;
            Logger*logger=new Logger();
            std::ifstream file (s, std::ios::in|std::ios::binary|std::ios::ate);
            if (file.is_open()){
                size = file.tellg();
                if(size>20000)
                    size=20000;
                memblock = new char [size];
                file.seekg (0, std::ios::beg);
                file.read (memblock, size);
                file.close();
                //delete[] memblock;
             }
             else logger->writelnToLog("not found");

            char *buf2=new char[size*2+1];
            for (int i = 0, k = 0; i < size; i++){
                               char high = ((unsigned char)memblock[i]) >> 4;
                               char low = ((unsigned char)memblock[i]) & 0x0f;

                               //if(high<0)
                               //    high='-'; else
                               if (high <= 9)
                                   high = high + 48;
                               else
                                   high = high + 87;
                               //if(low<0)
                               //    low='-'; else
                               if (low <= 9)
                                   low = low + 48;
                               else
                                   low = low + 87;
                               buf2[i+k] = high;
                               buf2[i+k+1] = low;
                               k++;

                            }
            buf2[size*2]=0;



                long l=size*2;
                for(long i=0;i<databaseLength;i++){
                    bool containsAt0=true;
                    long elementLength=database[i].length();
                    long ii=0;
                    while((l>ii)&&(elementLength>ii)){
                        if(buf2[ii]!=database[i][ii])
                            containsAt0=false;
                        ii++;
                    }
                    if(containsAt0){
                        qDebug()<<"Virus found!";
                        logger->writeToLog("suspicious file found at: ");
                        logger->writelnToLog(s);
                        logger->writeToLog("the name of virus is: ");
                        logger->writelnToLog(namebase[i]);
                        callVirusFoundWindow(s,namebase[i]);
                    }




                    /*if (buf2.find(database[i]) != std::string::npos) {
                         qDebug()<<"Virus found!";
                         logger->writeToLog("suspicious file found at: ");
                         logger->writelnToLog(s);
                         logger->writeToLog("the name of virus is: ");
                         logger->writelnToLog(namebase[i]);
                         callVirusFoundWindow();
                    }*/
                   // qDebug()<<"------";
                   // qDebug()<<QString::fromStdString(database[i]);
                   // qDebug()<<QString::fromStdString(buf2).left(220);
                }




    }


};

class Scanner_md5:public Scanner{
public:
    Scanner_md5(){
        logger= new Logger();
        this->loadDB();
    }
    /*
    is quite self-explanatory.
        it loads in operative memory all the known virus signatures. //in database string array, namebase is names array
        we dont use file reading from base because it will slow the scanning greatly.
        really fast, makes me proud.
    */

    virtual void loadDB(){
        //there is endl sign at the end of file, so -1.
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
                    // qDebug() <<  str;
                    // long symbolPos=str.indexOf('=');
                     namebase[niterator]="virus";
                     database[niterator]=str.toStdString();
                     str="";
                     ++niterator;
                }

            }
            databaseLength=niterator;
            logger->writelnToLog("Signature base loaded. ");
    }

    /*
    Scan is a function that can be applied to FILES ONLY.	directories' analog of scan is traverseForScanning function

    does signature search on a given file

    */
    virtual void scan(std::string s){

        //logger->writeToLog("Scanning:  ");
        //logger->writelnToLog(s);

        QString fileName= QString::fromStdString(s);
        QCryptographicHash crypto(QCryptographicHash::Md5);
        QFile file(fileName);
        file.open(QFile::ReadOnly);
        while(!file.atEnd()){
          crypto.addData(file.read(8192));
        }
        QByteArray buf2 = crypto.result().toHex();
       // for(int i=0;i<hash.length();i++)
        //logger->writelnToLog(buf2);

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
                        logger->writeToLog("suspicious file found at: ");
                        logger->writelnToLog(s);
                        logger->writeToLog("the name of virus is: ");
                        logger->writelnToLog(namebase[i]);
                        logger->writeToLog("the md5 hash of virus is: ");
                         logger->writelnToLog(database[i]);

                        callVirusFoundWindow(s,namebase[i]);
                    }
                }




    }


};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(argc>=3){
        Scanner* scanner;
        //std::string s = QSysInfo::prettyProductName().toStdString();
        //if (s == "Windows 8" || s == "Windows 8.1"){
        //    scanner =new Scanner8();
        //}
        //else if (s == "Windows 10"){
        //    scanner =new Scanner10();
        //}
        if (strcmp(argv[2],"hex")==0){
            scanner=new Scanner_hex();
        }else if (strcmp(argv[2],"md5")==0)
            scanner=new Scanner_md5();
        scanner->logger->writeToLog(argv[2]);
        scanner->logger->writelnToLog(" scanning algorithm.");
        scanner->logger->writeToLog("Scan started at: ");
        scanner->logger->writelnToLog(argv[1]);
        scanner->traverseForScanning(argv[1]);
        scanner->logger->writelnToLog("scanner_quit.");
    }else{
        Logger logger=Logger();
        logger.writelnToLog("not enough arguments.");
        logger.writelnToLog("scanner_quit.");
    }
    return 0;
}
