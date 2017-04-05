#include <QGridLayout.h>

#include "ListContainer.h"
#include "Database.h"

#define db Database::getInstance()

ListContainer::ListContainer(QWidget* parent, const containerType& type)
{
	if(parent) setParent(parent);

	switch (type)
	{
		case BOOKS:
		{
			std::vector<Book> books = db.getBooks();
			for (Book b : books)
				items.push_back(b.getTitle());
			break;
		}
		case AUTHORS:
		{
			std::vector<Author> authors = db.getAuthors();
			for (Author a : authors)
				items.push_back(a.getName());
			break;
		}
	}

	for (QString label : items)
	{
		addItem(label);
	}
}

/*
ListContainer::ListContainer(const ListContainer& lc)
{
	setParent(lc.parentWidget());
	items = lc.items;
}

ListContainer& ListContainer::operator = (const ListContainer& lc)
{
	if (this == &lc) return *this;
	items = lc.items;
	return *this;
}
*/

ListContainer::~ListContainer()
{
}


std::vector<QString> ListContainer::getItems() const
{
	return items;
}