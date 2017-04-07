#ifndef SCANNERBUTTON_H
#define SCANNERBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class ScannerButton : public QPushButton
{
public:
	ScannerButton(const QString& text, QWidget *parent = 0);
	~ScannerButton();
};

#endif //SCANNERBUTTON_H