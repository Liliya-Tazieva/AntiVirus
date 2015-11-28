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

    QFileSystemWatcher *mon_hosts;

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
        situation->setText(s0);
        something->setText(s1);
        question->setText(s2);

    }

public slots:
    void invoke();
    void yes();
    void no();
    void foo1(QString){

            set_window(QString("hosts_changed"),QString(""));
            show();
            qDebug()<<"hosts_changed";

    };
};

#endif // ASK_WINDOW_H
