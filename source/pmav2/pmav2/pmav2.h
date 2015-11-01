#ifndef PMAV2_H
#define PMAV2_H

#include <QtWidgets/QMainWindow>
#include "ui_pmav2.h"

class pmav2 : public QMainWindow
{
	Q_OBJECT

public:
	pmav2(QWidget *parent = 0);
	~pmav2();

private:
	Ui::pmav2Class ui;
};

#endif // PMAV2_H
