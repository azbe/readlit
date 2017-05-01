#include "src/MainWindow.h"
#include "src/Constants.h"
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	resize(UIConstants::MAINWINDOW_DEFAULT_WIDTH, UIConstants::MAINWINDOW_DEFAULT_HEIGHT);
    tabSettings = new QWidget(this);
    settingsLayout = new QGridLayout(tabSettings);
    settings = new Settings(tabSettings, "settings.cfg");
    settingsLayout->addWidget(settings,0,0);
    database.load(SettingsConstants::DATABASE_DEFAULT_PATH);
	mainTabs = new QTabWidget(this);
	mainLayout = new QHBoxLayout(this);

	tabReader = new QWidget(this);
	tabLocal = new QWidget(this);

    readerLayout = new QGridLayout(tabReader);
    readerExtras = new QWidget(tabReader);
    reader = new Reader(tabReader);
    readerLayout->addWidget(readerExtras, 0, 0, 1, 1);
    readerLayout->addWidget(reader, 0, 1, 1, 3);

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
    //settings->save("settings.cfg");
    database.save(SettingsConstants::DATABASE_DEFAULT_PATH);
    delete settings;
    delete settingsLayout;
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
}

void MainWindow::openBookInReader(const QString &path)
{
    delete reader;
    reader = new Reader(tabReader, path);
    readerLayout->addWidget(reader, 0, 1, 1, 3);
    mainTabs->setCurrentIndex(0);
}
