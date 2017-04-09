#ifndef DATABUTTON_H
#define DATABUTTON_H

#include <QPushButton>

class DataButton : public QPushButton
{
public:
	DataButton(const QString& text, QWidget *parent);
	~DataButton();
};

#endif //DATABUTTON_H
