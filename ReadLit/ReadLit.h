#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ReadLit.h"

class ReadLit : public QMainWindow
{
	Q_OBJECT

public:
	ReadLit(QWidget *parent = Q_NULLPTR);

private:
	Ui::ReadLitClass ui;
};
