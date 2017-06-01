#include "src/Settings.h"
#include "src/Constants.h"

Settings::Settings(QWidget *parent, const QString& loadPath) : QWidget(parent)
{
    rememberPath = loadPath;
    load(rememberPath);
    layoutSettings = new QVBoxLayout(this);
    layoutSettings->setSpacing(6);
    defaultText = new QGroupBox(this);
    defaultText->setTitle("Default Text");
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy.setVerticalStretch(1);
    defaultText->setSizePolicy(sizePolicy);
    defaultLayout = new QGridLayout(defaultText);
    defaultLayout->setSpacing(6);
    databaseTextLabel = new QLabel("Database", defaultText);
    databaseText = new QLineEdit(defaultText);
    databaseText->setReadOnly(true);
    databaseBrowser = new BrowserButton(defaultText,BrowserButton::JSON);
    databaseDefault= new QPushButton("Default",defaultText);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(1);
    sizePolicy1.setVerticalStretch(0);
    databaseText->setSizePolicy(sizePolicy1);
    databaseText->setText(databasePath);
    defaultLayout->addWidget(databaseTextLabel,0, 0, 1, 1);
    defaultLayout->addWidget(databaseText,0, 1, 1, 2);
    defaultLayout->addWidget(databaseBrowser,0, 3, 1, 2);
    defaultLayout->addWidget(databaseDefault, 0, 5, 1, 1);
    scannerTextLabel = new QLabel("Scanner", defaultText);
    scannerText = new QLineEdit(defaultText);
    scannerBrowser = new BrowserButton(defaultText,BrowserButton::DIR);
    scannerDefault= new QPushButton("Default",defaultText);
    scannerText->setSizePolicy(sizePolicy1);
    scannerText->setText(scannerPath);
    scannerText->setReadOnly(true);
    defaultLayout->addWidget(scannerTextLabel,1, 0, 1, 1);
    defaultLayout->addWidget(scannerText,1, 1, 1, 2);
    defaultLayout->addWidget(scannerBrowser,1, 3, 1, 2);
    defaultLayout->addWidget(scannerDefault, 1, 5, 1, 1);
    pythonScripts = new QGroupBox(this);
    pythonScripts->setTitle("Python Text");
    pythonScripts->setSizePolicy(sizePolicy);
    pythonLayout = new QGridLayout(pythonScripts);
    pythonLayout->setSpacing(6);
    dictionaryTextLabel = new QLabel("Dictionary", pythonScripts);
    dictionaryText = new QLineEdit(pythonScripts);
    dictionaryText->setReadOnly(true);
    dictionaryBrowser = new BrowserButton(pythonScripts,BrowserButton::PYTHON);
    dictionaryDefault= new QPushButton("Default",pythonScripts);
    dictionaryText->setSizePolicy(sizePolicy1);
    dictionaryText->setText(dictionaryPath);
    pythonLayout->addWidget(dictionaryTextLabel,4, 0, 1, 1);
    pythonLayout->addWidget(dictionaryText,4, 1, 1, 2);
    pythonLayout->addWidget(dictionaryBrowser,4, 3, 1, 2);
    pythonLayout->addWidget(dictionaryDefault, 4, 5, 1, 1);
    python2TextLabel = new QLabel("Python2", pythonScripts);
    python2Text = new QLineEdit(pythonScripts);
    python2Text->setReadOnly(true);
    python2Browser = new BrowserButton(pythonScripts,BrowserButton::ANY);
    python2Default= new QPushButton("Default",pythonScripts);
    python2Text->setSizePolicy(sizePolicy1);
    python2Text->setText(python2Path);
    pythonLayout->addWidget(python2TextLabel,3, 0, 1, 1);
    pythonLayout->addWidget(python2Text,3, 1, 1, 2);
    pythonLayout->addWidget(python2Browser,3, 3, 1, 2);
    pythonLayout->addWidget(python2Default, 3, 5, 1, 1);
    /*translatorTextLabel = new QLabel("Translator", pythonScripts);
    translatorText = new QLineEdit(pythonScripts);
    translatorText->setReadOnly(true);
    translatorBrowser = new BrowserButton(pythonScripts,BrowserButton::PYTHON);
    translatorDefault= new QPushButton("Default",pythonScripts);
    translatorText->setSizePolicy(sizePolicy1);
    translatorText->setText(translatorPath);
    pythonLayout->addWidget(translatorTextLabel,5, 0, 1, 1);
    pythonLayout->addWidget(translatorText,5, 1, 1, 2);
    pythonLayout->addWidget(translatorBrowser,5, 3, 1, 2);
    pythonLayout->addWidget(translatorDefault, 5, 5, 1, 1);*/
    saveButton = new QPushButton("Save",pythonScripts);
    bookSyncTextLabel = new QLabel("Books Sync", pythonScripts);
    bookSyncText = new QLineEdit(pythonScripts);
    bookSyncText->setReadOnly(true);
    bookSyncBrowser = new BrowserButton(pythonScripts,BrowserButton::PYTHON);
    bookSyncDefault= new QPushButton("Default",pythonScripts);
    bookSyncText->setSizePolicy(sizePolicy1);
    bookSyncText->setText(bookSyncPath);
    pythonLayout->addWidget(bookSyncTextLabel,6, 0, 1, 1);
    pythonLayout->addWidget(bookSyncText,6, 1, 1, 2);
    pythonLayout->addWidget(bookSyncBrowser,6, 3, 1, 2);
    pythonLayout->addWidget(bookSyncDefault, 6, 5, 1, 1);
    authorSyncTextLabel = new QLabel("Authors Sync", pythonScripts);
    authorSyncText = new QLineEdit(pythonScripts);
    authorSyncText->setReadOnly(true);
    authorSyncBrowser = new BrowserButton(pythonScripts,BrowserButton::PYTHON);
    authorSyncDefault= new QPushButton("Default",pythonScripts);
    authorSyncText->setSizePolicy(sizePolicy1);
    authorSyncText->setText(authorSyncPath);
    pythonLayout->addWidget(authorSyncTextLabel,7, 0, 1, 1);
    pythonLayout->addWidget(authorSyncText,7, 1, 1, 2);
    pythonLayout->addWidget(authorSyncBrowser,7, 3, 1, 2);
    pythonLayout->addWidget(authorSyncDefault, 7, 5, 1, 1);
    pythonLayout->addWidget(saveButton,8, 5, 1, 1);
    layoutSettings->addWidget(defaultText);
    layoutSettings->addWidget(pythonScripts);
    bonus = new QWidget(this);
    QSizePolicy sizeDefault(QSizePolicy::Expanding,QSizePolicy::Expanding);
    sizeDefault.setVerticalStretch(1);
    bonus->setSizePolicy(sizeDefault);
    layoutSettings->addWidget(bonus);
    connect(databaseDefault, SIGNAL(clicked(bool)), this, SLOT(updateDatabasePath()));
    connect(scannerDefault, SIGNAL(clicked(bool)), this, SLOT(updateScannerPath()));
    connect(dictionaryDefault, SIGNAL(clicked(bool)), this, SLOT(updateDictionaryPath()));
    //connect(translatorDefault, SIGNAL(clicked(bool)), this, SLOT(updateTranslatorPath()));
    connect(python2Default, SIGNAL(clicked(bool)), this, SLOT(updatePython2Path()));
    connect(bookSyncDefault, SIGNAL(clicked(bool)), this, SLOT(updateBookSyncPath()));
    connect(authorSyncDefault, SIGNAL(clicked(bool)), this, SLOT(updateAuthorSyncPath()));
    connect(databaseBrowser,SIGNAL(sendPaths(QStringList)),this,SLOT(browserDatabase(QStringList)));
    connect(scannerBrowser,SIGNAL(sendPaths(QStringList)),this,SLOT(browserScanner(QStringList)));
    connect(python2Browser,SIGNAL(sendPaths(QStringList)),this,SLOT(browserPython2(QStringList)));
    connect(authorSyncBrowser,SIGNAL(sendPaths(QStringList)),this,SLOT(browserAuthorSync(QStringList)));
    connect(dictionaryBrowser,SIGNAL(sendPaths(QStringList)),this,SLOT(browserDictionary(QStringList)));
    //connect(translatorBrowser,SIGNAL(sendPaths(QStringList)),this,SLOT(browserTranslator(QStringList)));
    connect(bookSyncBrowser,SIGNAL(sendPaths(QStringList)),this,SLOT(browserBookSync(QStringList)));
    connect(saveButton, SIGNAL(clicked(bool)),this,SLOT(saveFile()));
}

