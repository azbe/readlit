#include "Book.h"

Book::Book()
{
	title = "Warning: book title not set";
	year = 0;
	description = " ";
}

Book::Book(const std::string& _title, const std::string& _author, const std::string& _filePath, const int& _year, const std::string& _description)
{
	title = _title;
	author = _author;
	filePath = _filePath;
	year = _year;
	description = _description;
}

Book::Book(const Book& b)
{
	title = b.title;
	author = b.author;
	filePath = b.filePath;
	year = b.year;
	description = b.description;
}

Book& Book::operator = (const Book& b)
{
	if (this == &b) return *this;

	title = b.title;
	author = b.author;
	filePath = b.filePath;
	year = b.year;
	description = b.description;

	return *this;
}


Book::~Book()
{
}

std::string Book::getTitle() const
{
	return title;
}

std::string Book::getAuthor() const
{
	return author;
}

std::string Book::getFilePath() const
{
	return filePath;
}

int Book::getYear() const
{
	return year;
}

std::string Book::getDescription() const
{
	return description;
}

bool Book::operator == (const Book& b) const
{
	if (title == b.title && author == b.author && filePath == b.filePath && year == b.year && description == b.description) return true;
	return false;
}