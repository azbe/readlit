#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class Book;
class Author;
class QString;
class QJsonObject;


class DataBase
{
public:
    DataBase();

    bool addBook(const Book & NewBook);
    bool deleteBook(const QString & pathID);
    bool addAuthor(Author _author);
    bool deleteAuthor(const QString & name);
    Book getBook(const QString &PathID);
    Author getAuthor(const QString &name);


    void save(const QString & fileName);
    void load(const QString & fileName);
private:
    void write(QJsonObject &json);
    void read(const QJsonObject &JsonObj);

    std::map<QString, Book> books;
    std::map<QString, Author> authors;
};

#endif // DATABASE_H
