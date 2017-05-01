#include "src/ReaderExtras.h"
#include "ui_ReaderExtras.h"

ReaderExtras::ReaderExtras(QWidget *parent) :
    QWidget(parent)//,
    //ui(new Ui::ReaderExtras)
{
    //ui->setupUi(this);
    setContentsMargins(0,0,0,0);
    extrasLayout = new QVBoxLayout(this);

    findWidget = new QWidget(this);
    findWidget->setContentsMargins(0,0,0,0);
    findWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    findWidgetLayout = new QHBoxLayout(findWidget);
    findLineEdit = new QLineEdit(findWidget);
    findLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    findButton = new QPushButton("Find", findWidget);
    findWidgetLayout->addWidget(findLineEdit);
    findWidgetLayout->addWidget(findButton);

    for (int index = 0; index < 2; index++)
    {
        lebtbWidget[index] = new QWidget(this);\
        lebtbWidget[index]->setContentsMargins(0,0,0,0);
        lebtbWidgetLayout[index] = new QVBoxLayout(lebtbWidget[index]);
        lebtbSubWidget[index] = new QWidget(lebtbWidget[index]);
        lebtbSubWidget[index]->setContentsMargins(-9,0,-9,0);
        lebtbSubWidgetLayout[index] = new QHBoxLayout(lebtbSubWidget[index]);
        lebtbLineEdit[index] = new QLineEdit(lebtbSubWidget[index]);
        lebtbLineEdit[index]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        switch (index)
        {
            case 0:
            {
                lebtbPushButton[index] = new QPushButton("Define", lebtbSubWidget[index]);
                break;
            }
            case 1:
            {
                lebtbPushButton[index] = new QPushButton("Translate", lebtbSubWidget[index]);
            }
        }
        lebtbSubWidgetLayout[index]->addWidget(lebtbLineEdit[index]);
        lebtbSubWidgetLayout[index]->addWidget(lebtbPushButton[index]);
        lebtbTextBrowser[index] = new QTextBrowser(lebtbWidget[index]);
        lebtbWidgetLayout[index]->addWidget(lebtbSubWidget[index]);
        lebtbWidgetLayout[index]->addWidget(lebtbTextBrowser[index]);
    }

    extrasLayout->addWidget(findWidget);
    extrasLayout->addWidget(lebtbWidget[0]);
    extrasLayout->addWidget(lebtbWidget[1]);
}

ReaderExtras::~ReaderExtras()
{
    //delete ui;
    for (int i = 0; i < 2; i++)
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
