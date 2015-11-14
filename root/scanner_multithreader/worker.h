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

class Worker : public QObject
{
    Q_OBJECT
public:


    std::string* database;
    std::string* namebase;
    long databaseLength=0;





    virtual void scan(std::string s)=0;
    virtual void loadDB()=0;

public slots:
    void doWork(const QString &parameter) {
        scan(parameter.toStdString());
       // qDebug()<<parameter;
       // qDebug()<<QThread::currentThread();
        emit resultReady();
    }

signals:
    void resultReady();
    void virusFound(QString adress,QString name);
};

class Worker_md5:public Worker{
    virtual void scan(std::string s){

       // qDebug()<<QString::fromStdString(s);
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

                            std::ofstream fout;
                            fout.open("log_scanner.txt", std::ios::app);
                            fout << "suspicious file found at: ";
                            fout <<s<< std::endl;
                            fout << "the name of virus is: ";
                            fout <<'#'<<i<< std::endl;
                            fout << "the md5 hash of virus is: ";
                            fout <<database[i]<< std::endl;

                           emit virusFound(QString::fromStdString(s),QString::number(i).prepend('#'));
                       // callVirusFoundWindow(s,namebase[i]);
                    }
                }




    }





    virtual void loadDB(){

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
         //   logger->writelnToLog("Signature base loaded. ");
                qDebug()<<databaseLength;
                    std::ofstream fout;
                    fout.open("log_scanner.txt", std::ios::app);
                    fout <<"signature base loaded."<< std::endl;
                    fout.close();

        }

};

class Worker_hex:public Worker{

    virtual void loadDB(){
        std::ofstream fout;
        fout.open("log_scanner.txt", std::ios::app);


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
             qDebug()<<databaseLength;
            fout <<"signature base loaded."<< std::endl;
            fout.close();
    }


    virtual void scan(std::string s){
        std::ofstream fout;
        fout.open("log_scanner.txt", std::ios::app);

        std::ifstream::pos_type size;
            char * memblock;
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
             else fout <<"not found!"<< std::endl;

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
               if(l<database[i].length()){
                   containsAt0=false;
                   continue;
               }
               long elementLength=database[i].length();
               long ii=0;
               while((l>ii)&&(elementLength>ii)){
                   if(buf2[ii]!=database[i][ii])
                       containsAt0=false;
                   ii++;
               }

                    if(containsAt0){
                        qDebug()<<"Virus found!";
                        fout << "suspicious file found at: ";
                        fout <<s<< std::endl;
                        fout << "the name of virus is: ";
                        fout <<namebase[i]<< std::endl;
                        emit virusFound(QString::fromStdString(s),QString::fromStdString(namebase[i]));
                       // callVirusFoundWindow(s,namebase[i]);
                    }



                }
        fout.close();
    }
};

