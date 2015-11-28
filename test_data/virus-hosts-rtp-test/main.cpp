#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <qdir>
#include <qstring>
int main(int argc, char *argv[])
{   QString s=QDir::rootPath();
    std::string s0 = QSysInfo::prettyProductName().toStdString();
        s.append("Windows\\System32\\drivers\\etc\\hosts");
    std::ofstream fout;
    fout.open(s.toStdString(), std::ios::app);
    fout <<"#appended~~"<< std::endl;
    fout.close();

    QCoreApplication a(argc, argv);

    return a.exec();
}

