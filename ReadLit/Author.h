#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <vector>

#include "Book.h"

class Author
{
	friend class Database;
public:
	Author();
	Author(const std::string& _name, const std::vector<std::string>& _books, const int& yearBirth = 0, const int& yearDeath = 0, const std::string& _bio = " ");
	Author(const Author& a);
	Author& operator = (const Author& a);
	~Author();

	void addBook(const std::string& b);
	void addBook(const Book& b);

	std::string getName() const;
	std::vector<std::string> getBooks() const;
	int getYearBirth() const;
	int getYearDeath() const;
	std::string getBio() const;

	bool operator == (const Author& a) const;

private:
	std::string name; //Last+First name, nume si prenume
	std::vector<std::string> books; //Oriunde avem carti, eficientizam pastrand doar titlul si cautand cartea in baza de date
	int yearBirth;
	int yearDeath;
	std::string bio;
	//Si altele
};

#endif //AUTHOR_H