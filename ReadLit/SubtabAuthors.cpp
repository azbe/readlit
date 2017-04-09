#include "SubtabAuthors.h"
#include "DataButton.h"
#include "DataTable.h"
#include "Constants.h"

SubtabAuthors::SubtabAuthors(QWidget *parent) : QWidget(parent)
{
	QSizePolicy *genericPolicy;

	authors = new DataList(this);
	authorBooks = new DataList(this);
	authorData = new QWidget(this);
	authorLayout = new QHBoxLayout(this);

	genericPolicy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_AUTHORS_LIST_HORIZONTAL_STRETCH);
	authors->setSizePolicy(*genericPolicy);
	authorBooks->setSizePolicy(*genericPolicy);
	delete genericPolicy;

	genericPolicy = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_AUTHORS_DETAILS_WIDGET_HORIZONTAL_STRETCH);
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
		dataButtons[i]->setMaximumWidth(UIConstants::DATA_BUTTON_DEFAULT_MAX_SIZE);
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
