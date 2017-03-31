#ifndef AUTHOR_H
#define AUTHOR_H

class Author
{
public:
	Author();
	~Author();

private:
	std::string name; //Last+First name, nume si prenume
	std::vector<std::string> booksTitles; //Oriunde avem carti, eficientizam pastrand doar titlul si cautand cartea in baza de date
	int yearBirth;
	int yearDeath;
	std::string bio;
	//Si altele
};

#endif //AUTHOR_H