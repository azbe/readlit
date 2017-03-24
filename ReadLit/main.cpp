#include "ReadLit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ReadLit w;
	w.show();
	return a.exec();
}
