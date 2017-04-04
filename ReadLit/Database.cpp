#include "Database.h"

Database& Database::db()
{
	static Database db;
	return db;
}

Database::Database(){}

void Database::addBook(const Book& b)
{
	books.push_back(b);

	bool found = false;
	for (auto a : authors)
	{
		if (a.getName() == b.getAuthor())
		{
			a.addBook(b.getTitle());
			found = true;
		}
	}
	if (!found)
	{
		std::vector<std::string> book;
		book.push_back(b);
		authors.push_back(Author(b.getAuthor(), book));
	}
}

void Database::removeBook(const std::string& bookName)
{
	bool found = true;
	while (found)
	{
		found = false;
		for (int index = 0; index < books.size() && !found; index++)
		{
			if (books[index].getTitle() == bookName)
			{
				books.erase(books.begin() + index);
				found = true;
			}
		}
	}
}

void Database::addAuthor(const Author& a)
{
	authors.push_back(a);
	//TODO: Se cauta daca exista cartea si daca nu, se adauga o carte cu minim de informatii
}

void Database::removeAuthor(const std::string& authorName)
{
	bool found = true;
	while (found)
	{
		found = false;
		for (int index = 0; index < authors.size() && !found; index++)
		{
			if (authors[index].getName() == authorName)
			{
				authors.erase(authors.begin() + index);
				found = true;
			}
		}
	}
}