/********************************************************************************
** Form generated from reading UI file 'pmav2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PMAV2_H
#define UI_PMAV2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pmav2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pmav2Class)
    {
        if (pmav2Class->objectName().isEmpty())
            pmav2Class->setObjectName(QStringLiteral("pmav2Class"));
        pmav2Class->resize(600, 400);
        menuBar = new QMenuBar(pmav2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        pmav2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pmav2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        pmav2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(pmav2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pmav2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(pmav2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        pmav2Class->setStatusBar(statusBar);

        retranslateUi(pmav2Class);

        QMetaObject::connectSlotsByName(pmav2Class);
    } // setupUi

    void retranslateUi(QMainWindow *pmav2Class)
    {
        pmav2Class->setWindowTitle(QApplication::translate("pmav2Class", "pmav2", 0));
    } // retranslateUi

};

namespace Ui {
    class pmav2Class: public Ui_pmav2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PMAV2_H
