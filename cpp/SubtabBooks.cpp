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
    Book book = database->getBookByTitle(item->text());
    emit updateBookDetails(book);
}

void SubtabBooks::getSyncDetails()
{
    SyncWorker *worker = new SyncWorker(this, SyncWorker::BOOK, bookData->getUnsavedBook().getTitle(), bookData->getBook().getFilePath(), bookList->currentRow());
    connect(worker, SIGNAL(sendSyncDetails(QStringList, QString, int)), this, SLOT(getSyncDetailsDone(QStringList, QString, int)));
    connect(worker, SIGNAL(error(QString, SyncWorker*)), this, SLOT(getSyncDetailsError(QString, SyncWorker*)));
    worker->start();
}

void SubtabBooks::getSyncDetailsDone(const QStringList &details, const QString& path, int row)
{
    int currentRow = bookList->currentRow();
    QString description;
    for (int index = 2; index < details.size(); index++)
        description.append(details.value(index) + " ");
    Book newBook(path, details.value(0), details.value(1), database->getBook(path).getYear(), description);
    database->editBook(newBook);
    bookList->item(row)->setText(details.value(0));
    bookList->setCurrentRow(currentRow);
    emit updateAuthors();
}

void SubtabBooks::getSyncDetailsError(const QString &error, SyncWorker *worker)
{
    qDebug() << "SubtabBooks::getSyncDetailsError - Error: " << error;
    QMessageBox messageBox;
    messageBox.critical(0, "ERROR", "There was an error syncing: " + error);
    delete worker;
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
