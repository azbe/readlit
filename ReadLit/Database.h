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
	void removeBook(const std::string& bookName); 
	
	Book getBook(const std::string& bookName) const;
	Book getBook(const int& index) const;

	Author getAuthor(const std::string& name) const;
	Author getAuthor(const int& index) const;

	std::vector<Book> getBooks() const;
	std::vector<Author> getAuthors() const;

private:
	Database();
	
	std::vector<Book> books;
	std::vector<Author> authors;

};

#endif //DATABASE_H