#ifndef DATATABLE_H
#define DATATABLE_H

#include <QWidget>
#include <QTableWidget>

class DataTable : public QTableWidget
{
public:
	DataTable(QWidget *parent);
	~DataTable();
};

#endif //DATATABLE_H