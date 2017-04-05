#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Book.h"
#include "Author.h"

//Singleton
class Database
{
	friend class Mediator;
public:
	static Database& getInstance();
	Database(Database const&) = delete;
	void operator = (Database const&) = delete;

	void addBook(const Book& b);
	void removeBook(const QString& bookName); 
	
	Book getBook(const QString& bookName) const;
	Author getAuthor(const QString& name) const;

	std::vector<Book> getBooks() const;
	std::vector<Author> getAuthors() const;

private:
	Database();
	
	std::vector<Book> books;
	std::vector<Author> authors;

};

#endif //DATABASE_H