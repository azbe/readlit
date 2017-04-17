#ifndef BOOK_H
#define BOOK_H

#include <QObject>

/*
 *                                          ---Refactorizare---
 * Pentru optimizare transforma toate valorile in pointeri deoarece mapa din baza de date construieste obiectul
 * cu constructorul definit
*/
class QString;

class Book
{
public:
    Book();
    Book(const QString& _filePath, const QString& _title, const QString& _author, const int& _year, const QString& _description);
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
private:
    QString title;
    QString author;
    QString filePath;
    int year;
    QString description;
};

#endif //BOOK_H
