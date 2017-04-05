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
				items.push_back(QLabel(b.getTitle(), this));
			break;
		}
		case AUTHORS:
		{
			std::vector<Author> authors = db.getAuthors();
			for (Author a : authors)
				items.push_back(QLabel(a.getName(), this));
			break;
		}
	}

	layout = new QGridLayout(this);

	for (int index = 0; index < items.size(); index++)
		layout->setRowStretch(index, 1);
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
	std::vector<QString> it;
	for (int index = 0; index < items.size(); index++) 
		it.push_back(items[index].text());
	return it;
}