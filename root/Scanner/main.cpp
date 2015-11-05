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



/*
object which is situated in Scanner and PassiveProtection objects.
for each module it must have a separate log file.



NOT WORKING AS STATED. MUST REFACTOR SO IT WILL WORK AS IS SAID BELOW
and so it will take all 3 string types in printing function




When programm starts and Antivirus is created, it creates output file stream(separate for each module) and you can write with writeToLog() function
*/

class Logger{
public:
    void writeToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;
    }
    void writeToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;
    }
    void writelnToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;
    }
    void writelnToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;
    }
    void writelnToLog(){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << std::endl;
    }
    Logger(){
        std::ofstream fout; fout.open("log_scanner.txt"); fout.close();
    }

};




/*
Scanner class,
every Antivirus instance has one.

Implements roaming through files and directories, scanning files.

If you are writing method that is common for both win8 and win10,
then create this method in Scanner.
If (this method in win8 != this method in win10) then
create virtual method in Scanner and implement it in Scanner8 and Scanner10 classes.
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

    void loadDB(){
        //there is endl sign at the end of file, so -1.
        QFile f("viruses.db");
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

    NEEDS TO BE REFACTORED HEAVILY

    */
    void scan(std::string s){

        //logger->writeToLog("Scanning:  ");
        //logger->writelnToLog(s);


                std::ifstream striim;
                striim.open(s, std::ios::binary);
                bool buf[20000];
                memset(buf, 0, 20000);
                striim.read((char*)&buf, 20000);
                striim.close();

                std::string buf2(40000, '0');

                for (int i = 0, k = 0; i < 20000; i++){
                    char high = buf[i] >> 4;
                    char low = buf[i] & 0x0f;


                    if (high <= 9)
                        high = high + 48;
                    else
                        high = high + 87;

                    if (low <= 9)
                        low = low + 48;
                    else
                        low = low + 87;
                    buf2.at(i+k) = high;
                    buf2.at(i+k+1) = low;
                    k++;

                 }
                for(long i=0;i<databaseLength;i++){
                    if (buf2.find(database[i]) != std::string::npos) {
                         qDebug()<<"Virus found!";
                         logger->writeToLog("suspicious file found at: ");
                         logger->writelnToLog(s);
                         logger->writeToLog("the name of virus is: ");
                         logger->writelnToLog(namebase[i]);
                         callVirusFoundWindow();
                    }
                   // qDebug()<<"------";
                   // qDebug()<<QString::fromStdString(database[i]);
                   // qDebug()<<QString::fromStdString(buf2).left(220);
                }




    }
    //void scan(char* s){}

    /*
    Traverses the given directory and all the subdirectories
    and applies scan() to all files that a found.

    */
    void traverseForScanning(const char* s){
        //QDir::rootPath(); --finds root


        /*
        code samples that were used before non-reqursive algorithm

        DO NOT TOUCH.



        QStringList file_list = start.entryList(QDir::Files);
        for (int i = 0; i < file_list.size(); ++i){
        currentString = st;
        currentString.append("/");
        currentString.append(file_list.at(i).toStdString());
        logger->writeToLog("Scanning:  ");
        logger->writelnToLog(currentString);
        scan(currentString);
        }

        QStringList  dir_list = start.entryList(QDir::AllDirs);

        for (int i = 0; i < dir_list.size(); ++i){
        if (dir_list.at(i) != "."&&dir_list.at(i) != ".."){
        currentString = st;
        currentString.append("/");
        currentString.append(dir_list.at(i).toStdString());
        logger->writeToLog(currentString);
        logger->writelnToLog(" is a directory");
        traverseForScanning(currentString.c_str());
        }
        }

        */


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
    /*
    A magical function that starts  scanning using multiprocessing.

    */
    void invokeScanning(){
        //firstly, we ask the program what number of threads we'd better use.
        //int idealThreadNumber = QThread::idealThreadCount();


    }



    void callVirusFoundWindow() {
        //QProcess process;
       // process.start( "C:/Qt/VirusDetected/WhatToDoWithVirus.exe" );
       // if( !process.waitForStarted() ) {
       //     return;
       // }

       // process.write( "Hello, world!" );
       // process.closeWriteChannel();

       //if( !process.waitForFinished() ) {
        //    return;
        //}

        //qDebug() << process.readAllStandardError();
        //qDebug() << process.readAllStandardOutput();
        QProcess *process = new QProcess();
        QString program = "WhatToDoWithVirus.exe";
        QString arg = "av";
        process->start(program, QStringList() << arg);

    }



    Scanner(){
        this->loadDB();

        //writeReadTest();
    }
};

class Scanner8 :public Scanner{
public:
    Scanner8(){
        logger = new Logger();
    }
};

class Scanner10 :public Scanner{
public:
    Scanner10(){
        logger = new Logger();
    }
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(argc>=2){
        Scanner* scanner;
        std::string s = QSysInfo::prettyProductName().toStdString();
        if (s == "Windows 8" || s == "Windows 8.1"){
            scanner =new Scanner8();
        }
        else if (s == "Windows 10"){
            scanner =new Scanner10();
        }
        scanner->logger->writeToLog("Scan started at: ");
        scanner->logger->writelnToLog(argv[1]);
        scanner->traverseForScanning(argv[1]);
        scanner->logger->writelnToLog("scanner_quit.");
    }else{
        Logger logger=Logger();
        logger.writelnToLog("error.");
        logger.writelnToLog("scanner_quit.");
    }
    return 0;
   // QObject::connect((QObject*)viewer.engine(),SIGNAL(quit()),&app,SLOT(quit()));
    //a.quit();
    //return a.exec();
}
