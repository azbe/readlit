#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Book.h"

class Database
{
public:
	Database();
	~Database();

private:
	std::vector<Book> books;

};

#endif //DATABASE_H