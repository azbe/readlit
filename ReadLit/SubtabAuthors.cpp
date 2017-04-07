#include "SubtabAuthors.h"
#include "DataButton.h"
#include "DataTable.h"

SubtabAuthors::SubtabAuthors(QWidget *parent) : QWidget(parent)
{
	QSizePolicy *genericPolicy;

	authors = new DataList(this);
	authorBooks = new DataList(this);
	authorData = new QWidget(this);
	authorLayout = new QHBoxLayout(this);

	genericPolicy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	genericPolicy->setHorizontalStretch(1);
	authors->setSizePolicy(*genericPolicy);
	authorBooks->setSizePolicy(*genericPolicy);
	delete genericPolicy;

	genericPolicy = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	genericPolicy->setHorizontalStretch(2);
	authorData->setSizePolicy(*genericPolicy);
	delete genericPolicy;
	QGridLayout* authorDataLayout = new QGridLayout(authorData);
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
		//text += " Author Data";
		dataButtons[i] = new DataButton(text, authorData);
		dataButtons[i]->setMaximumWidth(75);
		dataButtons[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
		authorDataLayout->addWidget(dataButtons[i], 0, i, 1, 1);
	}
	DataTable *authorDataTable = new DataTable(authorData);
	authorDataLayout->addWidget(authorDataTable, 1, 0, 1, 5);
	authorDataLayout->setContentsMargins(0, 0, 0, 0);

	authorLayout->addWidget(authors);
	authorLayout->addWidget(authorBooks);
	authorLayout->addWidget(authorData);
}


SubtabAuthors::~SubtabAuthors()
{
	if (authors) delete authors;
	if (authorBooks) delete authorBooks;
	if (authorData) delete authorData;
	if (authorLayout) delete authorLayout;
}
