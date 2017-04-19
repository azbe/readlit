#include "src/Database.h"

DataBase::DataBase()
{

}

bool DataBase::addBook(const Book& NewBook)
{
    if(books.count(NewBook.getFilePath()) != 0)
    {
        //TODO EROARE
        qWarning("The book is already in the database!");
        return false;
    }
    books.insert(std::pair<QString, Book>(NewBook.getFilePath(), NewBook));
    if (findAuthor(NewBook.getAuthor()))
        addBookToAuthor(NewBook.getTitle(), NewBook.getAuthor());
    else
    {
        addAuthor(Author(NewBook.getAuthor()));
        addBookToAuthor(NewBook.getTitle(), NewBook.getAuthor());
    }
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

bool DataBase::findBook(const QString &PathID)
{
    if (books.count(PathID) == 0) return false;
    return true;
}

Book DataBase::getBook(const QString &PathID)
{
    if(books.count(PathID) == 0)
    {
        return Book();
    }
    return books[PathID];
}

QStringList DataBase::getBookTitles()
{
    QStringList bookTitles;
    for (auto const &book : books)
        bookTitles.append(book.second.getTitle());
    return bookTitles;
}

bool DataBase::findAuthor(const QString& name)
{
    if(authors.count(name) == 0) return false;
    return true;
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

QStringList DataBase::getAuthorNames()
{
    QStringList authorNames;
    for (auto const &author : authors)
        authorNames.append(author.second.getName());
    return authorNames;
}

bool DataBase::addBookToAuthor(const QString &title, const QString &name)
{
    authors[name].addBook(title);
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
    authors.clear();
    QJsonArray authorsArray = JsonObj["authors"].toArray();
    for(int index = 0; index < authorsArray.size(); index++)
    {
        QJsonObject authorObject = authorsArray[index].toObject();
        Author _author;
        _author.read(authorObject);
        authors.insert(std::pair<QString, Author>(_author.getName(), _author));
    }

    books.clear();
    QJsonArray booksArray = JsonObj["books"].toArray();
    for(int index = 0; index < booksArray.size(); index++)
    {
        QJsonObject bookObject = booksArray[index].toObject();
        Book book;
        book.read(bookObject);
        books.insert(std::pair<QString, Book>(book.getFilePath(), book));
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

