#include "SubtabBooks.h"

#include <QLabel>
#include <QLineEdit>

#include "BrowserButton.h"
#include "ScannerButton.h"
#include "DataList.h"
#include "DataTable.h"
#include "DataButton.h"

SubtabBooks::SubtabBooks(QWidget *parent) : QWidget(parent)
{
	QSizePolicy *genericPolicy;

	bookWidgets[0] = new QWidget(this);
	bookWidgets[1] = new QWidget(this);
	bookLayout = new QVBoxLayout(this);

	bookWidgets[0]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	bookWidgets[0]->setFixedHeight(41);
	QLayout *bookWidgetsLayout0 = new QHBoxLayout(bookWidgets[0]);
	QLabel *folderPathsLabel = new QLabel("Folder Paths", bookWidgets[0]);
	QLineEdit *folderPaths = new QLineEdit(bookWidgets[0]);
	BrowserButton *browserButton = new BrowserButton(bookWidgets[0]);
	browserButton->setText("+");
	ScannerButton *scannerButton = new ScannerButton("Scan 'n Save", bookWidgets[0]);
	bookWidgetsLayout0->addWidget(folderPathsLabel);
	bookWidgetsLayout0->addWidget(folderPaths);
	bookWidgetsLayout0->addWidget(browserButton);
	bookWidgetsLayout0->addWidget(scannerButton);
	bookWidgetsLayout0->setContentsMargins(0, 0, 0, 0);

	bookWidgets[1]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	QLayout *bookWidgetsLayout1 = new QHBoxLayout(bookWidgets[1]);
	DataList *bookList = new DataList(bookWidgets[1]);
	genericPolicy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	genericPolicy->setHorizontalStretch(2);
	bookList->setSizePolicy(*genericPolicy);
	delete genericPolicy;
	QWidget *dataWidget = new QWidget(bookWidgets[1]);
	genericPolicy = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	genericPolicy->setHorizontalStretch(3);
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
		text += " Book Data";
		dataButtons[i] = new DataButton(text, bookWidgets[1]);
		dataButtons[i]->setMaximumWidth(100);
		dataButtons[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
		dataWidgetLayout->addWidget(dataButtons[i], 0, i, 1, 1);
	}
	DataTable *bookData = new DataTable(bookWidgets[1]);
	dataWidgetLayout->addWidget(bookData, 1, 0, 1, 5);
	dataWidgetLayout->setContentsMargins(0, 0, 0, 0);
	bookWidgetsLayout1->addWidget(bookList);
	bookWidgetsLayout1->addWidget(dataWidget);
	bookWidgetsLayout1->setContentsMargins(0, 0, 0, 0);

	bookLayout->addWidget(bookWidgets[0]);
	bookLayout->addWidget(bookWidgets[1]);
}

SubtabBooks::~SubtabBooks()
{
	if (bookWidgets[0]) delete bookWidgets[0];
	if (bookWidgets[1]) delete bookWidgets[1];
	if (bookLayout) delete bookLayout;
}
