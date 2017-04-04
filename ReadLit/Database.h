#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Book.h"
#include "Author.h"

//Singleton
class Database
{
public:
	static Database& db();
	Database(Database const&) = delete;
	void operator = (Database const&) = delete;

	void addBook(const Book& b);
	void addAuthor(const Author& a);
	

	std::vector<Book> getBooks() { return books; }

private:
	Database();

	void removeBook(const std::string& bookName); //Vedem mai incolo
	void removeAuthor(const std::string& authorName); //Vedem mai incolo

	std::vector<Book> books;
	std::vector<Author> authors;

};

#endif //DATABASE_H