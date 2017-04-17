#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget>

#include "src/Database.h"

class MainWindow : public QWidget
{
	Q_OBJECT

    public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

    private:

	QTabWidget *mainTabs;
    QLayout	*mainLayout;

    DataBase database;
};

#endif //MAINWINDOW_H
