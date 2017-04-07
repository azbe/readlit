#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget.h>

#include "SubtabBooks.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	const int BASE_WIDTH = 800;
	const int BASE_HEIGHT = 600;

	QTabWidget *mainTabs;
	QLayout	*mainLayout;
};

#endif //MAINWINDOW_H