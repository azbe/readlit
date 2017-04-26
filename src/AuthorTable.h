#ifndef AUTHORTABLE_H
#define AUTHORTABLE_H

#include <QTableWidget>

#include "src/Author.h"

class AuthorTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit AuthorTable(QWidget *parent = 0);
    ~AuthorTable();

public slots:
    void setAuthor(const Author& author);

private:
    Author *author;
    QTableWidgetItem *header;
    QTableWidgetItem *name;
    QTableWidgetItem *yearBirth;
    QTableWidgetItem *yearDeath;
    QTableWidgetItem *bio;
};

#endif // AUTHORTABLE_H
