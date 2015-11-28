#ifndef WHATTODOWINDOW_H
#define WHATTODOWINDOW_H
#include <QString>
#include <QWidget>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class WhatToDoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit WhatToDoWindow(QWidget *parent = 0);

    //Initializing all parameters, that are used in WhatToDoWithVirus.cpp
    QPushButton *delbut;
    QPushButton *ignbut;
    QPushButton *quarbut;
    QLabel *question;
    QHBoxLayout *layout1;
    QVBoxLayout *layout2;
    QLabel *adress;
    QLabel *name;
    QString*addr;

    char* addr0i;

    //Functions
    void put_adress_and_name_in(char* s1, char* s2);
    void put_adress_and_name_in_susp(char* s1, char* s2);

    //Initializing signals and slots, to make buttons do stuff
signals:
    void signal1(bool);
public slots:
    void delete_it();
    void ignore_it();
    void quarantine_it();
};

#endif // WHATTODOWINDOW_H
