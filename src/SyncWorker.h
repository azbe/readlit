#ifndef SYNCWORKER_H
#define SYNCWORKER_H

#include <QObject>
#include <QProcess>

#include "src/Settings.h"

class SyncWorker : public QObject
{
    Q_OBJECT

public:
    enum SyncType { BOOK, AUTHOR };

    explicit SyncWorker(QObject *parent, SyncType type, const QString& search, const QString& _key, int _row);
    ~SyncWorker();
    void start();

signals:
    void sendSyncDetails(const QStringList& info, const QString& key, int row);
    void error(const QString& err, SyncWorker *worker);

private slots:
    void readStdOut();
    void readStdErr();

private:
    QStringList arguments;
    QProcess *script;
    QString key;
    int row;
};

#endif // SYNCWORKER_H
