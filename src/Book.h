#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QPointer>
/*
 *                                          ---Refactorizare---
 * Pentru optimizare transforma toate valorile in pointeri deoarece mapa din baza de date construieste obiectul
 * cu constructorul definit
*/

class Book
{
public:
    Book();
    Book(const QString& _filePath, const QString& _title = "n/a", const QString& _author = "n/a", const QString &_year = 0, const QString& _description = "n/a");
    Book(const Book& b);
    Book& operator = (const Book& b);
    ~Book();

    QString getTitle() const;
    QString getAuthor() const;
    QString getFilePath() const;
    QString getYear() const;
    QString getDescription() const;
    QString getYearInt() const;

    void setAuthor(const QString& newAuthor);

    bool operator == (const Book& b) const;

    void write(QJsonObject &json) ;
    void read(const QJsonObject &json);

    bool exists() const;
private:
    QString *title;
    QString *author;
    QString *filePath;
    QString *year;
    QString *description;
    bool _exist;
};

#endif //BOOK_H
