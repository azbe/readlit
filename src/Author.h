#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>

class Book;
class QJsonArray;
class QJsonObject;

class Author
{
public:
    Author();
    explicit Author(const QString & name, std::vector<QString> books, const int & yearBirth, const int & yearDeath, const QString & bio);
    Author(const Author & a);
    Author& operator = (const Author & a);
    bool operator ==(const Author &a) const;

    ~Author();

    QString getName();
    QString getBio();
    std::vector<QString> getVector();
    int getYearBirth();
    int getYearDeath();

    bool addBook(const QString & book)
    {

        books.push_back(book);
        return true;
    }

private:
    QString name;
    std::vector<QString> books;//Oriunde avem carti, optimizam eficienta pastrand doar titlul si cautand cartea in baza de date
    int yearBirth;
    int yearDeath;
    QString bio;
};

#endif // AUTHOR_H
