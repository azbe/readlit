#include <QGridLayout>

#include "ReadlitWindow.h"
#include "utils.h"

ReadLitWindow::ReadLitWindow(QWidget *parent, int width, int height) : QWidget(parent)
{
	resize(width, height);
	tabs = new QTabWidget;

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(tabs);
	setLayout(layout);
}

ReadLitWindow::~ReadLitWindow()
{
		
}

void ReadLitWindow::addTab(QWidget* frame, const QString& label)
{
	tabs->addTab(frame, label);
}

void ReadLitWindow::setWidgets(QLayout* layout)
{
	setLayout(layout);
}

int ReadLitWindow::countTabs() const
{
	if (tabs != NULL) return tabs->count();
	return 0;
}
