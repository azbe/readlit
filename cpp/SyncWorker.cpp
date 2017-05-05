#include "src/SyncWorker.h"

SyncWorker::SyncWorker(QObject *parent, SyncType type, const QString& search, const QString& _key, int _row) : QObject(parent)
{
    key = _key;
    row = _row;

    switch (type)
    {
        case BOOK:
        {
            arguments << "sync_book.py";
            break;
        }
        case AUTHOR:
        {
            arguments << "sync_author.py";
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
    script->start("python2", arguments);
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

