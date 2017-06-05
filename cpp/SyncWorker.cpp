#include "src/SyncWorker.h"
#include <QFileInfo>

SyncWorker::SyncWorker(QObject *parent, SyncType type, const QString& search, const QString& _key, int _row) : QObject(parent)
{
    key = _key;
    row = _row;

    switch (type)
    {
        case BOOK:
        {
            QFileInfo f(Settings::getBookSyncPath());
            if(f.exists())
            {
                QMessageBox messageBox;
                messageBox.critical(0, "ERROR", "Book sync script file does not exists: " + Settings::getBookSyncPath());
                return;
            }
            arguments << Settings::getBookSyncPath();
            break;
        }
        case AUTHOR:
        {
            QFileInfo f(Settings::getAuthorSyncPath());
            if(f.exists())
            {
                QMessageBox messageBox;
                messageBox.critical(0, "ERROR", "Author sync script file does not exists: " + Settings::getAuthorSyncPath());
                return;
            }
            arguments << Settings::getAuthorSyncPath();
            break;
        }
        case DEFINE:
        {
            QFileInfo f(Settings::getDictionaryPath());
            if(f.exists())
            {
                QMessageBox messageBox;
                messageBox.critical(0, "ERROR", "Dictionary script file does not exists: " + Settings::getDictionaryPath());
                return;
            }
            arguments << Settings::getDictionaryPath();
            break;
        }
    }
    arguments << QString("\'%1\'").arg(search);

    script = new QProcess(parent);
    connect(script, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdOut()));
    connect(script, SIGNAL(readyReadStandardError()), this, SLOT(readStdErr()));
}

void SyncWorker::start()
{
    qDebug() << Settings::getPythonPath() << " " << arguments;
    script->start(Settings::getPythonPath(), arguments);
}

SyncWorker::~SyncWorker()
{
    delete script;
}

void SyncWorker::readStdOut()
{
    QByteArray b = script->readAllStandardOutput();
    QStringList str = QString(b).split("\n");
    emit sendSyncDetails(str, key, row);
}

void SyncWorker::readStdErr()
{
    QByteArray b = script->readAllStandardError();
    emit error(QString(b), this);
}

