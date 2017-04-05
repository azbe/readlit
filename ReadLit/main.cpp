#include <stdlib.h>  
#include <crtdbg.h> 
#include <iostream>

#include <QtWidgets/QApplication>

#include "ReadlitWindow.h"
#include "Database.h"

#define _CRTDBG_MAP_ALLOC  
#define DB Database::getInstance()

ReadLitWindow* tabReader()
{
	ReadLitWindow* reader = new ReadLitWindow;
	return reader;
}

ReadLitWindow* tabLocal()
{
	ReadLitWindow* local = new ReadLitWindow;
	ReadLitWindow *localBooks, *localAuthors, *localSettings;
	localBooks = new ReadLitWindow; localAuthors = new ReadLitWindow; localSettings = new ReadLitWindow;
	local->addTab(localBooks, "Books");
	local->addTab(localAuthors, "Authors");
	local->addTab(localSettings, "Local Settings");
	return local;
}

ReadLitWindow* tabWorld()
{
	ReadLitWindow* world = new ReadLitWindow;
	ReadLitWindow *worldBooks, *worldAuthors, *worldSettings;
	worldBooks = new ReadLitWindow; worldAuthors = new ReadLitWindow; worldSettings = new ReadLitWindow;
	world->addTab(worldBooks, "Books");
	world->addTab(worldAuthors, "Authors");
	world->addTab(worldSettings, "World Settings");
	return world;
}

ReadLitWindow* tabSettings()
{
	ReadLitWindow* settings = new ReadLitWindow;
	return settings;
}

void testDB() //doar de testare
{
	DB.addBook(Book("Titlu1", "Autor1", "C:\\Users\\Radu\\titlu1.pdf"));
	DB.addBook(Book("Titlu2", "Autor2", "C:\\Users\\Radu\\titlu2.pdf"));
	DB.addBook(Book("Titlu3", "Autor2", "C:\\Users\\Radu\\titlu3.pdf"));
	DB.addBook(Book("Titlu4", "Autor1", "C:\\Users\\Radu\\titlu4.pdf"));
	DB.addBook(Book("Titlu5", "Autor3", "C:\\Users\\Radu\\titlu5.pdf"));
	DB.addBook(Book("Titlu6", "Autor2", "C:\\Users\\Radu\\titlu6.pdf"));
}

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);

	ReadLitWindow window;
	ReadLitWindow* reader = tabReader();
	ReadLitWindow* local = tabLocal();
	ReadLitWindow* world = tabWorld();
	ReadLitWindow* settings = tabSettings();
	
	window.addTab(reader, "Reader");
	window.addTab(local, "Local");
	window.addTab(world, "World");
	window.addTab(settings, "Settings");

	window.show();

	return a.exec();
}
