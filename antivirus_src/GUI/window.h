#ifndef WINDOW_H
#define WINDOW_H
#include <QCoreApplication>
#include <QDir>
#include <QComboBox>
#include <QWidget>
#include <QLineEdit>
#include "window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include "pmavmodules.h"
#include <QProcess>
#include <QFileDialog>
#include <QDialog>
#include <QNetworkReply>




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
    QHBoxLayout *layout0;
    QPushButton *scanall;
    QVBoxLayout *layout1;
    QVBoxLayout *layout2;
    QHBoxLayout *layout3;
    QString s;
    QProcess *process;
    QProcess *process_rtp;
    QComboBox *box1;
    QComboBox *box2;
    QLabel *lb1;
    QLabel *lb2;
    QLabel *link;
    QPushButton *choose;
    QFileDialog *explorer;
    QDialog *file_or_directory;
    QLabel *what;
    QPushButton *fi;
    QPushButton *fo;

    void disable_all();
    void requestVersion();

    //Initializing signals and slots, to make buttons do stuff
public slots:
    void scan_all();
    void scan_dir();
    void pass_def();
    void link_clicked(QString);
    void choosing_file();
    void explorer_creator1();
    void explorer_creator2();
    void on_scanner_finished(int x0, QProcess::ExitStatus x1);
    void requestReceived(QNetworkReply* reply);
    void on_rtp_finished(int x0, QProcess::ExitStatus x1);
};

#endif // WINDOW_H
