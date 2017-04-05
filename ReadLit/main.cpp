#include <stdlib.h>  
#include <crtdbg.h> 
#include <iostream>

#include <QtWidgets/QApplication>
#include <QGridLayout.h>

#include "ReadlitWindow.h"
#include "Database.h"
#include "ListContainer.h"

#define _CRTDBG_MAP_ALLOC  
#define DB Database::getInstance()

ReadLitWindow* tabReader()
{
	ReadLitWindow* reader = new ReadLitWindow;
	return reader;
}

ReadLitWindow* tabLocal()
{
	ReadLitWindow *local = new ReadLitWindow;

	ReadLitWindow *localBooks = new ReadLitWindow; 
	QGridLayout *localBooksLayout = new QGridLayout(localBooks);

	ListContainer *bookNames = new ListContainer(Q_NULLPTR, ListContainer::BOOKS);
	localBooksLayout->addWidget(bookNames, 0, 0, -1, 1);
	localBooksLayout->setColumnStretch(0, 1);

	//DetailsContainer *bookDetails = new DetailsContainer(Q_NULLPTR, DetailsContainer::BOOK);
	//localBooksLayout->addWidget(bookDetails, 0, 1, -1, 1);
	//localBooksLayout->setColumnStretch(1, 1);

	localBooks->setLayout(localBooksLayout);

	ReadLitWindow *localAuthors = new ReadLitWindow; 
	QGridLayout *localAuthorsLayout = new QGridLayout(localAuthors);

	ListContainer *authorNames = new ListContainer(Q_NULLPTR, ListContainer::AUTHORS);
	localAuthorsLayout->addWidget(authorNames, 0, 0, -1, 1);
	localAuthorsLayout->setColumnStretch(0, 1);

	ListContainer *authorBooks = new ListContainer(Q_NULLPTR, ListContainer::BOOKS);
	localAuthorsLayout->addWidget(authorBooks, 0, 1, -1, 1);
	localAuthorsLayout->setColumnStretch(1, 1);
	
	//DetailsContainer *authorDetails = new DetailsContainer(Q_NULLPTR, DetailsContainer::AUTHOR);
	//localAuthorsLayout->addWidget(authorDetails, 0, 2, -1, 1);
	//localBooksLayout->setColumnStretch(2, 1);
	
	localAuthors->setLayout(localAuthorsLayout);

	ReadLitWindow* localSettings = new ReadLitWindow;

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
	DB.addBook(Book("Titlu7", "Autor1", "C:\\Users\\Radu\\titlu6.pdf"));
}

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);

	testDB();

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
