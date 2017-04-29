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
#include <QFile>
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
    QString databasePath = "mare";
    QString scannerPath = "mare";
    QString translatorPath;
    QString dictionaryPath;
    QString authorSyncPath;
    QString bookSyncPath;

private:
    QWidget *bonus;
    QWidget *defaultButtons;
    QWidget *pythonButtons;
    QPushButton *saveButtonDefault;
    QPushButton *defaultsButtonDefault;
    QPushButton *saveButtonPython;
    QPushButton *defaultsButtonPython;
    QGroupBox *defaultText;
    QGroupBox *pythonScripts;
    QVBoxLayout *layoutSettings;
    QWidget *database;
    QLabel *databaseTextLabel;
    QLineEdit *databaseText;
    BrowserButton *databaseBrowser;
    QWidget *scanner;
    QLabel *scannerTextLabel;
    QLineEdit *scannerText;
    BrowserButton *scannerBrowser;
    QWidget *bookSync;
    QLabel *bookSyncTextLabel;
    QLineEdit *bookSyncText;
    BrowserButton *bookSyncBrowser;
    QWidget *translator;
    QLabel *translatorTextLabel;
    QLineEdit *translatorText;
    BrowserButton *translatorBrowser;
    QWidget *dictionary;
    QLabel *dictionaryTextLabel;
    QLineEdit *dictionaryText;
    BrowserButton *dictionaryBrowser;
    QWidget *authorSync;
    QLabel *authorSyncTextLabel;
    QLineEdit *authorSyncText;
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

