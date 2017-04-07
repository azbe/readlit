#ifndef SUBTABBOOKS_H
#define SUBTABBOOKS_H

#include <QWidget>
#include <QLayout>

class SubtabBooks : public QWidget
{
public:
	SubtabBooks(QWidget *parent);
	~SubtabBooks();

private:
	QWidget *bookWidgets[2];
	QLayout *bookLayout;
};

#endif //SUBTABBOOKS_H