#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

#include <vector>

#include "src/Book.h"

class Book;
class QJsonArray;
class QJsonObject;

class Author
{
public:
    Author();
    explicit Author(const QString & name,
                    std::vector<QString> books = std::vector<QString>(),
                    const QString &yearBirth = 0,
                    const QString &yearDeath = 0,
                    const QString & bio = "n/a");
    Author(const Author & a);
    Author& operator = (const Author & a);
    bool operator ==(const Author &a) const;

    ~Author();

    QString getName() const;
    QString getBio() const;
    QString getYearBirth() const;
    QString getYearDeath() const;
    QString getYearBirthInt() const;
    QString getYearDeathInt() const;
    std::vector<QString> getVector() const;

    bool addBook(const QString & book);
    bool exist();

    void write(QJsonObject &json) const;
    void read(const QJsonObject & json);

    //debug

private:
    QString *name;
    std::vector<QString> *books;//Oriunde avem carti, optimizam eficienta pastrand doar titlul si cautand cartea in baza de date
    QString *yearBirth;
    QString *yearDeath;
    QString *bio;
    bool _exist;
};

#endif // AUTHOR_H
