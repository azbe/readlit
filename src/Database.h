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
    Book getBookByTitle(const QString& title);
    QStringList getBookTitles();
    bool findAuthor(const QString &name);
    Author getAuthor(const QString &name);
    QStringList getAuthorNames();
    bool editBook(const Book &newBook);
    bool editAuthor(const Author &newAuthor);
    bool addBookToAuthor(const QString& title, const QString& name);
    bool removeBookFromAuthor(const QString& title, const QString& name);

    void save(const QString & fileName);
    void load(const QString & fileName);
private:
    void write(QJsonObject &json);
    void read(const QJsonObject &JsonObj);

    std::map<QString, Book> books;
    std::map<QString, Author> authors;
};

#endif // DATABASE_H
