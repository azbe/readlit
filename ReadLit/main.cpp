#include <stdlib.h>  
#include <crtdbg.h> 
#include <iostream>

#include <QApplication>
#include <QWidget>
#include "MainWindow.h"

#define _CRTDBG_MAP_ALLOC  

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);

	MainWindow mainWindow(Q_NULLPTR);
	mainWindow.show();

	return a.exec();
}
