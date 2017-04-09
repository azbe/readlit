#ifndef AUTHOR_H
#define AUTHOR_H

#include <qstring.h>

#include <vector>

#include "Book.h"

class Author
{
	friend class Database;
public:
	Author();
	Author(const QString& _name, const std::vector<QString>& _books, const int& yearBirth = 0, const int& yearDeath = 0, const QString& _bio = " ");
	Author(const Author& a);
	Author& operator = (const Author& a);
	~Author();

	void addBook(const QString& b);
	void addBook(const Book& b);

	QString getName() const;
	std::vector<QString> getBooks() const;
	int getYearBirth() const;
	int getYearDeath() const;
	QString getBio() const;

	bool operator == (const Author& a) const;

private:
	QString name; //Last+First name, nume si prenume
	std::vector<QString> books; //Oriunde avem carti, eficientizam pastrand doar titlul si cautand cartea in baza de date
	int yearBirth;
	int yearDeath;
	QString bio;
	//Si altele
};

#endif //AUTHOR_H