#include "author.h"
#include "book.h"

#include <QDebug>
#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

#include <iostream>
#include <vector>

/*
* bugs:
* -variabilele initializate nu functioneaza
* -variabilele sunt statice asa ca performanta nu e optima, mai ales cand foloseste constructorul predefinit in maps
*/
Author::Author()
{
    name = "error, no name in autho class";
    yearBirth = 0;
    yearDeath = 0;
    books = std::vector<QString>();
    bio = "";
}



Author::Author(const QString &name,
               std::vector<QString> books = std::vector<QString>(),
               const int &yearBirth = 0,
               const int &yearDeath = 0,
               const QString &bio = "")
{
    this->name = name;
    this->books = books;
    this->yearBirth = yearBirth;
    this->yearDeath = yearDeath;
    this->bio = bio;
}

Author::Author(const Author & a)
{
    name = a.name;
    books = a.books;
    yearBirth = a.yearBirth;
    yearDeath = a.yearDeath;
    bio = a.bio;

}

bool Author::operator ==(const Author &a) const
{
    if(name == a.name)
        return true;
    return false;
}

Author::~Author()
{

}

QString Author::getName()
{
    return name;
}

QString Author::getBio()
{
    return bio;
}

std::vector<QString> Author::getVector()
{
    return books;
}

int Author::getYearBirth()
{
    return yearBirth;
}

int Author::getYearDeath()
{
    return yearBirth;
}

