#ifndef ASK_WINDOW_H
#define ASK_WINDOW_H
#include <registry.h>
#include <QWidget>
#include <QTimer>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QStringList>
#include <QSettings>
#include <QVector>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileSystemWatcher>
#include <ctime>


class ask_window : public QWidget
{
    Q_OBJECT
public:
    QVector<QList<RegistryParameter>> c_r;
    explicit ask_window(QWidget *parent = 0);
    QTimer *timer;
    QLabel *situation;
    QLabel *question;
    QLabel *something;
    QPushButton *yes_but;
    QPushButton *no_but;
    QHBoxLayout *lo1;
    QVBoxLayout *lo2;
    QString s0;
    QString s1;
    QString s2;
    QString mode;
    QString hosts;

    QList<QStringList> autoruns_folders_contents;
    QStringList autoruns_folders;

    QFileSystemWatcher *mon_hosts;
    QFileSystemWatcher *mon_autoruns;

    RegistryParameter reserved_registry_parameter_changed;
    int reserved_registry_parameter_changed_int;

    bool reserved_dont_track_hosts=false;
    void activate();


    void set_window(QString m,QString param){
        mode=m;
        if(mode=="registry_changed"){
            s0="Attempt to add new program to autorun has been detected";
            s1=param;
            s2="Allow it?";
        }
        if(mode=="hosts_changed"){
            s0="An attempt to change 'hosts' file was detected.";
            s1="Do you want to allow the changes?";
            s2="";
        }
        if(mode=="autoruns_folder_changed"){
            s0="An attempt to change autoruns folder was detected.";
            s1="Do you want to allow the changes?";
            s2="";
        }
        situation->setText(s0);
        something->setText(s1);
        question->setText(s2);

    }

    void getAutorunsFolders(QStringList&,QList<QStringList>& );
public slots:
    void invoke();
    void yes();
    void no();
    void foo1(QString){


            std::ofstream fout;
            fout.open("log_real-time_protection.txt", std::ios::app);
            time_t t = time(0);   // get time now
            struct tm * now = localtime( & t );
            fout <<now->tm_hour  << ":" <<now->tm_min  << ":" <<now->tm_sec<<"  ";
            fout << "An attempt to change hosts file was noticed!";
            fout.close();

            set_window(QString("hosts_changed"),QString(""));
            show();
            qDebug()<<"hosts_changed";

    };

    void foo2(QString){
        QStringList folders=QStringList();
        QList<QStringList> folders_contents=QList<QStringList>();
        getAutorunsFolders(folders,folders_contents);

        for(int i=0;i<autoruns_folders_contents.length();i++)
             for(int i0=0;i0<autoruns_folders_contents.at(i).length();i0++)
               for(int ii0=0;ii0<folders_contents.at(i).length();ii0++)
                 if(autoruns_folders_contents.at(i).at(i0)==folders_contents.at(i).at(ii0))
                     folders_contents[i].removeAt(ii0);

        for(int i=folders_contents.length()-1;i>=0;i--)
            if(folders_contents[i].isEmpty())folders_contents.removeAt(i);

        if(folders_contents.length()>0){

            std::ofstream fout;
            fout.open("log_real-time_protection.txt", std::ios::app);
            time_t t = time(0);   // get time now
            struct tm * now = localtime( & t );
            fout <<now->tm_hour  << ":" <<now->tm_min  << ":" <<now->tm_sec<<"  ";
            fout << "An attempt to change autoruns folders was noticed!";
            fout.close();

            qDebug()<<folders_contents;
            set_window(QString("autoruns_folder_changed"),QString(""));
            show();
        }else{
            getAutorunsFolders(autoruns_folders,autoruns_folders_contents);
        }
            qDebug()<<"autoruns_folder_changed";
            qDebug()<<folders_contents;

    };
};

#endif // ASK_WINDOW_H
