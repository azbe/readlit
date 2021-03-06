#ifndef SUBTABBOOKS_H
#define SUBTABBOOKS_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QProcess>

#include "src/Database.h"
#include "src/BrowserButton.h"
#include "src/ScannerButton.h"
#include "src/DataList.h"
#include "src/BookTable.h"
#include "src/DataButton.h"
#include "src/Constants.h"
#include "src/SyncWorker.h"
#include <qdebug.h>

class SubtabBooks : public QWidget
{
    Q_OBJECT

public:
    SubtabBooks(QWidget *parent, DataBase &database);
	~SubtabBooks();

    void updateBookList();

    signals:
    void openInReader(const QString& filePath);
    void updateAuthors();
    void updateBookDetails(const Book& book);

    private slots:
    void toOpenInReader();
    void saveNewBook(const Book& book);
    void getBookDetails(QListWidgetItem *item);
    void getSyncDetails();
    void getSyncDetailsDone(const QStringList& details, const QString& path, int row);
    void getSyncDetailsError(const QString& error, SyncWorker *worker);
    void getBrowsePaths(QStringList browsePaths);
    void getBookPaths(QStringList bookPaths);
    void clearBookPaths();
    void deleteBook();

private:
    DataBase *database;
	QWidget *scanner;
	QWidget *books;
	QLayout *bookLayout;
    QLayout *bookWidgetsLayout0;
    QLabel *folderPathsLabel;
    QLineEdit *folderPaths;
    QPushButton *clearButton;
    BrowserButton *browserButton;
    ScannerButton *scannerButton;
    QLayout *bookWidgetsLayout1;
    DataList *bookList;
    QWidget *dataWidget;
    QGridLayout *dataWidgetLayout;
    DataButton *dataButtons[4];
    BookTable *bookData;
};

#endif //SUBTABBOOKS_H
