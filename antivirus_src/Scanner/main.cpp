#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <QDir>
#include <vector>
#include <QString>
#include <QFile>
#include  <QTextStream>
#include  <QDebug>
#include  <Stack>
#include <QCryptographicHash>
#include <QProcess>
#include <QTextCodec>
#include "traverser.h"
#include <ctime>


std::ofstream fout;

/*
for each module it must have a separate log file.

NOT WORKING AS STATED. MUST REFACTOR SO IT WILL WORK AS IS SAID BELOW
and so it will take all 3 string types in printing function

When programm starts, it creates output file stream once and you can write with writeToLog() function
*/
std::string get_time(){

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    std::string time=std::to_string(now->tm_hour)+":"+std::to_string(now->tm_min)+":"+std::to_string(now->tm_sec)+" ";
    return time;
}
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
class Scanner:public Heuristicable{
public:
    bool heuristic=false;
    Logger* logger;
    std::string* database;
    std::string* namebase;
    long long databaseLength=0;


    Scanner(bool h){
        logger= new Logger();
        this->loadDB();
        heuristic=h;
        if(heuristic){
            QFile f("heuristic.db");
            QString data;
                if (f.open(QFile::ReadOnly | QFile::Text)){
                    QTextStream in(&f);
                    data=in.readAll();
                }
            this->parseHeuristicDB(data);
        }
    }

    /*
    is quite self-explanatory.
        it loads in operative memory all the known virus signatures. //in database string array, namebase is names array
        we dont use file reading from base because it will slow the scanning greatly.
        really fast, makes me proud.
    */

