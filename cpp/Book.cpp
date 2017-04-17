#include "book.h"

#include <QString>
#include <QJsonObject>

/*
 * bugs:
 * -variabilele initializate nu functioneaza
 * -variabilele sunt statice asa ca performanta nu e optima, mai ales cand foloseste constructorul predefinit in maps
 */

Book::Book() /*adaugat pentru functionalizarea cu mape si vectori */
{
    title = "";
    author = "";
    filePath = "error no filePath";
    description = "";
    year = 0;
}

Book::Book(const QString& _filePath, const QString& _title = "", const QString& _author = "", const int& _year = 0, const QString& _description = "")
{
    title = _title;
    author = _author;
    filePath = _filePath;
    year = _year;
    description = _description;
}

Book::Book(const Book& b)
{
    title = b.title;
    author = b.author;
    filePath = b.filePath;
    year = b.year;
    description = b.description;
}

Book& Book::operator = (const Book& b)
{
    if (this == &b) return *this;

    title = b.title;
    author = b.author;
    filePath = b.filePath;
    year = b.year;
    description = b.description;

    return *this;
}


Book::~Book()
{
}

QString Book::getTitle() const
{
    return title;
}

QString Book::getAuthor() const
{
    return author;
}

QString Book::getFilePath() const
{
    return filePath;
}

int Book::getYear() const
{
    return year;
}

QString Book::getDescription() const
{
    return description;
}

bool Book::operator == (const Book& b) const
{
    if (title == b.title && author == b.author && filePath == b.filePath && year == b.year && description == b.description) return true;
    return false;
}

void Book::write(QJsonObject &json)
{
    json["title"] = title;
    json["author"] = author;
    json["filePath"] = filePath;
    json["year"] = year;
    json["description"] = description;
}

void Book::read(const QJsonObject &json)
{
    title = json["title"].toString() ;
    author = json["author"].toString();
    filePath = json["filePath"].toString();
    year = json["year"].toInt();
    description = json["description"].toString();
}

