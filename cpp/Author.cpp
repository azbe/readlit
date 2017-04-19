#include "src/Author.h"

/*
* bugs:
* -variabilele initializate nu functioneaza
*/
Author::Author()
{
    _exist = false;
}



Author::Author(const QString &name,
               std::vector<QString> books,
               const int &yearBirth,
               const int &yearDeath,
               const QString &bio)
{
    this->name = new QString(name);
    this->books = new std::vector<QString>(books);
    this->yearBirth = new int(yearBirth);
    this->yearDeath = new int(yearDeath);
    this->bio = new QString(bio);
    this->_exist = true;
}

Author::Author(const Author & a)
{
    name = new QString(*a.name);
    books = new std::vector<QString>(*a.books);
    yearBirth = new int(*a.yearBirth);
    yearDeath = new int(*a.yearDeath);
    bio = new QString(*a.bio);
    _exist = a._exist;
}

Author& Author::operator =(const Author &a)
{
    if (this == &a) return *this;

    name = new QString(*a.name);
    books = new std::vector<QString>(*a.books);
    yearBirth = new int(*a.yearBirth);
    yearDeath = new int(*a.yearDeath);
    bio = new QString(*a.bio);
    _exist = a._exist;

    return *this;
}

bool Author::operator ==(const Author &a) const
{
    if(*name == *a.name)
        return true;
    return false;
}

Author::~Author()
{
    delete name;
    delete books;
    delete yearBirth;
    delete yearDeath;
    delete bio;
}

QString Author::getName() const
{
    return *name;
}

QString Author::getBio() const
{
    return *bio;
}

std::vector<QString> Author::getVector() const
{
    return *books;
}

int Author::getYearBirth() const
{
    return *yearBirth;
}

int Author::getYearDeath() const
{
    return *yearBirth;
}

bool Author::addBook(const QString &book)
{
    //todo verificare, poate afecta complexitatea
    books->push_back(book);
    return true;
}

bool Author::exist()
{
    return _exist;
}

void Author::write(QJsonObject &json) const
{
    json["name"] = *name;
    QJsonArray booksJsonArray;
    foreach(const QString bookName, *books)
    {
        //qDebug() << bookName;
        booksJsonArray.append(bookName);
    }
    json["AuthorBooks"] = booksJsonArray;
    json["yearBirth"] = *yearBirth;
    json["yearDeath"] = *yearDeath;
    json["bio"] = *bio;
}

void Author::read(const QJsonObject &json)
{
    name = new QString(json["name"].toString());
    books = new std::vector<QString>();
    QJsonArray booksJsonArray = json["AuthorBooks"].toArray();
    for(int index = 0; index < booksJsonArray.size(); index++)
    {
        QString bookName = booksJsonArray[index].toString();
        books->push_back(bookName);
        qDebug() << bookName;
    }
    yearBirth = new int(json["yearBirth"].toInt());
    yearDeath = new int(json["yearDeath"].toInt());
    bio = new QString(json["bio"].toString());
}

