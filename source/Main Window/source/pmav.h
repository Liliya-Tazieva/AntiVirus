#ifndef PMAV_H
#define PMAV_H

#include <QtWidgets/QMainWindow>
#include "ui_pmav.h"

class pmav : public QMainWindow
{
    Q_OBJECT

public:
    pmav(QWidget *parent = 0);
    ~pmav();

private:
    Ui::pmavClass ui;
};

#endif // PMAV_H
