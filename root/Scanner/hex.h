#ifndef HEX
#define HEX

#endif // HEX

#include "scanner.h"


class Scanner_hex:public Scanner{
    /*
    is quite self-explanatory.
        it loads in operative memory all the known virus signatures. //in database string array, namebase is names array
        we dont use file reading from base because it will slow the scanning greatly.
        really fast, makes me proud.
    */

    void loadDB(){
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
                    bool containsAt0=true;
                    long elementLength=database[i].length();
                    long ii=0;
                    while((40000>ii)&&(elementLength>ii)){
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
};
