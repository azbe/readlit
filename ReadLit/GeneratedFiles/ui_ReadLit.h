/********************************************************************************
** Form generated from reading UI file 'ReadLit.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READLIT_H
#define UI_READLIT_H

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

class Ui_ReadLitClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ReadLitClass)
    {
        if (ReadLitClass->objectName().isEmpty())
            ReadLitClass->setObjectName(QStringLiteral("ReadLitClass"));
        ReadLitClass->resize(600, 400);
        menuBar = new QMenuBar(ReadLitClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ReadLitClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ReadLitClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ReadLitClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ReadLitClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ReadLitClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ReadLitClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ReadLitClass->setStatusBar(statusBar);

        retranslateUi(ReadLitClass);

        QMetaObject::connectSlotsByName(ReadLitClass);
    } // setupUi

    void retranslateUi(QMainWindow *ReadLitClass)
    {
        ReadLitClass->setWindowTitle(QApplication::translate("ReadLitClass", "ReadLit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReadLitClass: public Ui_ReadLitClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READLIT_H
