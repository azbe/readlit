#ifndef BOOKDETAILSCONTAINER_H
#define BOOKDETAILSCONTAINER_H

#include <QWidget>

#include "Book.h"

class BookDetailsContainer : public QWidget
{
	Q_OBJECT

public:
	BookDetailsContainer(QWidget *parent);
	~BookDetailsContainer();

private:
	std::string bookTitle;
	
};

#endif //BOOKDETAILSCONTAINER_H