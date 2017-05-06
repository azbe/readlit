#include "src/SubtabAuthors.h"
#include <qdebug.h>

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
    authorDataTable = new AuthorTable(authorData);
    connect(this, SIGNAL(updateAuthorDetails(Author)), authorDataTable, SLOT(setAuthor(Author)));
    connect(authorDataTable, SIGNAL(updateAuthor(Author)), this, SLOT(saveNewAuthor(Author)));
	for (int i = 0; i < 4; i++)
	{
		QString text;
        dataButtons[i] = new DataButton(text, authorData);
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
                connect(dataButtons[i], SIGNAL(clicked(bool)), authorDataTable, SLOT(saveAuthor()));
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
                connect(dataButtons[i], SIGNAL(clicked(bool)), authorDataTable, SLOT(clear()));
                break;
            }
		}
        //text += " Author Data";
        dataButtons[i]->setText(text);
		dataButtons[i]->setMaximumWidth(UIConstants::DATA_BUTTON_DEFAULT_MAX_SIZE);
		dataButtons[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
		authorDataLayout->addWidget(dataButtons[i], 0, i, 1, 1);
	}
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

void SubtabAuthors::saveNewAuthor(const Author &author)
{
    database->editAuthor(author);
}

void SubtabAuthors::newScan()
{
    QStringList authors = database->getAuthorNames();
    authorList->clear();
    authorList->addItems(authors);
    if (authorList->count() > 0)
    {
        authorList->setCurrentRow(0);
        updateAuthorBooks(authorList->item(0));
    }
}

void SubtabAuthors::getSyncDetails()
{
    SyncWorker *worker = new SyncWorker(this, SyncWorker::AUTHOR, authorDataTable->getUnsavedName(), authorDataTable->getAuthor().getName(), authorList->currentRow());
    connect(worker, SIGNAL(sendSyncDetails(QStringList, QString, int)), this, SLOT(getSyncDetailsDone(QStringList, QString, int)));
    connect(worker, SIGNAL(error(QString, SyncWorker*)), this, SLOT(getSyncDetailsError(QString, SyncWorker*)));
    worker->start();
}

void SubtabAuthors::getSyncDetailsDone(const QStringList &details, const QString &name, int row)
{
    int currentRow = authorList->currentRow();
    QString description;
    for (int index = 1; index < details.size(); index++)
        description.append(details.value(index) + " ");
    Author newAuthor(details.value(0), database->getAuthor(name).getVector(), database->getAuthor(name).getYearBirth(), database->getAuthor(name).getYearDeath(), description);
    database->editAuthor(newAuthor);
    authorList->item(row)->setText(details.value(0));
    authorList->setCurrentRow(currentRow);
}

void SubtabAuthors::getSyncDetailsError(const QString &err, SyncWorker *worker)
{
    qDebug() << "SutbabAuthors::getSyncDetailsError - Error: " << err;
    QMessageBox messageBox;
    messageBox.critical(0, "ERROR", "There was an error syncing: " + err);
    delete worker;
}

void SubtabAuthors::updateAuthorBooks(QListWidgetItem *item)
{
    if (!item) return;
    Author author = database->getAuthor(item->text());
    emit updateAuthorDetails(author);
    std::vector<QString> books = author.getVector();
    authorBooks->clear();
    for (unsigned i = 0; i < books.size(); i++)
        authorBooks->addItem(books[i]);
}
