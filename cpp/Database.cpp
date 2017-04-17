#include "database.h"
#include "author.h"
#include "book.h"

#include <QString>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <iostream>

DataBase::DataBase(const QString &filename)
{
    this->filename = new QString(filename);
}

DataBase::~DataBase()
{
    delete filename;
}

QString DataBase::getFileName()
{
    return *filename;
}

bool DataBase::addNewBook(const Book &book)
{

}


