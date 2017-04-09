#ifndef BROWSERBUTTON_H
#define BROWSERBUTTON_H

#include <QWidget>
#include <QToolButton>

class BrowserButton : public QToolButton
{
public:
	BrowserButton(QWidget *parent = 0);
	~BrowserButton();
};

#endif //BROWSERBUTTON_H
