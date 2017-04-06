#ifndef READLITWINDOW_H
#define READLITWINDOW_H
/*
#include <QWidget>
#include <QTabWidget.h>

class ReadLitWindow : public QWidget
{
	Q_OBJECT

public:

	enum windowType { TABBED, GRID, HORIZONTAL, VERTICAL};

	explicit ReadLitWindow(QWidget *parent = 0, const windowType& type = TABBED);
	
	~ReadLitWindow();

	
	int countTabs() const; //returneaza numarul de taburi

private:
	const int BASE_WIDTH = 800;
	const int BASE_HEIGHT = 600;

	QTabWidget	*tabWidget;
	QLayout	*tabLayout;
	std::vector<QWidget> widgets;
};
*/
#endif //READLITWINDOW_H