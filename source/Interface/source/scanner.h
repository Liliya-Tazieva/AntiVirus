#ifndef SCANNER
#define SCANNER
#include "widget.h"
#include <QLabel>
#include <QString>
using namespace std;
class Scaner
{
public:
    QString directory;
    Scaner();
    Scaner(QString s)
    {
        directory = new QString;
        directory = s;
    }
    void Scan_Dir(QString directory)
    {
        QLabel d(directory);
        d.move(100, 100);
        d.show();
    }
    void Scan_All(bool t)
    {
        QLabel d("Scanned all!");
        d.move(100, 100);
        d.show();
    }
}
#endif // SCANNER

