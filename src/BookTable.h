#ifndef BOOKTABLE_H
#define BOOKTABLE_H

#include <QTableWidget>
#include <QProcess>
#include <QHeaderView>

#include "src/Book.h"

class BookTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit BookTable(QWidget *parent = 0);
    ~BookTable();

    Book getBook();

signals:
    void updateBook(const Book& book);

public slots:
    void setBook(const Book& book);
    void saveBook();
    void syncBook();
    void getSyncBook();
    void finishedSyncBook(int exitCode, QProcess::ExitStatus exitStatus);
    void clear();

private:
    Book *book;
    QTableWidgetItem *header;
    QTableWidgetItem *path;
    QTableWidgetItem *title;
    QTableWidgetItem *author;
    QTableWidgetItem *year;
    QTableWidgetItem *summary;

    QProcess *script;
    bool isSyncing;
};

#endif // BOOKTABLE_H
