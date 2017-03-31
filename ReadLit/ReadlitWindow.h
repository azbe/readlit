#ifndef READLITWINDOW_H
#define READLITWINDOW_H

#include <QWidget>
#include <QTabWidget.h>

class ReadLitWindow : public QWidget
{
	Q_OBJECT

public:
	explicit ReadLitWindow(QWidget *parent = 0, int width = 800, int height = 400);
	~ReadLitWindow();

	void addTab(QWidget* frame, const QString& label);
	int countTabs() const;

private:
	QTabWidget* tabs;

};

#endif //READLITWINDOW_H