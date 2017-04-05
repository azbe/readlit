#include "Database.h"

Database& Database::getInstance()
{
	static Database database;
	return database;
}

Database::Database(){}

void Database::addBook(const Book& b)
{
	//TODO EXCEPTIONS!!!

	bool found = false;
	for (auto book : books)
	{
		if (book.title == b.title)
			return;
	}

	books.push_back(b);

	bool found = false;
	for (auto a : authors)
	{
		if (a.name == b.author)
		{
			a.addBook(b.title);
			found = true;
		}
	}
	if (!found)
	{
		std::vector<std::string> book;
		book.push_back(b.title);
		authors.push_back(Author(b.author, book));
	}
}

void Database::removeBook(const std::string& bookName)
{
	int found = -1;
	for (int index = 0; index < books.size() && found > -1; index++)
	{
		if (books[index].title == bookName)
		{
			books.erase(books.begin() + index);
			found = index;
		}
	}
	if (found > -1)
	{
		found = -1;
		for (int index = 0; index < authors.size() && !found; index++)
		{
			for (int index2 = 0; index2 < authors[index].books.size() && !found; index2++)
			{
				if (authors[index].books[index2] == bookName)
				{
					authors[index].books.erase(authors[index].books.begin() + index2);
					found = index;
				}
			}
		}
		if (found > -1)
		{
			if (authors[found].books.size() == 0)
				authors.erase(authors.begin() + found);
		}
	}
}

Book Database::getBook(const std::string& bookName) const
{
	for (auto b : books)
		if (b.title == bookName)
			return b;
}

Book Database::getBook(const int& index) const
{
	if (index < 0 || index >= books.size()) return;
	return books[index];
}

Author Database::getAuthor(const std::string& name) const
{
	for (auto a : authors)
		if (a.name == name)
			return a;
}

Author Database::getAuthor(const int& index) const
{
	if (index < 0 || index >= authors.size()) return;
	return authors[index];
}

std::vector<Book> Database::getBooks() const
{
	return books;
}

std::vector<Author> Database::getAuthors() const
{
	return authors;
}