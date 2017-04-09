#include <stdlib.h>
#include <iostream>

#include <QApplication>
#include <QWidget>

#include "MainWindow.h"

#define _CRTDBG_MAP_ALLOC  

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow mainWindow(Q_NULLPTR);
	mainWindow.show();

	return a.exec();
}
