#ifndef BROWSERBUTTON_H
#define BROWSERBUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QStringList>
#include <QFileDialog>
#include "src/Constants.h"

class BrowserButton : public QToolButton
{
    Q_OBJECT

public:
    enum BrowserButtonType { ANY, DIR, PYTHON, JSON};

    BrowserButton(QWidget *parent = 0, const BrowserButtonType& type = ANY);
	~BrowserButton();

signals:
    void sendPaths(const QStringList& paths);

private:
    void mousePressEvent(QMouseEvent *event);

    BrowserButtonType type;
};

#endif //BROWSERBUTTON_H
