#include <stdlib.h>  
#include <crtdbg.h> 
#include <iostream>

#include <QtWidgets/QApplication>
#include <QBoxLayout.h>

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
	QWidget *localBooksLayoutWidget = new QWidget(localBooks);
	localBooksLayoutWidget->setMinimumSize(100, 300);
	localBooksLayoutWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	localBooksLayoutWidget->setContentsMargins(11, 11, 11, 11);
	QHBoxLayout *localBooksLayout = new QHBoxLayout(localBooksLayoutWidget);
	localBooksLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	ListContainer *bookNames = new ListContainer(localBooksLayoutWidget, ListContainer::BOOKS);
	bookNames->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	localBooksLayout->addWidget(bookNames);

	//DetailsContainer *bookDetails = new DetailsContainer(Q_NULLPTR, DetailsContainer::BOOK);
	//localBooksLayout->addWidget(bookDetails, 0, 1);

	ReadLitWindow *localAuthors = new ReadLitWindow; 
	QWidget *localAuthorsLayoutWidget = new QWidget(localAuthors);
	localAuthorsLayoutWidget->setMinimumSize(100, 300);
	localAuthorsLayoutWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	localAuthorsLayoutWidget->setContentsMargins(11, 11, 11, 11);
	QHBoxLayout *localAuthorsLayout = new QHBoxLayout(localAuthorsLayoutWidget);
	localAuthorsLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	ListContainer *authorNames = new ListContainer(localAuthorsLayoutWidget, ListContainer::AUTHORS);
	localAuthorsLayout->addWidget(authorNames);
	
	ListContainer *authorBooks = new ListContainer(localAuthorsLayoutWidget, ListContainer::NOTHING);
	localAuthorsLayout->addWidget(authorBooks);
	
	//DetailsContainer *authorDetails = new DetailsContainer(localAuthorsLayoutWidget, DetailsContainer::AUTHOR);
	//localAuthorsLayout->addWidget(authorDetails, 0, 2);

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
	for (int i = 0; i < 100; i++)
	{
		char nr[4];
		itoa(i, nr, 10);
		DB.addBook(Book(nr, "Autor", "C:\\Users\\Radu\\titlu1.pdf"));
	}
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

	window.setMinimumSize(400, 400);

	window.show();

	return a.exec();
}
