#include "Author.h"



Author::Author()
{
	name = "Warning: author name not set";
	yearBirth = 0;
	yearDeath = 0;
	bio = " ";
}

Author::Author(const std::string& _name, const std::vector<std::string>& _books, const int& _yearBirth, const int& _yearDeath, const std::string& _bio)
{
	name = _name;
	books = _books;
	yearBirth = _yearBirth;
	yearDeath = _yearDeath;
	bio = _bio;
}

Author::Author(const Author& a)
{
	name = a.name;
	books = a.books;
	yearBirth = a.yearBirth;
	yearDeath = a.yearDeath;
	bio = a.bio;
}

Author& Author::operator = (const Author& a)
{
	if (this == &a) return *this;

	name = a.name;
	books = a.books;
	yearBirth = a.yearBirth;
	yearDeath = a.yearDeath;
	bio = a.bio;

	return *this;
}

void Author::addBook(const std::string& b)
{
	books.push_back(b);
}

void Author::addBook(const Book& b)
{
	books.push_back(b.getTitle());
}

std::string Author::getName() const
{
	return name;
}

std::vector<std::string> Author::getBooks() const
{
	return books;
}

int Author::getYearBirth() const
{
	return yearBirth;
}

int Author::getYearDeath() const
{
	return yearDeath;
}

std::string Author::getBio() const
{
	return bio;
}

Author::~Author()
{
}

bool Author::operator == (const Author& a) const
{
	if (name == a.name && books == a.books && yearBirth == a.yearBirth && yearDeath == a.yearDeath && bio == a.bio) return true;
	return false;
}