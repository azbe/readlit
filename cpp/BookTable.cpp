#include <QHeaderView>

#include "src/BookTable.h"

BookTable::BookTable(QWidget *parent) : QTableWidget(parent)
{
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
}

void BookTable::setBook(const Book& book)
{
    item(0,0)->setText(book.getFilePath());
    item(1,0)->setText(book.getTitle());
    item(2,0)->setText(book.getAuthor());
    item(3,0)->setText(QString::number(book.getYear()));
    item(4,0)->setText(book.getDescription());
}

BookTable::~BookTable()
{
    delete summary;
    delete year;
    delete author;
    delete title;
    delete path;
    delete header;
}