void Settings::saveFile()
{
    save(rememberPath);
}


void Settings::updateDatabasePath()
{

        databaseText->setText(SettingsConstants::DATABASE_DEFAULT_PATH);
}

void Settings::updateScannerPath()
{

        scannerText->setText(SettingsConstants::SCANNER_DEFAULT_PATH);
}

void Settings::updateTranslatorPath()
{

        translatorText->setText(SettingsConstants::TRANSLATOR_DEFAULT_PATH);
}

void Settings::updateDictionaryPath()
{

        dictionaryText->setText(SettingsConstants::DICTIONARY_DEFAULT_PATH);
}

void Settings::updatePython2Path()
{

        python2Text->setText(SettingsConstants::PYTHON2_DEFAULT_PATH);
}



void Settings::updateAuthorSyncPath()
{

        authorSyncText->setText(SettingsConstants::AUTHOR_SYNC_DEFAULT_PATH);
}

void Settings::updateBookSyncPath()
{

        bookSyncText->setText(SettingsConstants::BOOK_SYNC_DEFAULT_PATH);
}

void Settings::browserDatabase(const QStringList &folderPaths)
{
    if(!folderPaths.isEmpty()&&!folderPaths.value(0).isEmpty())
        databaseText->setText(folderPaths.value(0));
}

