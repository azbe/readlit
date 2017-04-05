#ifndef LISTCONTAINER_H
#define LISTCONTAINER_H
#include <vector>

#include <QWidget>
#include <QLabel.h>

#include "Book.h"

//Partea din Local cu lista de carti/autori (va cere bazei de date datele)

class ListContainer : public QWidget
{
	friend class Mediator;
public:
	enum containerType { BOOKS, AUTHORS};

	ListContainer(QWidget *parent, const containerType& type);
	//ListContainer(const ListContainer& lc);
	//ListContainer& operator =(const ListContainer& lc);
	~ListContainer();

	std::vector<QString> getItems() const;

private:
	std::vector<QLabel> items;
	QGridLayout *layout;
};

#endif //LISTCONTAINER_H