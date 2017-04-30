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
    browserButton = new BrowserButton(scanner, BrowserButton::DIR);
    connect(browserButton, SIGNAL(sendPaths(QStringList)), this, SLOT(getBrowsePaths(QStringList)));
    scannerButton = new ScannerButton(scanner, folderPaths);
    connect(scannerButton, SIGNAL(sendBookPaths(QStringList)), this, SLOT(getBookPaths(QStringList)));
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
    connect(bookList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(toOpenInReader()));
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
                connect(dataButtons[i], SIGNAL(clicked(bool)), this, SLOT(getSyncDetails()));
                isSyncing = false;
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
    for (int i = 0; i < 4; i++)
        delete dataButtons[i];
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

void SubtabBooks::toOpenInReader()
{
    emit(openInReader(bookData->getBook().getFilePath()));
}

void SubtabBooks::saveNewBook(const Book &book)
{
    database->editBook(book);
    bookList->currentItem()->setText(book.getTitle());
    emit updateAuthors();
}

void SubtabBooks::getBookDetails(QListWidgetItem *item)
{
    if (!item) return;
    Book book = database->getBookByTitle(item->text());
    emit updateBookDetails(book);
}

void SubtabBooks::getSyncDetails()
{
    if (isSyncing) return;
    QStringList arguments;
    arguments << "sync_books.py" << ("\'" + bookData->getUnsavedBook().getTitle() + "\'");

    script = new QProcess(this);
    try
    {
        connect(script, SIGNAL(readyReadStandardOutput()), this, SLOT(getSyncDetailsForReal()));
        connect(script, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(getSyncDetailsFinished(int, QProcess::ExitStatus)));
        script->start("python2", arguments);
        isSyncing = true;
        syncingRow = bookList->currentRow();
        syncingPath = new QString(bookData->getBook().getFilePath());
    }
    catch (...)
    {
        //TO DO
    }
}

void SubtabBooks::getSyncDetailsForReal()
{
    QByteArray b = script->readAllStandardOutput();

    QStringList str = QString(b).split("\n");
    if (str.value(0) == "ERROR" && str.value(1) == "ERROR" && str.value(2) == "ERROR")
        return;

    int currentRow = bookList->currentRow();
    Book newBook(*syncingPath, str.value(0), str.value(1), database->getBook(*syncingPath).getYear(), str.value(2));
    database->editBook(newBook);
    bookList->item(syncingRow)->setText(str.value(0));
    bookList->setCurrentRow(currentRow);
    getBookDetails(bookList->item(syncingRow));
    emit updateAuthors();
}

void SubtabBooks::getSyncDetailsFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode != 0 || exitStatus == QProcess::CrashExit)
    {
        //TO DO
        return;
    }
    isSyncing = false;
    delete syncingPath;
    delete script;
}

void SubtabBooks::getBrowsePaths(QStringList browsePaths)
{
    QString text;
    for (int index = 0; index < browsePaths.size() - 1; index++)
        text.append(browsePaths.value(index));
    text.append(browsePaths.value(browsePaths.size() - 1));
    if (!folderPaths->text().isEmpty()) text.prepend(",");

    folderPaths->setText(folderPaths->text().append(text));
}

void SubtabBooks::getBookPaths(QStringList bookPaths)
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
