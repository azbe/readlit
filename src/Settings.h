#ifndef SETTINGS
#define SETTINGS
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QWidget>
#include "src/BrowserButton.h"
#include "src/Constants.h"
class Settings : public QWidget
{
    Q_OBJECT

    public:
    explicit Settings(QWidget *parent = 0, const QString& loadPath = "");
    ~Settings();

    void save(const QString& path);
    void load(const QString& path);

public:
    QString databasePath;
    //...

private:
    QWidget *bonus;
    QWidget *defaultButtons;
    QWidget *pythonButtons;
    QPushButton *saveButtonDefault;
    QPushButton *defaultsButtonDefault;
    QPushButton *saveButtonPython;
    QPushButton *defaultsButtonPython;
    QGroupBox *defaultPaths;
    QGroupBox *pythonScripts;
    QVBoxLayout *layoutSettings;
    QWidget *database;
    QLabel *databasePathsLabel;
    QLineEdit *databasePaths;
    BrowserButton *databaseBrowser;
    QWidget *scanner;
    QLabel *scannerPathsLabel;
    QLineEdit *scannerPaths;
    BrowserButton *scannerBrowser;
    QWidget *bookSync;
    QLabel *bookSyncPathsLabel;
    QLineEdit *bookSyncPaths;
    BrowserButton *bookSyncBrowser;
    QWidget *translator;
    QLabel *translatorPathsLabel;
    QLineEdit *translatorPaths;
    BrowserButton *translatorBrowser;
    QWidget *dictionary;
    QLabel *dictionaryPathsLabel;
    QLineEdit *dictionaryPaths;
    BrowserButton *dictionaryBrowser;
    QWidget *authorSync;
    QLabel *authorSyncPathsLabel;
    QLineEdit *authorSyncPaths;
    BrowserButton *authorSyncBrowser;
    QGridLayout *defaultLayout;
    QGridLayout *pythonLayout;
    QPushButton *databaseDefault;
    QPushButton *scannerDefault;
    QPushButton *bookSyncDefault;
    QPushButton *authorSyncDefault;
    QPushButton *dictionaryDefault;
    QPushButton *translatorDefault;
};
#endif // SETTINGS

