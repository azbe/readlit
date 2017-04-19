#ifndef SUBTABBOOKS_H
#define SUBTABBOOKS_H

#include <QWidget>
#include <QLayout>

#include "src/Database.h"

class SubtabBooks : public QWidget
{
public:
    SubtabBooks(QWidget *parent, DataBase &database);
	~SubtabBooks();

private:
	QWidget *scanner;
	QWidget *books;
	QLayout *bookLayout;
};

#endif //SUBTABBOOKS_H
