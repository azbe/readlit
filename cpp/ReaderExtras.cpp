#include "src/ReaderExtras.h"

ReaderExtras::ReaderExtras(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    extrasLayout = new QVBoxLayout(this);

    findWidget = new QWidget(this);
    findWidget->setContentsMargins(0,0,0,0);
    findWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    findWidgetLayout = new QHBoxLayout(findWidget);
    findLineEdit = new QLineEdit(findWidget);
    findLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    findButton = new QPushButton("Find", findWidget);
    connect(findButton, SIGNAL(clicked(bool)), this, SLOT(emitFind()));
    findButton->setMaximumWidth(75);
    findWidgetLayout->addWidget(findLineEdit);
    findWidgetLayout->addWidget(findButton);

    for (int index = 0; index < 1; index++)
    {
        lebtbWidget[index] = new QWidget(this);\
        lebtbWidget[index]->setContentsMargins(0,0,0,0);
        lebtbWidgetLayout[index] = new QVBoxLayout(lebtbWidget[index]);
        lebtbSubWidget[index] = new QWidget(lebtbWidget[index]);
        lebtbSubWidget[index]->setContentsMargins(-9,0,-9,0);
        lebtbSubWidgetLayout[index] = new QHBoxLayout(lebtbSubWidget[index]);
        lebtbLineEdit[index] = new QLineEdit(lebtbSubWidget[index]);
        lebtbLineEdit[index]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        switch (index)
        {
            case 0:
            {
                lebtbPushButton[index] = new QPushButton("Define", lebtbSubWidget[index]);
                connect(lebtbPushButton[index], SIGNAL(clicked(bool)), this, SLOT(getDefinitions()));
                break;
            }
            case 1:
            {
                lebtbPushButton[index] = new QPushButton("Translate", lebtbSubWidget[index]);
            }
        }
        lebtbPushButton[index]->setMaximumWidth(75);
        lebtbSubWidgetLayout[index]->addWidget(lebtbLineEdit[index]);
        lebtbSubWidgetLayout[index]->addWidget(lebtbPushButton[index]);
        lebtbTextBrowser[index] = new QTextBrowser(lebtbWidget[index]);
        lebtbWidgetLayout[index]->addWidget(lebtbSubWidget[index]);
        lebtbWidgetLayout[index]->addWidget(lebtbTextBrowser[index]);
    }

    extrasLayout->addWidget(findWidget);
    extrasLayout->addWidget(lebtbWidget[0]);
    //extrasLayout->addWidget(lebtbWidget[1]);
}

ReaderExtras::~ReaderExtras()
{
    for (int i = 0; i < 1; i++)
    {
        delete lebtbTextBrowser[i];
        delete lebtbLineEdit[i];
        delete lebtbPushButton[i];
        delete lebtbSubWidgetLayout[i];
        delete lebtbSubWidget[i];
        delete lebtbWidgetLayout[i];
        delete lebtbWidget[i];
    }
    delete findButton;
    delete findLineEdit;
    delete findWidgetLayout;
    delete findWidget;
    delete extrasLayout;
}

void ReaderExtras::getDefinitions()
{
    if (lebtbLineEdit[0]->text().isEmpty())
        return;
    SyncWorker *worker = new SyncWorker(this, SyncWorker::DEFINE, lebtbLineEdit[0]->text(), "doesn't matter", 0);
    connect(worker, SIGNAL(sendSyncDetails(QStringList, QString, int)), this, SLOT(getDefinitionsDone(QStringList)));
    connect(worker, SIGNAL(error(QString, SyncWorker*)), this, SLOT(getDefinitionsError(QString, SyncWorker*)));
    worker->start();
}

void ReaderExtras::getDefinitionsDone(const QStringList& definitions)
{
    QString def;
    for (int index = 0; index < definitions.size(); index++)
        def.append(definitions.value(index)).append('\n');
    lebtbTextBrowser[0]->setText(def);
}

void ReaderExtras::getDefinitionsError(const QString &error, SyncWorker *worker)
{
    qDebug() << "SubtabBooks::getSyncDetailsError - Error: " << error;
    QMessageBox messageBox;
    messageBox.critical(0, "ERROR", "There was an error getting word definitions: " + error);
    delete worker;
}

void ReaderExtras::emitFind()
{
    if (findLineEdit->text().isEmpty())
        return;
    emit find(findLineEdit->text());
}
