#ifndef SUBTABAUTHORS_H
#define SUBTABAUTHORS_H

#include <QWidget>
#include <QLayout>

#include "DataList.h"

class SubtabAuthors : public QWidget
{
public:
	SubtabAuthors(QWidget *parent);
	~SubtabAuthors();

private:
	DataList *authors;
	DataList *authorBooks;
	QWidget *authorData;
	QLayout *authorLayout;
};

#endif //SUBTABAUTHORS_H