#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget.h>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:

	QTabWidget *mainTabs;
	QLayout	*mainLayout;
};

#endif //MAINWINDOW_H