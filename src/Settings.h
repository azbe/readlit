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
#include <QVBoxLayout>
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
    QWidget *defaultButtons;
    QWidget *pythonButtons;
    QPushButton *saveButtonDefault;
    QPushButton *defaultsButtonDefault;
    QPushButton *saveButtonPython;
    QPushButton *defaultsButtonPython;
    QHBoxLayout *pythonButtonHorizontalLayout;
    QHBoxLayout *defaultButtonHorizontalLayout;
    QGroupBox *defaultPaths;
    QGroupBox *pythonScripts;
    QLayout *layoutSettings;
    QWidget *database;
    QLabel *databasePathsLabel;
    QLineEdit *databasePaths;
    BrowserButton *databaseBrowser;
    QHBoxLayout *databaseHorizontalLayout;
    QWidget *reader;
    QLabel *readerPathsLabel;
    QLineEdit *readerPaths;
    BrowserButton *readerBrowser;
    QHBoxLayout *readerHorizontalLayout;
    QWidget *scanner;
    QLabel *scannerPathsLabel;
    QLineEdit *scannerPaths;
    BrowserButton *scannerBrowser;
    QHBoxLayout *scannerHorizontalLayout;
    QWidget *settings;
    QLabel *settingsPathsLabel;
    QLineEdit *settingsPaths;
    BrowserButton *settingsBrowser;
    QHBoxLayout *settingsHorizontalLayout;
    QWidget *bookSync;
    QLabel *bookSyncPathsLabel;
    QLineEdit *bookSyncPaths;
    BrowserButton *bookSyncBrowser;
    QHBoxLayout *bookSyncHorizontalLayout;
    QWidget *translator;
    QLabel *translatorPathsLabel;
    QLineEdit *translatorPaths;
    BrowserButton *translatorBrowser;
    QHBoxLayout *translatorHorizontalLayout;
    QWidget *dictionary;
    QLabel *dictionaryPathsLabel;
    QLineEdit *dictionaryPaths;
    BrowserButton *dictionaryBrowser;
    QHBoxLayout *dictionaryHorizontalLayout;
    QWidget *worldSearch;
    QLabel *worldSearchPathsLabel;
    QLineEdit *worldSearchPaths;
    BrowserButton *worldSearchBrowser;
    QHBoxLayout *worldSearchHorizontalLayout;
    QWidget *authorSync;
    QLabel *authorSyncPathsLabel;
    QLineEdit *authorSyncPaths;
    BrowserButton *authorSyncBrowser;
    QHBoxLayout *authorSyncHorizontalLayout;
    QVBoxLayout *defaultVerticalLayout;
    QVBoxLayout *pythonVerticalLayout;
};
#endif // SETTINGS

