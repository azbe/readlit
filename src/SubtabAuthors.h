#ifndef SUBTABAUTHORS_H
#define SUBTABAUTHORS_H

#include <QWidget>
#include <QLayout>

#include "DataList.h"
#include "Database.h"
#include "src/DataButton.h"
#include "src/DataTable.h"
#include "src/Constants.h"

class SubtabAuthors : public QWidget
{
    Q_OBJECT

public:
    SubtabAuthors(QWidget *parent, DataBase& database);
	~SubtabAuthors();

public slots:
    void newScan();

private:
    DataBase *database;
    DataList *authorList;
	DataList *authorBooks;
	QWidget *authorData;
	QLayout *authorLayout;
    QGridLayout *authorDataLayout;
    DataButton *dataButtons[4];
    DataTable *authorDataTable;
};

#endif //SUBTABAUTHORS_H
