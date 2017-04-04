#include "ListContainer.h"

ListContainer::ListContainer(QWidget* parent)
{
	setParent(parent);
}

void ListContainer::addItem(std::string item, const bool& book)
{
	if (book) books.push_back(item);
	else authors.push_back(item);
}

void ListContainer::removeItem(const int& index, const bool& book)
{
	//TODO: exceptions
	if (index < 0 || ((book) ? (index >= books.size()) : (index >= authors.size()))) return;
	if (book) books.erase(books.begin() + index);
	else authors.erase(authors.begin() + index);
}

ListContainer::ListContainer(const ListContainer& lc)
{
	books = lc.getBooks();
	authors = lc.getAuthors();
}

ListContainer& ListContainer::operator = (const ListContainer& lc)
{
	if (this == &lc) return *this;

	books = lc.getBooks();
	authors = lc.getAuthors();
	
	return *this;
}

ListContainer::~ListContainer()
{
}

std::vector<std::string> ListContainer::getBooks() const
{
	return books;
}

std::vector<std::string> ListContainer::getAuthors() const
{
	return authors;
}