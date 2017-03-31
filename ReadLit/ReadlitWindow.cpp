#include "ReadlitWindow.h"
#include <QVBoxLayout>

ReadLitWindow::ReadLitWindow(bool isTab, QWidget *parent, int width, int height) : QWidget(parent)
{
	resize(width, height);
	tabs = new QTabWidget;

	QBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabs);
	setLayout(mainLayout);
}

ReadLitWindow::~ReadLitWindow()
{
}

void ReadLitWindow::addTab(QWidget* frame, const QString& label)
{
	tabs->addTab(frame, label);
}

int ReadLitWindow::countTabs() const
{
	if (tabs != NULL) return tabs->count();
	return 0;
}

