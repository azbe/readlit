#ifndef SUBTABAUTHORS_H
#define SUBTABAUTHORS_H

#include <QWidget>
#include <QLayout>

#include "DataList.h"
#include "Database.h"

class SubtabAuthors : public QWidget
{
public:
    SubtabAuthors(QWidget *parent, DataBase& database);
	~SubtabAuthors();

private:
	DataList *authors;
	DataList *authorBooks;
	QWidget *authorData;
	QLayout *authorLayout;
};

#endif //SUBTABAUTHORS_H
