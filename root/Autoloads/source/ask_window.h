#ifndef ASK_WINDOW_H
#define ASK_WINDOW_H

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

/*
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter) {
        QString result;
        qDebug()<<"hello";
        std::ofstream fout; fout.open("log_rtp1.txt", std::ios::app); fout <<"ping"<< std::endl;         fout.close();
        emit resultReady(result);
    }

signals:
    void resultReady(const QString &result);
};
*/

class ask_window : public QWidget
{
    Q_OBJECT
public:
    QVector<QStringList> c;
   /* QThread workerThread;*/
    explicit ask_window(QWidget *parent = 0);
    QTimer *timer;
    QLabel *situation;
    QLabel *question;
    QLabel *something;
    QPushButton *yes_but;
    QPushButton *no_but;
    QHBoxLayout *lo1;
    QVBoxLayout *lo2;

    void activate();

public slots:
    void invoke();
    void yes();
    void no();
   /* void handleResults(const QString &);
signals:
    void operate(const QString &);*/

};

#endif // ASK_WINDOW_H
