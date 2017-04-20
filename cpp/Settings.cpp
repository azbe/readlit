#include "src/Settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent)
{

    layoutSettings = new QVBoxLayout(this);
    defaultPaths = new QGroupBox(this);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setVerticalStretch(1);
    defaultPaths->setSizePolicy(sizePolicy);
    defaultPaths->setTitle("Default Paths");
    defaultVerticalLayout = new QVBoxLayout(defaultPaths);
    defaultVerticalLayout->setSpacing(0);
    database = new QWidget(defaultPaths);
    databaseHorizontalLayout = new QHBoxLayout(database);
    databaseHorizontalLayout->setSpacing(6);
    databaseHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    databasePathsLabel = new QLabel("Database", database);
    databasePaths = new QLineEdit(database);
    databaseBrowser = new BrowserButton(database);
    databaseHorizontalLayout->addWidget(databasePathsLabel);
    databaseHorizontalLayout->addWidget(databasePaths);
    databaseHorizontalLayout->addWidget(databaseBrowser);
    defaultVerticalLayout->addWidget(database);
    reader = new QWidget(defaultPaths);
    readerPathsLabel = new QLabel("Reader    ", reader);
    readerPaths = new QLineEdit(reader);
    readerBrowser = new BrowserButton(reader);
    readerHorizontalLayout = new QHBoxLayout(reader);
    readerHorizontalLayout->setSpacing(6);
    readerHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    readerHorizontalLayout->addWidget(readerPathsLabel);
    readerHorizontalLayout->addWidget(readerPaths);
    readerHorizontalLayout->addWidget(readerBrowser);
    defaultVerticalLayout->addWidget(reader);
    scanner = new QWidget(defaultPaths);
    scannerPathsLabel = new QLabel("Scanner  ", scanner);
    scannerPaths = new QLineEdit(scanner);
    scannerBrowser = new BrowserButton(scanner);
    scannerHorizontalLayout = new QHBoxLayout(scanner);
    scannerHorizontalLayout->setSpacing(6);
    scannerHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    scannerHorizontalLayout->addWidget(scannerPathsLabel);
    scannerHorizontalLayout->addWidget(scannerPaths);
    scannerHorizontalLayout->addWidget(scannerBrowser);
    defaultVerticalLayout->addWidget(scanner);
    settings = new QWidget(defaultPaths);
    settingsPathsLabel = new QLabel("Settings  ", settings);
    settingsPaths = new QLineEdit(settings);
    settingsBrowser = new BrowserButton(settings);
    settingsHorizontalLayout = new QHBoxLayout(settings);
    settingsHorizontalLayout->setSpacing(6);
    settingsHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    settingsHorizontalLayout->addWidget(settingsPathsLabel);
    settingsHorizontalLayout->addWidget(settingsPaths);
    settingsHorizontalLayout->addWidget(settingsBrowser);
    defaultVerticalLayout->addWidget(settings);
    defaultButtons = new QWidget(defaultPaths);
    defaultButtonHorizontalLayout = new QHBoxLayout(defaultButtons);
    saveButtonDefault = new QPushButton("Save",defaultButtons);
    defaultButtonHorizontalLayout->addWidget(saveButtonDefault);
    defaultsButtonDefault = new QPushButton("Defaults",defaultButtons);
    defaultButtonHorizontalLayout->addWidget(defaultsButtonDefault);
    defaultVerticalLayout->addWidget(defaultButtons);


    pythonScripts = new QGroupBox(this);
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setVerticalStretch(1);
    pythonScripts->setSizePolicy(sizePolicy2);
    pythonScripts->setTitle("Python Scripts");
    pythonVerticalLayout = new QVBoxLayout(pythonScripts);
    pythonVerticalLayout->setSpacing(0);
    translator = new QWidget(pythonScripts);
    translatorHorizontalLayout = new QHBoxLayout(translator);
    translatorHorizontalLayout->setSpacing(6);
    translatorHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    translatorPathsLabel = new QLabel("Translator", translator);
    translatorPaths = new QLineEdit(translator);
    translatorBrowser = new BrowserButton(translator);
    translatorHorizontalLayout->addWidget(translatorPathsLabel);
    translatorHorizontalLayout->addWidget(translatorPaths);
    translatorHorizontalLayout->addWidget(translatorBrowser);
    pythonVerticalLayout->addWidget(translator);
    dictionary = new QWidget(pythonScripts);
    dictionaryPathsLabel = new QLabel("Dictionary    ", dictionary);
    dictionaryPaths = new QLineEdit(dictionary);
    dictionaryBrowser = new BrowserButton(dictionary);
    dictionaryHorizontalLayout = new QHBoxLayout(dictionary);
    dictionaryHorizontalLayout->setSpacing(6);
    dictionaryHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    dictionaryHorizontalLayout->addWidget(dictionaryPathsLabel);
    dictionaryHorizontalLayout->addWidget(dictionaryPaths);
    dictionaryHorizontalLayout->addWidget(dictionaryBrowser);
    pythonVerticalLayout->addWidget(dictionary);
    worldSearch = new QWidget(pythonScripts);
    worldSearchPathsLabel = new QLabel("World Search  ", worldSearch);
    worldSearchPaths = new QLineEdit(worldSearch);
    worldSearchBrowser = new BrowserButton(worldSearch);
    worldSearchHorizontalLayout = new QHBoxLayout(worldSearch);
    worldSearchHorizontalLayout->setSpacing(6);
    worldSearchHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    worldSearchHorizontalLayout->addWidget(worldSearchPathsLabel);
    worldSearchHorizontalLayout->addWidget(worldSearchPaths);
    worldSearchHorizontalLayout->addWidget(worldSearchBrowser);
    pythonVerticalLayout->addWidget(worldSearch);
    bookSync = new QWidget(pythonScripts);
    bookSyncPathsLabel = new QLabel("Book Sync  ", bookSync);
    bookSyncPaths = new QLineEdit(bookSync);
    bookSyncBrowser = new BrowserButton(bookSync);
    bookSyncHorizontalLayout = new QHBoxLayout(bookSync);
    bookSyncHorizontalLayout->setSpacing(6);
    bookSyncHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    bookSyncHorizontalLayout->addWidget(bookSyncPathsLabel);
    bookSyncHorizontalLayout->addWidget(bookSyncPaths);
    bookSyncHorizontalLayout->addWidget(bookSyncBrowser);
    pythonVerticalLayout->addWidget(bookSync);
    authorSync = new QWidget(pythonScripts);
    authorSyncPathsLabel = new QLabel("Author Sync  ", authorSync);
    authorSyncPaths = new QLineEdit(authorSync);
    authorSyncBrowser = new BrowserButton(authorSync);
    authorSyncHorizontalLayout = new QHBoxLayout(authorSync);
    authorSyncHorizontalLayout->setSpacing(6);
    authorSyncHorizontalLayout->setContentsMargins(9, 4, 9, 4);
    authorSyncHorizontalLayout->addWidget(authorSyncPathsLabel);
    authorSyncHorizontalLayout->addWidget(authorSyncPaths);
    authorSyncHorizontalLayout->addWidget(authorSyncBrowser);
    pythonVerticalLayout->addWidget(authorSync);
    pythonButtons = new QWidget(pythonScripts);
    pythonButtonHorizontalLayout = new QHBoxLayout(pythonButtons);
    saveButtonPython = new QPushButton("Save",pythonButtons);
    pythonButtonHorizontalLayout->addWidget(saveButtonPython);
    defaultsButtonPython = new QPushButton("Defaults",pythonButtons);
    pythonButtonHorizontalLayout->addWidget(defaultsButtonPython);
    pythonVerticalLayout->addWidget(pythonButtons);






    layoutSettings->setContentsMargins(0, 0, 0, 0);
    layoutSettings->addWidget(defaultPaths);
    layoutSettings->addWidget(pythonScripts);

}

