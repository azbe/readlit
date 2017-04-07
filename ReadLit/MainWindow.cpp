#include <QGridLayout>

#include "MainWindow.h"
#include "SubtabBooks.h"
#include "SubtabAuthors.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	resize(BASE_WIDTH, BASE_HEIGHT);

	mainTabs = new QTabWidget(this);
	mainLayout = new QHBoxLayout(this);

	QWidget *tabReader, *tabLocal, *tabSettings;
	tabReader = new QWidget(this);
	tabLocal = new QWidget(this);
	tabSettings = new QWidget(this);

	//TO DO: Reader

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
