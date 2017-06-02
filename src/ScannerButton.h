#ifndef SCANNERBUTTON_H
#define SCANNERBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QMouseEvent>
#include <QLineEdit>
#include <QDebug>
#include "src/Settings.h"

class ScannerButton : public QPushButton
{
    Q_OBJECT

public:

    ScannerButton(QWidget *parent, QLineEdit *folderPaths);
	~ScannerButton();

    void mousePressEvent(QMouseEvent *event);
    QStringList getBooksInFolder(QString folderPath);

private:
    QLineEdit *folderPaths;

    signals:
    void sendBookPaths(QStringList bookPaths);
};

#endif //SCANNERBUTTON_H
