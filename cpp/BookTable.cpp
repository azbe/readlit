#include "src/BookTable.h"

BookTable::BookTable(QWidget *parent) : QTableWidget(parent)
{
    book = 0;
    setColumnCount(1);
    setRowCount(5);

    header = new QTableWidgetItem();
    setHorizontalHeaderItem(0, header);

    path = new QTableWidgetItem("Path");
    setVerticalHeaderItem(0, path);
    setItem(0, 0, new QTableWidgetItem());
    item(0,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item(0,0)->setFlags(item(0,0)->flags() ^ Qt::ItemIsEditable);

    title = new QTableWidgetItem("Title");
    setVerticalHeaderItem(1, title);
    setItem(1, 0, new QTableWidgetItem());
    item(1,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    author = new QTableWidgetItem("Author");
    setVerticalHeaderItem(2, author);
    setItem(2, 0, new QTableWidgetItem());
    item(2,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    year = new QTableWidgetItem("Year");
    setVerticalHeaderItem(3, year);
    setItem(3, 0, new QTableWidgetItem());
    item(3,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    summary = new QTableWidgetItem("Summary");
    setVerticalHeaderItem(4, summary);
    setItem(4, 0, new QTableWidgetItem());
    item(4,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    setGridStyle(Qt::SolidLine);
    horizontalHeader()->setVisible(false);
    horizontalHeader()->setCascadingSectionResizes(true);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setCascadingSectionResizes(true);
    verticalHeader()->setDefaultSectionSize(30);
    verticalHeader()->setStretchLastSection(true);

    isSyncing = false;
}

Book BookTable::getBook()
{
    return *book;
}

void BookTable::setBook(const Book& book)
{
    this->book = new Book(book);
    item(0,0)->setText(book.getFilePath());
    item(1,0)->setText(book.getTitle());
    item(2,0)->setText(book.getAuthor());
    item(3,0)->setText(QString::number(book.getYear()));
    item(4,0)->setText(book.getDescription());
}

void BookTable::saveBook()
{
    QString title = item(1,0)->text();
    QString author = item(2,0)->text();
    int year = book->getYear();
    try
    {
        year = item(3,0)->text().toInt();
    }
    catch (...) {} //TO DO
    QString summary = item(4,0)->text();

    Book newBook(book->getFilePath(), title, author, year, summary);
    this->book = new Book(newBook);
    emit updateBook(newBook);
}

void BookTable::syncBook()
{
    if (isSyncing) return;
    QStringList arguments;
    arguments << "sync_books.py" << ("\'" + item(1,0)->text() + "\'");

    script = new QProcess(this);
    try
    {
        connect(script, SIGNAL(readyReadStandardOutput()), this, SLOT(getSyncBook()));
        connect(script, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finishedSyncBook(int, QProcess::ExitStatus)));
        script->start("python2", arguments);
        isSyncing = true;
    }
    catch (...)
    {
        //TO DO
    }
}

void BookTable::getSyncBook()
{
    QByteArray b = script->readAllStandardOutput();

    QStringList str = QString(b).split("\n");
    item(1,0)->setText(str.value(0));
    item(2,0)->setText(str.value(1));
    item(4,0)->setText(str.value(2));
}

void BookTable::finishedSyncBook(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode != 0 || exitStatus == QProcess::CrashExit)
    {
        //TO DO
        return;
    }
    isSyncing = false;
}

void BookTable::clear()
{
    item(0,0)->setText(book->getFilePath());
    item(1,0)->setText(book->getTitle());
    item(2,0)->setText(book->getAuthor());
    item(3,0)->setText(QString::number(book->getYear()));
    item(4,0)->setText(book->getDescription());
}

BookTable::~BookTable()
{
    if (book) delete book;
    delete summary;
    delete year;
    delete author;
    delete title;
    delete path;
    delete header;
}
