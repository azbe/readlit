#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>

#include "src/Database.h"
#include "src/SubtabBooks.h"
#include "src/SubtabAuthors.h"
#include "src/Reader.h"
#include "src/ReaderExtras.h"
#include "src/Settings.h"

class MainWindow : public QWidget
{
	Q_OBJECT

    public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

    private slots:
    void openBookInReader(const QString& path);

    private:

	QTabWidget *mainTabs;
    QLayout	*mainLayout;
    QWidget *tabReader;
    QHBoxLayout *readerLayout;
    Reader *reader;
    ReaderExtras *readerExtras;
    QWidget *tabLocal;
    QTabWidget *localTabs;
    QLayout *localLayout;
    SubtabBooks *books;
    SubtabAuthors *authors;
    QWidget *tabSettings;
    QGridLayout *settingsLayout;
    Settings *settings;

    DataBase database;
};

#endif //MAINWINDOW_H
