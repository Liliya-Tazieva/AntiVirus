#include "pmav2.h"
#include <QtWidgets/QApplication>
#include <string>
#include <QPushButton>
class antivirus{
	virtual void scan() = 0;
	virtual void toogleDefence() = 0;
};
class antivirus8 :public antivirus{
	virtual void scan(){

	}
	virtual void toogleDefence(){

	}
};
class antivirus10 :public antivirus{
	virtual void scan(){

	}
	virtual void toogleDefence(){

	}
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*
	std::string s = QSysInfo::productType() .toStdString();
	QPushButton button(s.c_str());
	button.show();*/

	std::string s = QSysInfo::prettyProductName().toStdString();
	QPushButton button0(s.c_str());
	button0.show();
	/*pmav2 w;

	w.show();*/
	return a.exec();
}
