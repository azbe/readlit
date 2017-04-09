#ifndef DATALIST_H
#define DATALIST_H

#include <QWidget>
#include <QListWidget>

class DataList : public QListWidget
{
public:
	DataList(QWidget *parent);
	~DataList();
};

#endif //DATALIST_H