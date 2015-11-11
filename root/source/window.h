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
    QProcess *process;
    QProcess *process_rtp;

    //not using antivirus class anymore: Antivirus* antivirus;

    //Initializing signals and slots, to make buttons do stuff
signals:
    void signal1(bool);
public slots:
    void scan_all();
    void scan_dir();
    void pass_def();
    void on_scanner_finished(int x0, QProcess::ExitStatus x1);

    void on_rtp_finished(int x0, QProcess::ExitStatus x1);
};

#endif // WINDOW_H
