#include "src/Settings.h"
#include "src/Constants.h"

Settings::Settings(QWidget *parent, const QString& loadPath) : QWidget(parent)
{
    databasePath = SettingsConstants::DATABASE_DEFAULT_PATH;
    //..
    //load(loadPath);

    layoutSettings = new QVBoxLayout(this);
    layoutSettings->setSpacing(6);
    defaultPaths = new QGroupBox(this);
    defaultPaths->setTitle("Default Paths");
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy.setVerticalStretch(1);
    defaultPaths->setSizePolicy(sizePolicy);
    defaultLayout = new QGridLayout(defaultPaths);
    defaultLayout->setSpacing(6);
    databasePathsLabel = new QLabel("Database", defaultPaths);
    databasePaths = new QLineEdit(defaultPaths);
    databaseBrowser = new BrowserButton(defaultPaths);
    databaseDefault= new QPushButton("Default",defaultPaths);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(1);
    sizePolicy1.setVerticalStretch(0);
    databasePaths->setSizePolicy(sizePolicy1);
    defaultLayout->addWidget(databasePathsLabel,0, 0, 1, 1);
    defaultLayout->addWidget(databasePaths,0, 1, 1, 2);
    defaultLayout->addWidget(databaseBrowser,0, 3, 1, 2);
    defaultLayout->addWidget(databaseDefault, 0, 5, 1, 1);
    scannerPathsLabel = new QLabel("Scanner", defaultPaths);
    scannerPaths = new QLineEdit(defaultPaths);
    scannerBrowser = new BrowserButton(defaultPaths);
    scannerDefault= new QPushButton("Default",defaultPaths);
    scannerPaths->setSizePolicy(sizePolicy1);
    defaultLayout->addWidget(scannerPathsLabel,1, 0, 1, 1);
    defaultLayout->addWidget(scannerPaths,1, 1, 1, 2);
    defaultLayout->addWidget(scannerBrowser,1, 3, 1, 2);
    defaultLayout->addWidget(scannerDefault, 1, 5, 1, 1);
    saveButtonDefault = new QPushButton("Save",defaultPaths);
    defaultLayout->addWidget(saveButtonDefault,2, 0, 1, 1);
    pythonScripts = new QGroupBox(this);
    pythonScripts->setTitle("Python Paths");
    pythonScripts->setSizePolicy(sizePolicy);
    pythonLayout = new QGridLayout(pythonScripts);
    pythonLayout->setSpacing(6);
    dictionaryPathsLabel = new QLabel("Dictionary", pythonScripts);
    dictionaryPaths = new QLineEdit(pythonScripts);
    dictionaryBrowser = new BrowserButton(pythonScripts);
    dictionaryDefault= new QPushButton("Default",pythonScripts);
    dictionaryPaths->setSizePolicy(sizePolicy1);
    pythonLayout->addWidget(dictionaryPathsLabel,3, 0, 1, 1);
    pythonLayout->addWidget(dictionaryPaths,3, 1, 1, 2);
    pythonLayout->addWidget(dictionaryBrowser,3, 3, 1, 2);
    pythonLayout->addWidget(dictionaryDefault, 3, 5, 1, 1);
    translatorPathsLabel = new QLabel("Translator", pythonScripts);
    translatorPaths = new QLineEdit(pythonScripts);
    translatorBrowser = new BrowserButton(pythonScripts);
    translatorDefault= new QPushButton("Default",pythonScripts);
    translatorPaths->setSizePolicy(sizePolicy1);
    pythonLayout->addWidget(translatorPathsLabel,4, 0, 1, 1);
    pythonLayout->addWidget(translatorPaths,4, 1, 1, 2);
    pythonLayout->addWidget(translatorBrowser,4, 3, 1, 2);
    pythonLayout->addWidget(translatorDefault, 4, 5, 1, 1);
    saveButtonPython = new QPushButton("Save",pythonButtons);
    bookSyncPathsLabel = new QLabel("Books Sync", pythonScripts);
    bookSyncPaths = new QLineEdit(pythonScripts);
    bookSyncBrowser = new BrowserButton(pythonScripts);
    bookSyncDefault= new QPushButton("Default",pythonScripts);
    bookSyncPaths->setSizePolicy(sizePolicy1);
    pythonLayout->addWidget(bookSyncPathsLabel,5, 0, 1, 1);
    pythonLayout->addWidget(bookSyncPaths,5, 1, 1, 2);
    pythonLayout->addWidget(bookSyncBrowser,5, 3, 1, 2);
    pythonLayout->addWidget(bookSyncDefault, 5, 5, 1, 1);
    authorSyncPathsLabel = new QLabel("Authors Sync", pythonScripts);
    authorSyncPaths = new QLineEdit(pythonScripts);
    authorSyncBrowser = new BrowserButton(pythonScripts);
    authorSyncDefault= new QPushButton("Default",pythonScripts);
    authorSyncPaths->setSizePolicy(sizePolicy1);
    pythonLayout->addWidget(authorSyncPathsLabel,6, 0, 1, 1);
    pythonLayout->addWidget(authorSyncPaths,6, 1, 1, 2);
    pythonLayout->addWidget(authorSyncBrowser,6, 3, 1, 2);
    pythonLayout->addWidget(authorSyncDefault, 6, 5, 1, 1);
    pythonLayout->addWidget(saveButtonPython,7, 0, 1, 1);
    layoutSettings->addWidget(defaultPaths);
    layoutSettings->addWidget(pythonScripts);
    bonus = new QWidget(this);
    QSizePolicy sizeDefault(QSizePolicy::Expanding,QSizePolicy::Maximum);
    bonus->setSizePolicy(sizeDefault);
    layoutSettings->addWidget(bonus);



}

Settings::~Settings()
{


    delete bookSyncPathsLabel;
    delete bookSyncPaths;
    delete bookSyncBrowser;
    delete bookSync;
    delete authorSyncPathsLabel;
    delete authorSyncPaths;
    delete authorSyncBrowser;
    delete authorSync;
    delete translatorPathsLabel;
    delete translatorPaths;
    delete translatorBrowser;
    delete translator;
    delete dictionaryPathsLabel;
    delete dictionaryPaths;
    delete dictionaryBrowser;
    delete dictionary;
    delete saveButtonPython;
    delete defaultsButtonPython;
    delete pythonButtons;
    delete pythonLayout;
    delete pythonScripts;
    delete databasePathsLabel;
    delete databasePaths;
    delete databaseBrowser;;
    delete database;
    delete scannerPathsLabel;
    delete scannerPaths;
    delete scannerBrowser;
    delete scanner;
    delete saveButtonDefault;
    delete defaultsButtonDefault;
    delete defaultButtons;
    delete defaultLayout;
    delete defaultPaths;
    delete layoutSettings;


}
