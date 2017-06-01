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
#include <QTextStream>
#include <QMouseEvent>
#include <QMessageBox>
#include <qdebug.h>
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

    static QString getDatabasePath();
    static QString getScannerPath();
    static QString getTranslatorPath();
    static QString getDictionaryPath();
    static QString getAuthorSyncPath();
    static QString getBookSyncPath();
    static QString getPythonPath();

    private slots:
    void updateDatabasePath();
    void updateScannerPath();
    void updateDictionaryPath();
    void updateTranslatorPath();
    void updatePython2Path();
    void updateAuthorSyncPath();
    void updateBookSyncPath();
    void browserDatabase(const QStringList &folderPaths);
    void browserScanner(const QStringList &folderPaths);
    void browserPython2(const QStringList &folderPaths);
    void browserDictionary(const QStringList &folderPaths);
    void browserTranslator(const QStringList &folderPaths);
    void browserBookSync(const QStringList &folderPaths);
    void browserAuthorSync(const QStringList &folderPaths);
    void saveFile();

private:
    QWidget *bonus;
    QString rememberPath;
    QPushButton *saveButton;
    QGroupBox *defaultText;
    QGroupBox *pythonScripts;
    QVBoxLayout *layoutSettings;
    QLabel *databaseTextLabel;
    QLineEdit *databaseText;
    BrowserButton *databaseBrowser;
    QLabel *scannerTextLabel;
    QLineEdit *scannerText;
    BrowserButton *scannerBrowser;
    QLabel *bookSyncTextLabel;
    QLineEdit *bookSyncText;
    BrowserButton *bookSyncBrowser;
    QLabel *translatorTextLabel;
    QLineEdit *translatorText;
    BrowserButton *translatorBrowser;
    QLabel *dictionaryTextLabel;
    QLineEdit *dictionaryText;
    BrowserButton *dictionaryBrowser;
    QLabel *authorSyncTextLabel;
    QLineEdit *authorSyncText;
    BrowserButton *authorSyncBrowser;
    QLabel *python2TextLabel;
    QLineEdit *python2Text;
    BrowserButton *python2Browser;
    QGridLayout *python2Layout;
    QPushButton *python2Default;
    QGridLayout *defaultLayout;
    QGridLayout *pythonLayout;
    QPushButton *databaseDefault;
    QPushButton *scannerDefault;
    QPushButton *bookSyncDefault;
    QPushButton *authorSyncDefault;
    QPushButton *dictionaryDefault;
    QPushButton *translatorDefault;

    static QString databasePath;
    static QString scannerPath;
    static QString translatorPath;
    static QString dictionaryPath;
    static QString authorSyncPath;
    static QString bookSyncPath;
    static QString python2Path;
};
#endif // SETTINGS

