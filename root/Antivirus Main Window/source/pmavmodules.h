#ifndef PMAVMODULES
#define PMAVMODULES

#endif // PMAVMODULES

#include <QApplication>
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <string>
#include <QDir>
#include <QStringList>
#include <fstream>
#include <iostream>
#include <stack>
#include <QThread>
#include <QObject>
#include  <QFile>
#include  <QTextStream>
#include <QDebug>
#include <QProcess>
#include <algorithm>











/*
object which is situated in Scanner and PassiveProtection modules.
for each module it must have a separate log file.



NOT WORKING AS STATED. MUST REFACTOR SO IT WILL WORK AS IS SAID BELOW
and so it will take all 3 string types in printing function




When programm starts and Antivirus is created, it creates output file stream(separate for each module) and you can write with writeToLog() function
*/

class Logger{
public:
    void writeToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;
    }
    void writeToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;
    }
    void writelnToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;
    }
    void writelnToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;
    }
    void writelnToLog(){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << std::endl;
    }
    Logger(){
        std::ofstream fout; fout.open("log_scanner.txt"); fout.close();
    }

};







/*
PassiveProtection class,
every Antivirus instance has one.

Implements all the passive protection features pointed in google docs.

If you are writing method that is common for both win8 and win10,
then create this method in PassiveProtection.
If (this method in win8 != this method in win10) then
create virtual method in PassiveProtection and implement it in PassiveProtection8 and PassiveProtection10 classes.
*/
class PassiveProtection{
public:
    void turnOnProtection(){
    }
    void turnOffProtection(){
    }
};