    void loadDB(){
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
    if finds something, then it opens whattodowithvirus.exe window, if not, does nothing
    requires the database to be loaded before to work correctly

    if founds virus, returns true and changes param1 and param2 to adress and name of the virus
    else returns false
    */
    bool scan(QString s,QString &param1,std::string &param2){
        bool virusFound=false;
        QString fileName= s;
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
                        logger->writeToLog(get_time()+"suspicious file found at: ");
                        logger->writelnToLog(s.toStdString());
                        logger->writeToLog("the name of virus is: ");
                        logger->writelnToLog(namebase[i]);
                        logger->writeToLog("the md5 hash of virus is: ");
                         logger->writelnToLog(database[i]);
                         QString gg=QString::number(i).prepend('#');
                        param1=s;
                        param2=gg.toStdString();
                        return true;
                    }
                }
                return false;
    }

    /*
    Traverses the given directory and all the subdirectories
    and applies scanning functions to all files that a found.
    */
    void traverseForScanning(const char* s){


        std::stack< QString, std::list<QString>> stack;
        QString st = QString::fromLocal8Bit(s);
        stack.push(st);
        while (stack.size() != 0){
            QString st = stack.top();
            //logger->writeToLog("Scanning directory: ");
            //logger->writelnToLog(st.toStdString());
            stack.pop();
            QDir start(st);
            start.setNameFilters(QStringList() << "*");
            QString currentString;
            if (!start.exists())
            {
               logger->writelnToLog("error");
            }
            QStringList  dir_list = start.entryList(QDir::AllDirs);
            for (int i = 0; i < dir_list.size(); ++i){
                if (dir_list.at(i) != "."&&dir_list.at(i) != ".."){
                    currentString = st;
                    currentString.append("\\");
                    currentString.append(dir_list.at(i));
                    stack.push(currentString);
                }
            }

            QStringList filters;
              filters << "*.exe" << "*.dll" << "*.cpt"<< "*.jpg"<< "*.jpeg"
                      << "*.dbf"<< "*.iso"<< "*.tga"<< "*.bat"<< "*cil"<<"*.js"<<"*.gif"<<"*.bmp"<<"*.html"
                      <<"*.htm"<<"*.ax"<<"*.cpl"<<"*.acm"<<"*.drv"<<"*.efi"<<"*.mui"<<"*.ocx"<<"*.scr"<<"*.sys"<<"*.tsp"
                       << "*.doc"<< "*.docx"<< "*.xls"<< "*.xlsx"<< "*ppt"<<"*.pptx"<<"*.odt"<<"*.ods"<<"*.odp" ;
            start.setNameFilters(filters);

            QStringList file_list = start.entryList(QDir::Files);
            for (int i = 0; i < file_list.size(); ++i){
                currentString = st;
                currentString.append("\\");
                currentString.append(file_list.at(i));
                QString param1="";
                std::string param2="";
                bool virusFound=scan(currentString,param1,param2);
                if(virusFound){
                    callVirusFoundWindow("md5",param1,param2);
                }else if(heuristic){
                    virusFound=scanHeuristic_c(currentString,param1,param2);
                    if(virusFound)
                        callVirusFoundWindow("euristic",param1,param2);//not a misstape, "euristic" is okay
                }
            }


        }


    };

    void callVirusFoundWindow(QString type, QString adress, std::string name) {
        QProcess *process = new QProcess();
        QString program = "WhatToDoWithVirus.exe";
        QString arg1 = adress;
        QString arg2 = QString::fromStdString(name);
        process->start(program, QStringList() <<type <<arg1<<arg2);

    }




};
int countFiles(MainWindow* w,QString start){
        int filecount=0;
        w->stack.push(start);
        while (w->stack.size()!=0&&filecount<100){
            QString st =  w->stack.top();
            w->stack.pop();
            QDir start(st);
            start.setNameFilters(QStringList() << "*");
            QString currentString;
            QStringList  dir_list = start.entryList(QDir::AllDirs);
            for (int i = 0; i < dir_list.size(); ++i){
                if (dir_list.at(i) != "."&&dir_list.at(i) != ".."){
                    currentString = st;
                    currentString.append("\\");
                    currentString.append(dir_list.at(i));
                     w->stack.push(currentString);
                }
            }

            QStringList filters;
              filters << "*.exe" << "*.dll" << "*.cpt"<< "*.jpg"<< "*.jpeg"
                      << "*.dbf"<< "*.iso"<< "*.tga"<< "*.bat"<< "*cil"<<"*.js"<<"*.gif"<<"*.bmp"<<"*.html"
                      <<"*.htm"<<"*.ax"<<"*.cpl"<<"*.acm"<<"*.drv"<<"*.efi"<<"*.mui"<<"*.ocx"<<"*.scr"<<"*.sys"<<"*.tsp"
                       << "*.doc"<< "*.docx"<< "*.xls"<< "*.xlsx"<< "*ppt"<<"*.pptx"<<"*.odt"<<"*.ods"<<"*.odp" ;
            start.setNameFilters(filters);

            QStringList file_list = start.entryList(QDir::Files);
            filecount+=file_list.size();
        }
    while(!w->stack.empty())
         w->stack.pop();
    return filecount;
}

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;

        if(argc>=4){

            for(int i=0;i<strlen(argv[1]);i++)
                if(argv[1][i]=='/')
                    argv[1][i]='\\';
            bool ignoreUserChoice=false;

           //checking if it is one file
           //Determining algorithm
           QString g=QString::fromLocal8Bit(argv[1]);
           QFile f(g);
           if (f.open(QIODevice::ReadOnly)){
               Scanner* scanner;
               if(strcmp(argv[2],"md5")==0){
                   scanner=new Scanner(false);
               }else{
                   scanner=new Scanner(true);
               }
               scanner->logger->writeToLog(argv[2]);
               scanner->logger->writelnToLog(" scanning algorithm.");
               scanner->logger->writeToLog("resource consumption: ");
               scanner->logger->writelnToLog(argv[3]);
               scanner->logger->writeToLog(get_time()+"It is a file: ");
               scanner->logger->writelnToLog(g.toStdString());
               QString param1="";
               std::string param2="";
               bool virusFound=scanner->scan(g,param1,param2);
               if(virusFound){
                   scanner->callVirusFoundWindow("md5",param1,param2);
               }else if(scanner->heuristic){
                   virusFound=scanner->scanHeuristic_c(g,param1,param2);
                   if(virusFound)
                       scanner->callVirusFoundWindow("euristic",param1,param2);//not a misstape, "euristic" is okay
               }
               scanner->logger->writelnToLog(get_time()+"scanner_quit.");
               return 0;
           }else{
               //its not a single file, so we are checking if our user ade a proper choice
               if(countFiles(&w,g)<100)
                   ignoreUserChoice=true;
           }


            if((strcmp(argv[3],"Low")==0)||ignoreUserChoice){
                Scanner* scanner;
                if(strcmp(argv[2],"md5")==0){
                    scanner=new Scanner(false);
                }else{
                    scanner=new Scanner(true);
                }
                scanner->logger->writeToLog(argv[2]);
                scanner->logger->writelnToLog(" scanning algorithm.");
                scanner->logger->writeToLog("resource consumption: ");
                scanner->logger->writelnToLog("Low");
                scanner->logger->writeToLog(get_time()+"Scan started at: ");
                scanner->logger->writelnToLog(argv[1]);
                scanner->traverseForScanning(argv[1]);
                scanner->logger->writelnToLog(get_time()+"scanner_quit.");
                return 0;
            }else{
                a.connect(&w, SIGNAL(quit_()), &a, SLOT(quit()));

                Traverser *traverser=new Traverser();
                a.connect(traverser, SIGNAL(listReady()),&w,SLOT(handleResults()));
                a.connect(&w,SIGNAL(giveList()),traverser, SLOT(giveMore()));

                if (strcmp(argv[2],"md5+heuristic")==0)
                 w.heuristic=true;


                 w.activate();

                 std::ofstream fout;
                 fout.open("log_scanner.txt");
                 fout <<argv[2];
                 fout <<" scanning algorithm."<<std::endl;
                 fout<<"resource consumption: ";
                 fout<<argv[3]<<std::endl;
                 fout <<get_time()+"Scan started at: ";
                 std::string stds=std::string(argv[1]);
                 fout <<stds<<std::endl;

                  QTextCodec *codec = QTextCodec::codecForName("UTF8");

                  QByteArray ba(stds.c_str());                  // Convert to QByteArray
                  QString msg = codec->toUnicode(ba);          // Qt magic !!!


                 traverser->initTraversing(QString::fromLocal8Bit(argv[1]),&w);

                 traverser->giveMore();

                 fout.close();

                 return a.exec();

            }
        }else{
            Logger logger=Logger();
            logger.writelnToLog(get_time()+"not enough arguments.");
            logger.writelnToLog(get_time()+"scanner_quit.");

            return 0;
        }

}


