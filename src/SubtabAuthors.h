#ifndef SUBTABAUTHORS_H
#define SUBTABAUTHORS_H

#include <QWidget>
#include <QLayout>

#include "DataList.h"
#include "Database.h"
#include "src/DataButton.h"
#include "src/AuthorTable.h"
#include "src/Constants.h"

class SubtabAuthors : public QWidget
{
    Q_OBJECT

public:
    SubtabAuthors(QWidget *parent, DataBase& database);
	~SubtabAuthors();

signals:
    void updateAuthorDetails(const Author& author);

public slots:
    void saveNewAuthor(const Author& author);
    void newScan();
    void updateAuthorBooks(QListWidgetItem *item);

private:
    DataBase *database;
    DataList *authorList;
	DataList *authorBooks;
	QWidget *authorData;
	QLayout *authorLayout;
    QGridLayout *authorDataLayout;
    DataButton *dataButtons[4];
    AuthorTable *authorDataTable;
};

#endif //SUBTABAUTHORS_H
