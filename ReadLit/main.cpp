#include <stdlib.h>  
#include <crtdbg.h> 
#include <iostream>

#include <QApplication>
#include <QWidget>

#define _CRTDBG_MAP_ALLOC  

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);

	return a.exec();
}