Settings::~Settings()
{


    delete bookSyncPathsLabel;
    delete bookSyncPaths;
    delete bookSyncBrowser;
    delete bookSyncHorizontalLayout;
    delete bookSync;
    delete authorSyncPathsLabel;
    delete authorSyncPaths;
    delete authorSyncBrowser;
    delete authorSyncHorizontalLayout;
    delete authorSync;
    delete translatorPathsLabel;
    delete translatorPaths;
    delete translatorBrowser;
    delete translatorHorizontalLayout;
    delete translator;
    delete dictionaryPathsLabel;
    delete dictionaryPaths;
    delete dictionaryBrowser;
    delete dictionaryHorizontalLayout;
    delete dictionary;
    delete worldSearchPathsLabel;
    delete worldSearchPaths;
    delete worldSearchBrowser;
    delete worldSearchHorizontalLayout;
    delete worldSearch;
    delete saveButtonPython;
    delete defaultsButtonPython;
    delete pythonButtonHorizontalLayout;
    delete pythonButtons;
    delete pythonVerticalLayout;
    delete pythonScripts;
    delete databasePathsLabel;
    delete databasePaths;
    delete databaseBrowser;
    delete databaseHorizontalLayout;
    delete database;
    delete readerPathsLabel;
    delete readerPaths;
    delete readerBrowser;
    delete readerHorizontalLayout;
    delete reader;
    delete scannerPathsLabel;
    delete scannerPaths;
    delete scannerBrowser;
    delete scannerHorizontalLayout;
    delete scanner;
    delete settingsPathsLabel;
    delete settingsPaths;
    delete settingsBrowser;
    delete settingsHorizontalLayout;
    delete settings;
    delete saveButtonDefault;
    delete defaultsButtonDefault;
    delete defaultButtonHorizontalLayout;
    delete defaultButtons;
    delete defaultVerticalLayout;
    delete defaultPaths;
    delete layoutSettings;


}
