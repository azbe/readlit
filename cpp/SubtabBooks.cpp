#include "src/SubtabBooks.h"

#include <QLabel>
#include <QLineEdit>

#include "src/BrowserButton.h"
#include "src/ScannerButton.h"
#include "src/DataList.h"
#include "src/DataTable.h"
#include "src/DataButton.h"
#include "src/Constants.h"

SubtabBooks::SubtabBooks(QWidget *parent) : QWidget(parent)
{
	QSizePolicy *genericPolicy;

	scanner = new QWidget(this);
	books = new QWidget(this);
	bookLayout = new QVBoxLayout(this);

	scanner->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	scanner->setFixedHeight(41);
	QLayout *bookWidgetsLayout0 = new QHBoxLayout(scanner);
	QLabel *folderPathsLabel = new QLabel("Folder Paths", scanner);
	QLineEdit *folderPaths = new QLineEdit(scanner);
	BrowserButton *browserButton = new BrowserButton(scanner);
	ScannerButton *scannerButton = new ScannerButton(scanner);
	bookWidgetsLayout0->addWidget(folderPathsLabel);
	bookWidgetsLayout0->addWidget(folderPaths);
	bookWidgetsLayout0->addWidget(browserButton);
	bookWidgetsLayout0->addWidget(scannerButton);
	bookWidgetsLayout0->setContentsMargins(0, 0, 0, 0);

	books->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	QLayout *bookWidgetsLayout1 = new QHBoxLayout(books);
	DataList *bookList = new DataList(books);
	genericPolicy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_BOOKS_LIST_HORIZONTAL_STRETCH);
	bookList->setSizePolicy(*genericPolicy);
	delete genericPolicy;
	QWidget *dataWidget = new QWidget(books);
	genericPolicy = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_BOOKS_DETAILS_WIDGET_HORIZONTAL_STRETCH);
	dataWidget->setSizePolicy(*genericPolicy);
	delete genericPolicy;
	QGridLayout *dataWidgetLayout = new QGridLayout(dataWidget);
	DataButton *dataButtons[4];
	for (int i = 0; i < 4; i++)
	{
		QString text;
		switch (i)
		{
			case 0: { text = "Sync"; break; }
			case 1: { text = "Set"; break; }
			case 2: { text = "Load"; break; }
			case 3: { text = "Clear"; break; }
		}
		//text += " Book Data";
		dataButtons[i] = new DataButton(text, books);
		dataButtons[i]->setMaximumWidth(UIConstants::DATA_BUTTON_DEFAULT_MAX_SIZE);
		dataButtons[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
		dataWidgetLayout->addWidget(dataButtons[i], 0, i, 1, 1);
	}
	DataTable *bookData = new DataTable(books);
	dataWidgetLayout->addWidget(bookData, 1, 0, 1, 5);
	dataWidgetLayout->setContentsMargins(0, 0, 0, 0);
	bookWidgetsLayout1->addWidget(bookList);
	bookWidgetsLayout1->addWidget(dataWidget);
	bookWidgetsLayout1->setContentsMargins(0, 0, 0, 0);

	bookLayout->addWidget(scanner);
	bookLayout->addWidget(books);
}

SubtabBooks::~SubtabBooks()
{
	if (scanner) delete scanner;
	if (books) delete books;
	if (bookLayout) delete bookLayout;
}
