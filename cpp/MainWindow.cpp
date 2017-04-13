#include <QGridLayout>

#include "src/MainWindow.h"
#include "src/SubtabBooks.h"
#include "src/SubtabAuthors.h"
#include "src/Constants.h"
#include "src/Reader.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	resize(UIConstants::MAINWINDOW_DEFAULT_WIDTH, UIConstants::MAINWINDOW_DEFAULT_HEIGHT);

	mainTabs = new QTabWidget(this);
	mainLayout = new QHBoxLayout(this);

	QWidget *tabReader, *tabLocal, *tabSettings;
	tabReader = new QWidget(this);
	tabLocal = new QWidget(this);
	tabSettings = new QWidget(this);

    QGridLayout *readerLayout = new QGridLayout(tabReader);
    QListWidget *listWidget = new QListWidget(tabReader); //Doar de test, nu va fi un listwidget
    Reader *reader = new Reader(tabReader, "/home/radu/Downloads/Crime_and_Punishment.pdf");
    readerLayout->addWidget(listWidget, 0, 0, 1, 1);
    readerLayout->addWidget(reader, 0, 1, 1, 1);

	QTabWidget *localTabs = new QTabWidget(tabLocal);
	QLayout *localLayout = new QHBoxLayout(tabLocal);

	SubtabBooks *books = new SubtabBooks(tabLocal);
	SubtabAuthors *authors = new SubtabAuthors(tabLocal);

	localTabs->addTab(books, "Books");
	localTabs->addTab(authors, "Authors");

	localTabs->setCurrentIndex(0);
	localLayout->addWidget(localTabs);

	//TO DO: Settings

	mainTabs->addTab(tabReader, "Reader");
	mainTabs->addTab(tabLocal, "Local");
	mainTabs->addTab(tabSettings, "Settings");

	mainTabs->setCurrentIndex(0);
	mainLayout->addWidget(mainTabs);
}

MainWindow::~MainWindow() 
{
	if (mainTabs) delete mainTabs;
	if (mainLayout) delete mainLayout;
}
