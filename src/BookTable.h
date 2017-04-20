#ifndef BOOKTABLE_H
#define BOOKTABLE_H

#include <QTableWidget>

#include "src/Book.h"

class BookTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit BookTable(QWidget *parent = 0);
    ~BookTable();

public slots:
    void setBook(const Book& book);

private:
    QTableWidgetItem *header;
    QTableWidgetItem *path;
    QTableWidgetItem *title;
    QTableWidgetItem *author;
    QTableWidgetItem *year;
    QTableWidgetItem *summary;
};

#endif // BOOKTABLE_H
