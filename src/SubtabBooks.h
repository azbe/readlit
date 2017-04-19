#ifndef SUBTABBOOKS_H
#define SUBTABBOOKS_H

#include <QWidget>
#include <QLayout>
#include <QLabel>

#include "src/Database.h"
#include "src/BrowserButton.h"
#include "src/ScannerButton.h"
#include "src/DataList.h"
#include "src/DataTable.h"
#include "src/DataButton.h"
#include "src/Constants.h"


class SubtabBooks : public QWidget
{
    Q_OBJECT

public:
    SubtabBooks(QWidget *parent, DataBase &database);
	~SubtabBooks();

    void updateBookList();

    signals:
    void updateAuthors();

    private slots:
    void getBookpaths(QStringList bookPaths);

private:
    DataBase *database;
	QWidget *scanner;
	QWidget *books;
	QLayout *bookLayout;
    QLayout *bookWidgetsLayout0;
    QLabel *folderPathsLabel;
    QLineEdit *folderPaths;
    BrowserButton *browserButton;
    ScannerButton *scannerButton;
    QLayout *bookWidgetsLayout1;
    DataList *bookList;
    QWidget *dataWidget;
    QGridLayout *dataWidgetLayout;
    DataButton *dataButtons[4];
    DataTable *bookData;
};

#endif //SUBTABBOOKS_H
