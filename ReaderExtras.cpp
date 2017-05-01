#include "ReaderExtras.h"
#include "ui_ReaderExtras.h"

ReaderExtras::ReaderExtras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderExtras)
{
    ui->setupUi(this);
}

ReaderExtras::~ReaderExtras()
{
    delete ui;
}
