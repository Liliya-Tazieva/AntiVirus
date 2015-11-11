#include "whattodowindow.h"
#include <QLabel>
#include <QString>
#include <QFont>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <iostream>
#include <fstream>


class Logger{
public:
    void writeToLog(const char* s){
        std::ofstream fout; fout.open("log_quarantinner.txt", std::ios::app); fout << s;                 fout.close();
    }
    void writeToLog(std::string s){
        std::ofstream fout; fout.open("log_quarantinner.txt", std::ios::app); fout << s;                 fout.close();
    }
    void writelnToLog(std::string s){
        std::ofstream fout; fout.open("log_quarantinner.txt", std::ios::app); fout << s << std::endl;    fout.close();
    }
    void writelnToLog(const char* s){
        std::ofstream fout; fout.open("log_quarantinner.txt", std::ios::app); fout << s << std::endl;    fout.close();
    }
    void writelnToLog(){
        std::ofstream fout; fout.open("log_quarantinner.txt", std::ios::app); fout << std::endl;         fout.close();
    }
    Logger(){
        std::ofstream fout; fout.open("log_quarantinner.txt"); fout.close();
    }

};

void quarantine(char* s){


    // setlocale(LC_ALL,"Russian");
    std::ifstream::pos_type size;
        char * memblock;
        Logger*logger=new Logger();
        std::ifstream file;
        file.open(s, std::ios::in|std::ios::binary|std::ios::ate);
        if (file.is_open()){
            size = file.tellg();
            //if(size>20000)
             //   size=20000;
            memblock = new char [size];
            file.seekg (0, std::ios::beg);
            file.read (memblock, size);
            file.close();
            //delete[] memblock;
         }
         else {
            logger->writeToLog(s);
            logger->writelnToLog(" not found");
        }
        char *buf2=new char[size*2+1];
        for (int i = 0, k = 0; i < size; i++){
                           char high = memblock[i] >> 4;
                           char low = memblock[i] & 0x0f;

                           buf2[i+k] = high+87;
                           buf2[i+k+1] = low+87;
                           k++;

                        }
        buf2[size*2]=0;

        std::string s0=std::string(s);

        size_t index = 0;
        while (index!=-1) {
             index = s0.find('\\');
             if(index!=-1)
             s0.replace(index, 1, "/");
        }




        s0=s0.substr(s0.rfind("/")+1);
        s0="quarantine/"+s0+".quar";

        QDir().mkdir("quarantine");

        int ii=0;
        int cc=0;
        while(s[ii]!=0){
            if(s[ii]=='\\'||s[ii]=='/')
            cc=ii;
            ii++;
        }

        int sij=0;
        while(sij+cc!=ii)
            sij++;
        char* charname=new char[sij+5+10+1];
       // insert(ch)
       // ii=0;
        charname[0]='q';  //я устал и хочу спать
        charname[1]='u';
        charname[2]='a';
        charname[3]='r';
        charname[4]='a';
        charname[5]='n';
        charname[6]='t';
        charname[7]='i';
        charname[8]='n';
        charname[9]='e';
        charname[10]='/';
        int jj=0;
        while(cc<ii){
            charname[jj+11]=s[cc+1];
            cc++;
            jj++;
        }
        charname[11+sij-1]='.';
        charname[11+sij-1+1]='q';
        charname[11+sij-1+2]='u';
        charname[11+sij-1+3]='a';
        charname[11+sij-1+4]='r';
        charname[sij+15]=0;

        logger->writelnToLog(charname);
        QString filename=QString::fromLocal8Bit(charname);
        QFile filew( filename );
        if ( filew.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &filew );
            stream << QString::fromStdString(buf2);
        }

    logger->writelnToLog("quarantinner_end.");

}
WhatToDoWindow::WhatToDoWindow(QWidget *parent) : QWidget(parent)
{
    //Font kind in the window
    QFont font_kind1("Calibri", 30);
    QFont font_kind2("Calibri", 23);

    //Virus detected, asking what to do line
    question = new QLabel("What to do now?");
    question->setFont(font_kind1);

    //"Delete it?" button
    delbut = new QPushButton("&Delete");
    delbut->setFont(font_kind2);

    //"Ignore it?" button
    ignbut = new QPushButton("&Ignore");
    ignbut->setFont(font_kind2);

    //"Quarantine it?" button
    quarbut = new QPushButton("&Quarantine");
    quarbut->setFont(font_kind2);

    //LayOut
    layout1 = new QHBoxLayout;
    layout1->addWidget(delbut);
    layout1->addWidget(ignbut);
    layout1->addWidget(quarbut);
    layout2 = new QVBoxLayout;

    //Window's head name and other features
    setWindowTitle("Virus detector");
    setLayout(layout2);

    //Signal-slot connection
    connect(delbut,SIGNAL(clicked()),this,SLOT(delete_it()),Qt::DirectConnection);
    connect(ignbut,SIGNAL(clicked()),this,SLOT(ignore_it()),Qt::DirectConnection);
    connect(quarbut,SIGNAL(clicked()),this,SLOT(quarantine_it()),Qt::DirectConnection);

}
//adding type of virus name and adress of file, where it has been located
void WhatToDoWindow::put_adress_and_name_in(char *s1, char *s2)
{
    QString s = QString::fromLocal8Bit(s1,-1);
    //Logger* ff=new Logger();
    adress = new QLabel("in the file " + s);
    addr=new QString(s);
    //ff->writeToLog("111");
    strcpy(addr0i,s1);
    s = QString::fromLocal8Bit(s2,-1);
    name = new QLabel("Virus "+s+" has been detected");
    QFont f("Calibri", 30);
    adress->setFont(f);
    name->setFont(f);
}


void WhatToDoWindow::delete_it()
{
    std::string x=addr->toStdString();  //какой-то дикий костыль, но по-другому чет не взлетело
    QFile del(QString::fromStdString(x));
    del.remove();
    /* Можно будет продумать концепцию всплывающих окон при удалении, но они,
      наверное, не вписываются в архитектуру с процессами, так что я пока просто оставлю место*/
    this->close();
}

void WhatToDoWindow::ignore_it()
{
    /* Можно будет продумать концепцию всплывающих окон при удалении, но они,
      наверное, не вписываются в архитектуру с процессами, так что я пока просто оставлю место*/
    this->close();
}

void WhatToDoWindow::quarantine_it()
{
    quarantine(addr0i);

    std::string x=addr->toStdString();  //какой-то дикий костыль, но по-другому чет не взлетело
    QFile del(QString::fromStdString(x));
    del.remove();
    /* Можно будет продумать концепцию всплывающих окон при удалении, но они,
      наверное, не вписываются в архитектуру с процессами, так что я пока просто оставлю место*/
    this->close();
}

