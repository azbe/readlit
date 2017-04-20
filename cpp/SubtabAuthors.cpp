#include "src/SubtabAuthors.h"

SubtabAuthors::SubtabAuthors(QWidget *parent, DataBase& database) : QWidget(parent)
{
    this->database = &database;
	QSizePolicy *genericPolicy;

    authorList = new DataList(this);
	authorBooks = new DataList(this);
	authorData = new QWidget(this);
	authorLayout = new QHBoxLayout(this);

	genericPolicy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_AUTHORS_LIST_HORIZONTAL_STRETCH);
    authorList->addItems(this->database->getAuthorNames());
    authorList->setSizePolicy(*genericPolicy);
    authorList->setSortingEnabled(true);
    connect(authorList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(updateAuthorBooks(QListWidgetItem*)));
    authorBooks->setSizePolicy(*genericPolicy);
    authorBooks->setSortingEnabled(true);
	delete genericPolicy;

	genericPolicy = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_AUTHORS_DETAILS_WIDGET_HORIZONTAL_STRETCH);
	authorData->setSizePolicy(*genericPolicy);
	delete genericPolicy;
    authorDataLayout = new QGridLayout(authorData);
	for (int i = 0; i < 4; i++)
	{
		QString text;
		switch (i)
		{
		case 0: { text = "Sync"; break; }
        case 1: { text = "Save"; break; }
		case 2: { text = "Load"; break; }
		case 3: { text = "Clear"; break; }
		}
		//text += " Author Data";
		dataButtons[i] = new DataButton(text, authorData);
		dataButtons[i]->setMaximumWidth(UIConstants::DATA_BUTTON_DEFAULT_MAX_SIZE);
		dataButtons[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
		authorDataLayout->addWidget(dataButtons[i], 0, i, 1, 1);
	}
    authorDataTable = new AuthorTable(authorData);
    connect(this, SIGNAL(updateAuthorDetails(Author)), authorDataTable, SLOT(setAuthor(Author)));
    authorDataLayout->addWidget(authorDataTable, 1, 0, 1, 5);
	authorDataLayout->setContentsMargins(0, 0, 0, 0);

    authorLayout->addWidget(authorList);
	authorLayout->addWidget(authorBooks);
    authorLayout->addWidget(authorData);
}

SubtabAuthors::~SubtabAuthors()
{
    delete authorDataTable;
    for (int i = 0; i < 4; i++) delete dataButtons[i];
    delete authorDataLayout;
    delete authorData;
    delete authorBooks;
    delete authorList;
    delete authorLayout;
}

void SubtabAuthors::newScan()
{
    QStringList authors = database->getAuthorNames();
    authorList->clear();
    authorList->addItems(authors);
}

void SubtabAuthors::updateAuthorBooks(QListWidgetItem *item)
{
    Author author = database->getAuthor(item->text());
    emit updateAuthorDetails(author);
    QStringList books = database->getBookTitles();
    authorBooks->clear();
    authorBooks->addItems(books);
}