void Settings::browserScanner(const QStringList &folderPaths)
{
    if(!folderPaths.isEmpty()&&!folderPaths.value(0).isEmpty())
        scannerText->setText(folderPaths.value(0));
}

void Settings::browserPython2(const QStringList &folderPaths)
{
    if(!folderPaths.isEmpty()&&!folderPaths.value(0).isEmpty())
        python2Text->setText(folderPaths.value(0));
}

void Settings::browserDictionary(const QStringList &folderPaths)
{
    if(!folderPaths.isEmpty()&&!folderPaths.value(0).isEmpty())
        dictionaryText->setText(folderPaths.value(0));
}

void Settings::browserTranslator(const QStringList &folderPaths)
{
    if(!folderPaths.isEmpty()&&!folderPaths.value(0).isEmpty())
        translatorText->setText(folderPaths.value(0));
}

void Settings::browserBookSync(const QStringList &folderPaths)
{
    if(!folderPaths.isEmpty()&&!folderPaths.value(0).isEmpty())
       bookSyncText->setText(folderPaths.value(0));
}

void Settings::browserAuthorSync(const QStringList &folderPaths)
{
    if(!folderPaths.isEmpty()&&!folderPaths.value(0).isEmpty())
        authorSyncText->setText(folderPaths.value(0));
}

void Settings::save(const QString &fileName)
{
    QFile saveFile(fileName);

    if(!saveFile.exists()|| !saveFile.open(QIODevice::WriteOnly))
    {
         qDebug()<<"Settings::save - Error: Folder does not exist";
        return;
    }

    QTextStream textFisier(&saveFile);
    textFisier<<"Database Path="<<databaseText->text()<<'\n';
    textFisier<<"Scanner Path="<<scannerText->text()<<'\n';
    textFisier<<"Dictionary Path="<<dictionaryText->text()<<'\n';
    //textFisier<<("Translator Path="+translatorText->text()+'\n');
    textFisier<<"Author Sync Path="<<authorSyncText->text()<<'\n';
    textFisier<<"Book Sync Path="<<bookSyncText->text()<<'\n';
    textFisier<<"Python2 Path="<<python2Text->text()<<'\n';
    saveFile.close();
}

