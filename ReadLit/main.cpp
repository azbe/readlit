#include <QtWidgets/QApplication>
#include <QPushButton>
#include "ReadlitWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ReadLitWindow window;

	ReadLitWindow reader;

	ReadLitWindow local;
	ReadLitWindow localBooks;
	ReadLitWindow localAuthors;
	ReadLitWindow localSettings;
	QPushButton unpin;
	local.addTab(&localBooks, "Books");
	local.addTab(&localAuthors, "Authors");
	local.addTab(&localSettings, "Local Settings");

	ReadLitWindow world;
	ReadLitWindow worldBooks;
	ReadLitWindow worldAuthors;
	ReadLitWindow worldSettings;
	world.addTab(&worldBooks, "Books");
	world.addTab(&worldAuthors, "Authors");
	world.addTab(&worldSettings, "World Settings");

	window.addTab(&reader, "Reader");
	window.addTab(&local, "Local");
	window.addTab(&world, "World");

	window.show();

	return a.exec();
}
