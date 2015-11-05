#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include <QLineEdit>
#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include "pmavmodules.h"





class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    //Initializing all parameters, that are used in window.cpp
    QFont *font_kind4;
    QLabel *ask_dir;
    QLineEdit *line;
    QLabel *funny_joke;
    QPushButton *scanit;
    QCheckBox *passive_def;
    QPushButton *scanall;
    QVBoxLayout *layout1;
    QVBoxLayout *layout2;
    QHBoxLayout *layout3;
    QVBoxLayout *layout4;
    QString s;
    Antivirus* antivirus;
    QLabel *SW;
    QTimer *timer;
    QLabel *waiting_window;
    //Initializing signals and slots, to make buttons do stuff
signals:
    void signal1(bool);
private slots:
    void wait_window1();
    void wait_window2();
    void close_the_window();
    void close_waiting_window1();
    void close_waiting_window2();
public slots:
    void scan_all();
    void scan_dir();
    void pass_def();
};

#endif // WINDOW_H
