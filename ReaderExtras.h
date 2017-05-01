#ifndef READEREXTRAS_H
#define READEREXTRAS_H

#include <QWidget>

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
    Ui::ReaderExtras *ui;
};

#endif // READEREXTRAS_H
