#ifndef READLITWINDOW_H
#define READLITWINDOW_H

#include <QWidget>
#include <QTabWidget.h>

class ReadLitWindow : public QWidget
{
	Q_OBJECT

public:
	explicit ReadLitWindow(QWidget *parent = 0, int width = 800, int height = 600);
	~ReadLitWindow();

	void addTab(QWidget* frame, const QString& label);
	void setWidgets(QLayout* mainLayout);
	int countTabs() const; //returneaza numarul de taburi

private:
	QTabWidget* tabs;
};

#endif //READLITWINDOW_H