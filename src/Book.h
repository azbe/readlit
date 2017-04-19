#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QString>
#include <QJsonObject>
/*
 *                                          ---Refactorizare---
 * Pentru optimizare transforma toate valorile in pointeri deoarece mapa din baza de date construieste obiectul
 * cu constructorul definit
*/

class Book
{
public:
    Book();
    Book(const QString& _filePath, const QString& _title = "Title", const QString& _author = "Author", const int& _year = 0, const QString& _description = "Description");
    Book(const Book& b);
    Book& operator = (const Book& b);
    ~Book();

    QString getTitle() const;
    QString getAuthor() const;
    QString getFilePath() const;
    int getYear() const;
    QString getDescription() const;

    bool operator == (const Book& b) const;

    void write(QJsonObject &json) ;
    void read(const QJsonObject &json);

    bool exists() const;
private:
    QString *title;
    QString *author;
    QString *filePath;
    int *year;
    QString *description;
    bool _exist;
};

#endif //BOOK_H
