#include "src/MainWindow.h"
#include "src/Constants.h"
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	resize(UIConstants::MAINWINDOW_DEFAULT_WIDTH, UIConstants::MAINWINDOW_DEFAULT_HEIGHT);
    tabSettings = new QWidget(this);
    settingsLayout = new QGridLayout(tabSettings);
    settings = new Settings(tabSettings, "settings.cfg");
    settingsLayout->addWidget(settings,0,0);
    database.load(Settings::databasePath.trimmed());
	mainTabs = new QTabWidget(this);
	mainLayout = new QHBoxLayout(this);

	tabReader = new QWidget(this);
	tabLocal = new QWidget(this);

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

	mainTabs->addTab(tabReader, "Reader");
	mainTabs->addTab(tabLocal, "Local");
	mainTabs->addTab(tabSettings, "Settings");

    mainTabs->setCurrentIndex(1);
	mainLayout->addWidget(mainTabs);
}

MainWindow::~MainWindow() 
{
    database.save(Settings::databasePath.trimmed());
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
    readerExtras->setParent(0);
    delete readerLayout;
    readerLayout = new QHBoxLayout(tabReader);
    reader = new Reader(tabReader, path);
    readerLayout->addWidget(readerExtras, 1);
    if (reader->isNull())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"ERROR","There was an error opening the book.");
        qDebug() << "MainWindow::openBookInReader - Error: reader is null";
        delete reader;
        reader = nullptr;
        return;
    }
    readerLayout->addWidget(reader, 3);
    mainTabs->setCurrentIndex(0);
}
