#include "src/SubtabBooks.h"

#include <QLabel>
#include <QLineEdit>

SubtabBooks::SubtabBooks(QWidget *parent, DataBase& database) : QWidget(parent)
{
	QSizePolicy *genericPolicy;

    this->database = &database;
	scanner = new QWidget(this);
	books = new QWidget(this);
	bookLayout = new QVBoxLayout(this);

	scanner->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	scanner->setFixedHeight(41);
    bookWidgetsLayout0 = new QHBoxLayout(scanner);
    folderPathsLabel = new QLabel("Folder Paths", scanner);
    folderPaths = new QLineEdit(scanner);
    browserButton = new BrowserButton(scanner);
    scannerButton = new ScannerButton(scanner, folderPaths);
    connect(scannerButton, SIGNAL(sendBookPaths(QStringList)), this, SLOT(getBookpaths(QStringList)));
	bookWidgetsLayout0->addWidget(folderPathsLabel);
	bookWidgetsLayout0->addWidget(folderPaths);
	bookWidgetsLayout0->addWidget(browserButton);
	bookWidgetsLayout0->addWidget(scannerButton);
	bookWidgetsLayout0->setContentsMargins(0, 0, 0, 0);

	books->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    bookWidgetsLayout1 = new QHBoxLayout(books);
    bookList = new DataList(books);
    bookList->addItems(this->database->getBookTitles());
	genericPolicy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_BOOKS_LIST_HORIZONTAL_STRETCH);
	bookList->setSizePolicy(*genericPolicy);
    bookList->setSortingEnabled(true);
	delete genericPolicy;
    dataWidget = new QWidget(books);
	genericPolicy = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	genericPolicy->setHorizontalStretch(UIConstants::LOCAL_BOOKS_DETAILS_WIDGET_HORIZONTAL_STRETCH);
	dataWidget->setSizePolicy(*genericPolicy);
	delete genericPolicy;
    dataWidgetLayout = new QGridLayout(dataWidget);
    bookData = new BookTable(books);
    connect(bookList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(getBookDetails(QListWidgetItem*)));
    connect(this, SIGNAL(updateBookDetails(Book)), bookData, SLOT(setBook(Book)));
    connect(bookData, SIGNAL(updateBook(Book)), this, SLOT(saveNewBook(Book)));
    dataWidgetLayout->addWidget(bookData, 1, 0, 1, 5);
    dataWidgetLayout->setContentsMargins(0, 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		QString text;
        dataButtons[i] = new DataButton("", books);
		switch (i)
		{
            case 0:
            {
                text = "Sync";
                break;
            }
            case 1:
            {
                text = "Save";
                connect(dataButtons[i], SIGNAL(clicked(bool)), bookData, SLOT(saveBook()));
                break;
            }
            case 2:
            {
                text = "Load";
                break;
            }
            case 3:
            {
                text = "Clear";
                connect(dataButtons[i], SIGNAL(clicked(bool)), bookData, SLOT(clear()));
                break;
            }
		}
		//text += " Book Data";
        dataButtons[i]->setText(text);
		dataButtons[i]->setMaximumWidth(UIConstants::DATA_BUTTON_DEFAULT_MAX_SIZE);
		dataButtons[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
		dataWidgetLayout->addWidget(dataButtons[i], 0, i, 1, 1);
	}
	bookWidgetsLayout1->addWidget(bookList);
	bookWidgetsLayout1->addWidget(dataWidget);
	bookWidgetsLayout1->setContentsMargins(0, 0, 0, 0);

	bookLayout->addWidget(scanner);
    bookLayout->addWidget(books);
}

SubtabBooks::~SubtabBooks()
{
    delete bookData;
    for (int i = 0; i < 4; i++) dataButtons[i];
    delete dataWidgetLayout;
    delete dataWidget;
    delete bookList;
    delete bookWidgetsLayout1;
    delete books;
    delete scannerButton;
    delete browserButton;
    delete folderPaths;
    delete folderPathsLabel;
    delete bookWidgetsLayout0;
    delete scanner;
    delete bookLayout;
}

void SubtabBooks::saveNewBook(const Book &book)
{
    database->editBook(book);
    bookList->currentItem()->setText(book.getTitle());
    //emit updateAuthors();
}

void SubtabBooks::getBookDetails(QListWidgetItem *item)
{
    Book book = database->getBookByTitle(item->text());
    emit updateBookDetails(book);
}

void SubtabBooks::getBookpaths(QStringList bookPaths)
{
    for (int index = 0; index < bookPaths.size(); index++)
    {
        if (!database->findBook(bookPaths.value(index)))
            database->addBook(Book(bookPaths.value(index), bookPaths.value(index)));
    }
    updateBookList();
    emit updateAuthors();
}

void SubtabBooks::updateBookList()
{
    QStringList books = database->getBookTitles();
    bookList->clear();
    bookList->addItems(books);
}
