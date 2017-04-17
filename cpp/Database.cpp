#include "src/Database.h"
#include "src/Book.h"
#include "src/Author.h"

#include <QDebug>
#include <QMap>
#include <QFile>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <iostream>
#include <map>

DataBase::DataBase()
{

}

bool DataBase::addBook(const Book &NewBook)
{
    if(books.count(NewBook.getFilePath()) != 0)
    {
        //TODO EROARE
        qWarning("The book is already in the database!");
        return false;
    }
    books.insert(std::pair<QString, Book>(NewBook.getFilePath(), NewBook));
    return true;
}

bool DataBase::deleteBook(const QString &pathID)
{
    if(books.count(pathID) == 0)
    {
        return false;
    }
    books.erase(pathID);
    return true;
}

bool DataBase::addAuthor(Author _author)
{
    if(authors.count(_author.getName()) != 0)
    {
        //TODO eroare , nu s-a putut adauga deoarece exista deja
        return false;
    }
    authors.insert(std::pair<QString, Author>(_author.getName(), _author));
    return true;
}

bool DataBase::deleteAuthor(const QString &name)
{
    if(authors.count(name) == 0)
    {
        return false;
    }
    authors.erase(name);
    return true;
}

Book DataBase::getBook(const QString &PathID)
{
    try
    {
        if(books.count(PathID) == 0)
        {
            throw "Book not found";
        }
        return books[PathID];
    }catch(char *exception)
    {
        //qWarning(exception);
        //todo eroare extragere carte
        qDebug() << exception;
    }
    return Book();
}

Author DataBase::getAuthor(const QString &name)
{
    if(authors.count(name) == 0)
    {
        //todo error;
        return Author();
    }
    return authors[name];
}

void DataBase::write(QJsonObject &json)
{
    QJsonArray booksArray;
    for(std::map<QString, Book>::iterator it = books.begin(); it != books.end(); it++)
    {
        Book temp = it->second;
        QJsonObject bookObject;
        temp.write(bookObject);
        booksArray.append(bookObject);
    }
    json["books"] = booksArray;

    QJsonArray authorsArray;
    for(std::map<QString, Author>::iterator it = authors.begin(); it != authors.end(); it++)
    {
        Author temp = it->second;
        QJsonObject authorObject;
        temp.write(authorObject);
        authorsArray.append(authorObject);
    }
    json["authors"] = authorsArray;
}

void DataBase::read(const QJsonObject &JsonObj)
{
    books.clear();
    QJsonArray booksArray = JsonObj["books"].toArray();
    for(int index = 0; index < booksArray.size(); index++)
    {
        QJsonObject bookObject = booksArray[index].toObject();
        Book book;
        book.read(bookObject);
        books.insert(std::pair<QString, Book>(book.getFilePath(), book));
    }

    authors.clear();
    QJsonArray authorsArray = JsonObj["authors"].toArray();
    for(int index = 0; index < authorsArray.size(); index++)
    {
        QJsonObject authorObject = authorsArray[index].toObject();
        Author _author;
        _author.read(authorObject);
        authors.insert(std::pair<QString, Author>(_author.getName(), _author));
    }
}

void DataBase::save(const QString &fileName)
{
    QFile saveFile(fileName);

    if(!saveFile.exists() || !saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file!");
        return;
    }

    QJsonObject booksObject;
    write(booksObject);
    QJsonDocument saveDoc(booksObject);
    saveFile.write(saveDoc.toJson());
}

void DataBase::load(const QString &fileName)
{
    QFile savedFile(fileName);

    if(!savedFile.exists() || !savedFile.open(QIODevice::ReadOnly))
    {
        qWarning("couldnt open the file");
        return;
    }

    QByteArray savedData = savedFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));
    read(loadDoc.object());
}

