#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
public:
	Book();
	Book(const std::string& _title, const std::string& _author, const std::string& _filePath, const int& _year = 0, const std::string& _description = " ");
	Book(const Book& b);
	Book& operator = (const Book& b);
	~Book();

	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getFilePath() const;
	int getYear() const;
	std::string getDescription() const;

private:
	std::string title;
	std::string author;
	std::string filePath;
	int year;
	std::string description;
	//Si altele
};

#endif //BOOK_H