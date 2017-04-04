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

void ListContainer::removeItem(const int& index, const bool& book = true)
{
	if (book) books.erase(books.begin() + index);
	else authors.erase(books.begin() + index);
}

ListContainer::ListContainer(const ListContainer& lc)
{
	books.clear();
	books = lc.getBooks();
	authors.clear();
	authors = lc.getAuthors();
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