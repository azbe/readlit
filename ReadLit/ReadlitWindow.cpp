#include "ReadlitWindow.h"
#include <QVBoxLayout>

ReadLitWindow::ReadLitWindow(QWidget *parent, int width, int height) : QWidget(parent)
{
	resize(width, height);

	tabs = new QTabWidget;

	QVBoxLayout *mainLayout = new QVBoxLayout;
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

