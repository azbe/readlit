#include "src/Book.h"

/*
 * bugs:
 * -variabilele initializate nu functioneaza
 * -variabilele sunt statice asa ca performanta nu e optima, mai ales cand foloseste constructorul predefinit in maps
 */

Book::Book() /*adaugat pentru functionalizarea cu mape si vectori */
{
    _exist = false;
}

Book::Book(const QString& _filePath,
           const QString& _title,
           const QString& _author,
           const QString& _year,
           const QString& _description)
{
    if (_title.isEmpty()) title = new QString(*filePath);
    else title = new QString(_title);
    author = new QString(_author);
    filePath = new QString(_filePath);
    year = new QString(_year);
    description = new QString(_description);
    _exist = true;
}

Book::Book(const Book& b)
{
    title = new QString(*b.title);
    author = new QString(*b.author);
    filePath = new QString(*b.filePath);
    year = new QString(*b.year);
    description = new QString(*b.description);
}

//de refactorizat
Book& Book::operator = (const Book& b)
{
    if (this == &b) return *this;

    title = new QString(*b.title);
    author = new QString(*b.author);
    filePath = new QString(*b.filePath);
    year = new QString(*b.year);
    description = new QString(*b.description);
    _exist = b._exist;

    return *this;
}


Book::~Book()
{
    delete title;
    delete author;
    delete filePath;
    delete year;
    delete description;
}

QString Book::getTitle() const
{
    return *title;
}

QString Book::getAuthor() const
{
    return *author;
}

QString Book::getFilePath() const
{
    return *filePath;
}

QString Book::getYear() const
{
    return *year;
}

QString Book::getDescription() const
{
    return *description;
}

QString Book::getYearInt() const
{
    return *year;
}

bool Book::operator == (const Book& b) const
{
    if (*filePath == *b.filePath) return true;
    return false;
}

void Book::write(QJsonObject &json)
{
    json["title"] = *title;
    json["author"] = *author;
    json["filePath"] = *filePath;
    json["year"] = *year;
    json["description"] = *description;
}

void Book::read(const QJsonObject &json)
{
    title = new QString(json["title"].toString());
    author = new QString(json["author"].toString());
    filePath = new QString(json["filePath"].toString());
    year = new QString(json["year"].toString());
    description = new QString(json["description"].toString());
}

bool Book::exists() const
{
    return _exist;
}

