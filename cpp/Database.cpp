#include "src/Database.h"

DataBase::DataBase()
{

}

bool DataBase::addBook(const Book& NewBook)
{
    if(books.count(NewBook.getFilePath()) != 0)
    {
        error("The book: " + NewBook.getFilePath() + "is not in data base: deleteBook(const QString &)");
        return false;
    }
    books.insert(std::pair<QString, Book>(NewBook.getFilePath(), NewBook));
    if (!findAuthor(NewBook.getAuthor()))
        addAuthor(Author(NewBook.getAuthor()));
    addBookToAuthor(NewBook.getTitle(), NewBook.getAuthor());
    return true;
}

bool DataBase::deleteBook(const QString &pathID)
{
    if(books.count(pathID) == 0)
    {
        return false;
        error("The book: " + pathID + "is not in data base: deleteBook(const QString &)");
    }
    books.erase(pathID);
    return true;
}

bool DataBase::addAuthor(Author _author)
{
    if(authors.count(_author.getName()) != 0)
    {
        error("The author " + _author.getName() + "is already in database !addAuthor(Author)");
        return false;
    }
    authors.insert(std::pair<QString, Author>(_author.getName(), _author));
    return true;
}

bool DataBase::deleteAuthor(const QString &name)
{
    if(authors.count(name) == 0)
    {
        error("The author " + name + " is not data base: getBook()");
        return false;
    }
    authors.erase(name);
    return true;
}

bool DataBase::findBook(const QString &PathID)
{
    if (books.count(PathID) == 0)
    {
        return false;
        error("The book: " + PathID + "is not in data base: findBook(const QString &)");
    }
    return true;
}

Book DataBase::getBook(const QString &PathID)
{
    if(books.count(PathID) == 0)
    {
        error("The book: " + PathID + "is not in data base: getBook(const QString &)");
        return Book();
    }
    return books[PathID];
}

Book DataBase::getBookByTitle(const QString &title)
{
    for (auto const &book : books)
        if (book.second.getTitle() == title)
            return book.second;
    return Book();
    error("The book: " + title + "is not in data base: getBookByTitle(const QString &)");
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
    if(authors.count(name) == 0)
    {
        //error("The author: " + name + " is not in database: findAuthor(const QString&)");
        return false;
    }
    return true;
}

Author DataBase::getAuthor(const QString &name)
{
    if(authors.count(name) == 0)
    {
        error("The author: " + name + " isn't in database: getAuthor()");
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
    return authors[name].addBook(title);
}

bool DataBase::removeBookFromAuthor(const QString &title, const QString &name)
{
    bool check = false;
    std::vector<QString> authorBooks = authors[name].getVector();
    for (unsigned index = 0; index < authorBooks.size(); index++)
    {
        if (authorBooks[index] == title)
        {
            check = true;
            authorBooks.erase(authorBooks.begin() + index);
            break;
        }
    }
    Author newAuthor(authors[name].getName(), authorBooks, authors[name].getYearBirth(), authors[name].getYearDeath(), authors[name].getBio());
    deleteAuthor(name);
    if (authorBooks.size() > 0) addAuthor(newAuthor);
    return check;
}

bool DataBase::editBook(const Book &newBook)
{
    bool check = false;
    QString oldTitle = books[newBook.getFilePath()].getTitle();
    QString oldAuthor = books[newBook.getFilePath()].getAuthor();
    removeBookFromAuthor(oldTitle, oldAuthor);
    if (!findAuthor(newBook.getAuthor()))
    {
        addAuthor(Author(newBook.getAuthor()));
        check = true;
    }
    check = deleteBook(newBook.getFilePath());
    check = addBook(newBook);
    return check;
}

bool DataBase::editAuthor(const Author &newAuthor)
{
    bool check = false;
    check = deleteAuthor(newAuthor.getName());
    check = addAuthor(newAuthor);
    return check;
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

    if(!saveFile.open(QIODevice::WriteOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"ERROR","Couldn't open database file for saving. Check if the file is still there and if it's writable.\nChanges to the database have NOT been saved.\nGiven path: " + fileName);
        messageBox.setFixedSize(500,200);
        error("Couldn't save file because is not writeable!");
        return;
    }

    QJsonObject booksObject;
    write(booksObject);
    QJsonDocument saveDoc(booksObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
}

void DataBase::load(const QString &fileName)
{
    QFile savedFile(fileName);

    if(!savedFile.exists() || !savedFile.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"ERROR","Couldn't open database file for loading. Check if the file exists and if it's readable.\nGiven path: " + fileName);
        error("Couldn't open load file because it is not readable!");
        return;
    }

    QByteArray savedData = savedFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));
    read(loadDoc.object());
    savedFile.close();
}

void DataBase::error(const QString error)
{
    qDebug() << error + "\nClass name: Database";
}

