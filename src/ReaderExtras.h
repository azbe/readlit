#ifndef READEREXTRAS_H
#define READEREXTRAS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>

#include "src/SyncWorker.h"

namespace Ui {
class ReaderExtras;
}

class ReaderExtras : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderExtras(QWidget *parent = 0);
    ~ReaderExtras();

private:
    QVBoxLayout *extrasLayout;
    QWidget *findWidget;
    QHBoxLayout *findWidgetLayout;
    QLineEdit *findLineEdit;
    QPushButton *findButton;
    QWidget *lebtbWidget[2];
    QVBoxLayout *lebtbWidgetLayout[2];
    QWidget *lebtbSubWidget[2];
    QHBoxLayout *lebtbSubWidgetLayout[2];
    QLineEdit *lebtbLineEdit[2];
    QPushButton *lebtbPushButton[2];
    QTextBrowser *lebtbTextBrowser[2];

signals:
    void find(const QString& search);

private slots:
    void emitFind();
    void getDefinitions();
    void getDefinitionsDone(const QStringList& definitions);
    void getDefinitionsError(const QString& error, SyncWorker *worker);
};

#endif // READEREXTRAS_H
