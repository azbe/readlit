#ifndef LISTCONTAINER_H
#define LISTCONTAINER_H
#include <vector>

#include <QWidget>

#include "Book.h"

//Partea din Local cu lista de carti/autori (va cere bazei de date datele)

class ListContainer : public QWidget
{

public:
	ListContainer(QWidget *parent);
	ListContainer(const ListContainer& lc);
	~ListContainer();

	void addItem(std::string item, const bool& book = true);
	void removeItem(const int& index, const bool& book = true);

	std::vector<std::string> getBooks() const;
	std::vector<std::string> getAuthors() const;

private:
	std::vector<std::string> books;
	std::vector<std::string> authors;
};

#endif //LISTCONTAINER_H