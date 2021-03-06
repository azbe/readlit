#ifndef BOOKTABLE_H
#define BOOKTABLE_H

#include <QTableWidget>
#include <QProcess>
#include <QHeaderView>
#include <qdebug.h>
#include "src/Book.h"

class BookTable : public QTableWidget
{
    Q_OBJECT

public:
    BookTable(QWidget *parent = 0);
    ~BookTable();

    Book getBook();
    Book getUnsavedBook();

signals:
    void updateBook(const Book& book);

public slots:
    void setBook(const Book& book);
    void saveBook();
    void clear();

private:
    Book *book;
    QTableWidgetItem *header;
    QTableWidgetItem *path;
    QTableWidgetItem *title;
    QTableWidgetItem *author;
    QTableWidgetItem *year;
    QTableWidgetItem *summary;
};

#endif // BOOKTABLE_H
