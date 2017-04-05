#include <stdlib.h>  
#include <crtdbg.h> 
#include <iostream>

#include <QApplication>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

#include "QWidget.h"
#include "Database.h"
#include "ListContainer.h"

#define _CRTDBG_MAP_ALLOC  
#define DB Database::getInstance()

/*
QWidget* tabReader()
{
	QWidget* reader = new QWidget;
	return reader;
}
*/

QWidget* tabLocal()
{
	QWidget *local = new QWidget();

	QTabWidget *localTabs = new QTabWidget(local);
	QGridLayout *localLayout = new QGridLayout(local);

	QWidget *localBooks = new QWidget(localTabs);
	QWidget *localAuthors = new QWidget(localTabs);
	//QWidget *localSettings = new QWidget(localTabs);

	QHBoxLayout *localBooksLayout = new QHBoxLayout(localBooks);
	ListContainer *bookList = new ListContainer(localBooks, ListContainer::BOOKS);
	//DetailsContainer *bookDetails = new DetailsContainer(localBooks, DetailsContainer::BOOK);
	localBooksLayout->addWidget(bookList);
	//localBooksLayout->addWidget(bookDetails);

	QHBoxLayout *localAuthorsLayout = new QHBoxLayout(localAuthors);
	ListContainer *authorList = new ListContainer(localAuthors, ListContainer::AUTHORS);
	ListContainer *authorBookList = new ListContainer(localAuthors, ListContainer::NOTHING);
	//DetailsContainer *authorDetails = new DetailsContainer(localAuthors, DetailsContainer::AUTHOR);
	localAuthorsLayout->addWidget(authorList);
	localAuthorsLayout->addWidget(authorBookList);
	//localAuthorsLayout->addWidget(authorDetails);

	localTabs->addTab(localBooks, "Books");
	localTabs->addTab(localAuthors, "Authors");
	//localTabs->addTab(localSettings, "Settings");

	localLayout->addWidget(localTabs);
	localTabs->setCurrentIndex(0);

	return local;
}

/*
QWidget* tabWorld()
{
	QWidget* world = new QWidget;
	QWidget *worldBooks, *worldAuthors, *worldSettings;
	worldBooks = new QWidget; worldAuthors = new QWidget; worldSettings = new QWidget;
	world->addTab(worldBooks, "Books");
	world->addTab(worldAuthors, "Authors");
	world->addTab(worldSettings, "World Settings");
	return world;
}

QWidget* tabSettings()
{
	QWidget* settings = new QWidget;
	return settings;
}
*/

void dateTestDB() //doar de testare
{
	for (int i = 0; i < 100; i++)
	{
		char b[3], a[2];
		char* path = "C:\\Users\\Radu\\titlu.pdf";
		itoa(i, b, 10);
		itoa((i / 10), a, 10);
		DB.addBook(Book(b, a, "C:\\Users\\Radu\\titlu.pdf"));
	}
}

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	QApplication a(argc, argv);

	//Se populeaza Baza de Date cu date nesemnificative (temporar, doar pentru teste)
	dateTestDB();

	//Window-ul principal
	//In Qt, QWidget este clasa de baza: aproape orice window si fereastra in Qt sunt, in esenta, QWidget-uri
	QWidget *mainWindow = new QWidget(Q_NULLPTR); 

	//Tab-urile Reader, Local, World si Settings vor intra sub un obiect QTabWidget
	//QTabWidget "tine" taburile, ele se adauga la el
	//Taburile sunt descendentii lui QTabWidget, care este la randul lui descendentul window-ului principal (*mainWindow)
	QTabWidget *mainTabs = new QTabWidget(mainWindow);
	
	//Layout-urile sunt asemanatoare cu Swing-ul din Java (laborator PAO)
	//Ele ordoneaza obiectele intr-un QWidget
	//E nevoie de un layout si pentru QTabWidget
	QGridLayout *mainLayout = new QGridLayout(mainWindow);

	//Subtaburile fiecarui tab principal (cele de mai sus)
	//Se va face referire la fiecare functie pentru a nu "manji" main-ul (mai mult decat e deja)
	//QWidget* reader = tabReader();
	QWidget* local = tabLocal();
	//QWidget* world = tabWorld();
	//QWidget* settings = tabSettings();

	//mainTabs->addTab(reader, "Reader");
	mainTabs->addTab(local, "Local");
	//mainTabs->addTab(world, "World");
	//mainTabs->addTab(settings, "Settings");

	mainLayout->addWidget(mainTabs);
	mainTabs->setCurrentIndex(0);

	//Aici se afiseaza window-ul principal si se porneste aplicatia
	mainWindow->show();
	return a.exec();
}
