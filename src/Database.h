#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QFile>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <map>

#include "src/Book.h"
#include "src/Author.h"

class DataBase
{
public:
    DataBase();

    bool addBook(const Book &NewBook);
    bool deleteBook(const QString & pathID);
    bool addAuthor(Author _author);
    bool deleteAuthor(const QString & name);
    bool findBook(const QString &PathID);
    Book getBook(const QString &PathID);
    QStringList getBookTitles();
    Author getAuthor(const QString &name);
    QStringList getAuthorNames();


    void save(const QString & fileName);
    void load(const QString & fileName);
private:
    void write(QJsonObject &json);
    void read(const QJsonObject &JsonObj);

    std::map<QString, Book> books;
    std::map<QString, Author> authors;
};

#endif // DATABASE_H
