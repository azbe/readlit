#include <QHeaderView>

#include "src/AuthorTable.h"

AuthorTable::AuthorTable(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(1);
    setRowCount(4);

    header = new QTableWidgetItem();
    setHorizontalHeaderItem(0, header);

    name = new QTableWidgetItem("Name");
    setVerticalHeaderItem(0, name);
    setItem(0, 0, new QTableWidgetItem());
    item(0,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item(0,0)->setFlags(item(0,0)->flags() ^ Qt::ItemIsEditable);

    yearBirth = new QTableWidgetItem("Birth Year");
    setVerticalHeaderItem(1, yearBirth);
    setItem(1, 0, new QTableWidgetItem());
    item(1,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    yearDeath = new QTableWidgetItem("Death Year");
    setVerticalHeaderItem(2, yearDeath);
    setItem(2, 0, new QTableWidgetItem());
    item(2,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    bio = new QTableWidgetItem("Bio");
    setVerticalHeaderItem(3, bio);
    setItem(3, 0, new QTableWidgetItem());
    item(3,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    setGridStyle(Qt::SolidLine);
    horizontalHeader()->setVisible(false);
    horizontalHeader()->setCascadingSectionResizes(true);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setCascadingSectionResizes(true);
    verticalHeader()->setDefaultSectionSize(30);
    verticalHeader()->setStretchLastSection(true);
}

void AuthorTable::setAuthor(const Author &author)
{
    item(0,0)->setText(author.getName());
    item(1,0)->setText(QString::number(author.getYearBirth()));
    item(2,0)->setText(QString::number(author.getYearDeath()));
    item(3,0)->setText(author.getBio());
}

AuthorTable::~AuthorTable()
{
    delete bio;
    delete yearDeath;
    delete yearBirth;
    delete name;
    delete header;
}
