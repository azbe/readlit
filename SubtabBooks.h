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
	QWidget *scanner;
	QWidget *books;
	QLayout *bookLayout;
};

#endif //SUBTABBOOKS_H