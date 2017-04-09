#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
	friend class Database;
public:
	Book();
	Book(const QString& _title, const QString& _author, const QString& _filePath, const int& _year = 0, const QString& _description = " ");
	Book(const Book& b);
	Book& operator = (const Book& b);
	~Book();

	QString getTitle() const;
	QString getAuthor() const;
	QString getFilePath() const;
	int getYear() const;
	QString getDescription() const;

	bool operator == (const Book& b) const;

private:
	QString title;
	QString author;
	QString filePath;
	int year;
	QString description;
	//Si altele
};

#endif //BOOK_H
