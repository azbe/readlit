#ifndef BOOK_H
#define BOOK_H

class Book
{
public:
	Book();
	~Book();

private:
	std::string title;
	Author author;
	int year;
	std::string description;
	//Si altele
};

#endif //BOOK_H