void Settings::load(const QString &fileName)
{
    QFile savedFile(fileName);

    if(!savedFile.exists() || !savedFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Settings::load - Error: Folder does not exist";
        return;
    }
    QStringList str,str1;
    QString line;
            while (!savedFile.atEnd()) {
           line = savedFile.readLine();
            str = line.split('=');
            if(QString::compare(str[0],"Database Path")==0)
            {
                str1 = str[1].split('\n');
                databasePath=str1[0];
            }

            if(QString::compare(str[0],"Scanner Path")==0)
            {
                str1 = str[1].split('\n');
                scannerPath=str1[0];
            }
            if(QString::compare(str[0],"Dictionary Path")==0)
            {
                str1 = str[1].split('\n');
                dictionaryPath=str1[0];
            }
            /*if(QString::compare(str[0],"Translator Path")==0)
            translatorPath=str[1];*/
            if(QString::compare(str[0],"Book Sync Path")==0)
            {
                str1 = str[1].split('\n');
                bookSyncPath=str1[0];
            }
            if(QString::compare(str[0],"Author Sync Path")==0)
            {
                str1 = str[1].split('\n');
                authorSyncPath=str1[0];
            }
            if(QString::compare(str[0],"Python2 Path")==0)
            {
                str1 = str[1].split('\n');
                python2Path=str1[0];
            }
      }
            savedFile.close();

}

Settings::~Settings()
{

    delete bookSyncTextLabel;
    delete bookSyncText;
    delete bookSyncBrowser;
    delete bookSyncDefault;
    delete authorSyncTextLabel;
    delete authorSyncText;
    delete authorSyncBrowser;
    delete authorSyncDefault;
    delete translatorTextLabel;
    delete translatorText;
    delete translatorBrowser;
    delete translatorDefault;
    delete dictionaryTextLabel;
    delete dictionaryText;
    delete dictionaryBrowser;
    delete dictionaryDefault;
    delete saveButton;
    delete pythonLayout;
    delete pythonScripts;
    delete databaseTextLabel;
    delete databaseText;
    delete databaseBrowser;
    delete databaseDefault;
    delete scannerTextLabel;
    delete scannerText;
    delete scannerBrowser;
    delete scannerDefault;
    delete defaultLayout;
    delete defaultText;
    delete layoutSettings;
}

QString Settings::databasePath = SettingsConstants::DATABASE_DEFAULT_PATH;
QString Settings::scannerPath = SettingsConstants::SCANNER_DEFAULT_PATH;
QString Settings::dictionaryPath = SettingsConstants::DICTIONARY_DEFAULT_PATH;
QString Settings::authorSyncPath = SettingsConstants::AUTHOR_SYNC_DEFAULT_PATH;
QString Settings::bookSyncPath = SettingsConstants::BOOK_SYNC_DEFAULT_PATH;
QString Settings::translatorPath = SettingsConstants::TRANSLATOR_DEFAULT_PATH;
QString Settings::python2Path=SettingsConstants::PYTHON2_DEFAULT_PATH;

QString Settings::getDatabasePath()
{
    return databasePath;
}

QString Settings::getScannerPath()
{
    return scannerPath;
}

QString Settings::getTranslatorPath()
{
    return translatorPath;
}

QString Settings::getDictionaryPath()
{
    return dictionaryPath;
}

QString Settings::getAuthorSyncPath()
{
    return authorSyncPath;
}

QString Settings::getBookSyncPath()
{
    return bookSyncPath;
}

QString Settings::getPythonPath()
{
    return python2Path;
}
