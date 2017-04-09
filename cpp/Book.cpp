#include "src/Book.h"

Book::Book()
{
	title = "Warning: book title not set";
	year = 0;
	description = " ";
}

Book::Book(const QString& _title, const QString& _author, const QString& _filePath, const int& _year, const QString& _description)
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

QString Book::getTitle() const
{
	return title;
}

QString Book::getAuthor() const
{
	return author;
}

QString Book::getFilePath() const
{
	return filePath;
}

int Book::getYear() const
{
	return year;
}

QString Book::getDescription() const
{
	return description;
}

bool Book::operator == (const Book& b) const
{
	if (title == b.title && author == b.author && filePath == b.filePath && year == b.year && description == b.description) return true;
	return false;
}
