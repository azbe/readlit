
#include "src/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	resize(UIConstants::MAINWINDOW_DEFAULT_WIDTH, UIConstants::MAINWINDOW_DEFAULT_HEIGHT);
    database.load("database.json");

	mainTabs = new QTabWidget(this);
	mainLayout = new QHBoxLayout(this);

	tabReader = new QWidget(this);
	tabLocal = new QWidget(this);
	tabSettings = new QWidget(this);

    readerLayout = new QHBoxLayout(tabReader);
    readerExtras = new ReaderExtras(tabReader);
    reader = new Reader(tabReader);
    readerLayout->addWidget(readerExtras, 1);
    readerLayout->addWidget(reader, 3);

    localTabs = new QTabWidget(tabLocal);
    localLayout = new QHBoxLayout(tabLocal);

    books = new SubtabBooks(tabLocal, database);
    authors = new SubtabAuthors(tabLocal, database);
    connect(books, SIGNAL(updateAuthors()), authors, SLOT(newScan()));
    connect(books, SIGNAL(openInReader(QString)), this, SLOT(openBookInReader(QString)));

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
    delete tabSettings;
    delete authors;
    delete books;
    delete localLayout;
    delete localTabs;
    delete tabLocal;
    delete readerExtras;
    delete reader;
    delete readerLayout;
    delete tabReader;
    delete mainLayout;
    delete mainTabs;
    database.save("database.json");
}

void MainWindow::openBookInReader(const QString &path)
{
    delete reader;
    readerExtras->setParent(0);
    delete readerLayout;
    readerLayout = new QHBoxLayout(tabReader);
    reader = new Reader(tabReader, path);
    readerLayout->addWidget(readerExtras, 1);
    readerLayout->addWidget(reader, 3);
    mainTabs->setCurrentIndex(0);
}
