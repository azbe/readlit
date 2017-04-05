#ifndef LISTCONTAINER_H
#define LISTCONTAINER_H
#include <vector>

#include <QListWidget>
#include <QLabel.h>

#include "Book.h"

//Partea din Local cu lista de carti/autori (va cere bazei de date datele)

class ListContainer : public QListWidget
{
	friend class Mediator;
public:
	enum containerType { BOOKS, AUTHORS, NOTHING};

	ListContainer(QWidget *parent, const containerType& type);
	//ListContainer(const ListContainer& lc);
	//ListContainer& operator =(const ListContainer& lc);
	~ListContainer();

	std::vector<QString> getItems() const;

private:
	std::vector<QString> items;
};

#endif //LISTCONTAINER_H