#include <QGridLayout>

#include "src/MainWindow.h"
#include "src/SubtabBooks.h"
#include "src/SubtabAuthors.h"
#include "src/Constants.h"
#include "src/Reader.h"
#include "src/Settings.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	resize(UIConstants::MAINWINDOW_DEFAULT_WIDTH, UIConstants::MAINWINDOW_DEFAULT_HEIGHT);
    database.load("database.json");

	mainTabs = new QTabWidget(this);
	mainLayout = new QHBoxLayout(this);

	QWidget *tabReader, *tabLocal, *tabSettings;
	tabReader = new QWidget(this);
	tabLocal = new QWidget(this);
	tabSettings = new QWidget(this);

    QGridLayout *readerLayout = new QGridLayout(tabReader);
    QWidget *readerExtras = new QWidget(tabReader);
    Reader *reader = new Reader(tabReader, "/home/alin/Downloads/0.pdf");
    readerLayout->addWidget(readerExtras, 0, 0, 1, 1);
    readerLayout->addWidget(reader, 0, 1, 1, 3);

	QTabWidget *localTabs = new QTabWidget(tabLocal);
	QLayout *localLayout = new QHBoxLayout(tabLocal);

    QGridLayout *settingsLayout = new QGridLayout(tabSettings);
    Settings *settings = new Settings(tabSettings);


    SubtabBooks *books = new SubtabBooks(tabLocal, database);
    SubtabAuthors *authors = new SubtabAuthors(tabLocal, database);
    connect(books, SIGNAL(updateAuthors()), authors, SLOT(newScan()));

	localTabs->addTab(books, "Books");
	localTabs->addTab(authors, "Authors");

	localTabs->setCurrentIndex(0);
	localLayout->addWidget(localTabs);

	//TO DO: Settings

	mainTabs->addTab(tabReader, "Reader");
	mainTabs->addTab(tabLocal, "Local");
	mainTabs->addTab(tabSettings, "Settings");

    mainTabs->setCurrentIndex(1);
	mainLayout->addWidget(mainTabs);
}

MainWindow::~MainWindow() 
{
    if (mainLayout) delete mainLayout;
    if (mainTabs) delete mainTabs;
    database.save("database.json");
}
