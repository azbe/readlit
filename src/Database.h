#pragma once

#include <QObject>

class QString;
class Author;
class Book;
class QJsonObject;
class QJsonArray;
class QJsonDocument;

class DataBase
{
public:
    DataBase(const QString &filename);
    ~DataBase();

    DataBase();
    QString getFileName();
    Author getAuthor(const QString& authorName);
    Book getBook(const QString& filePath);

    bool addNewBook(const Book &book);
    bool addNewAuthor(const Author &author);

private:
    QString *filename;
};
