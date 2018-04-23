#include "klasser.h"
using namespace std;

int main_klasser()
{
	Person p("Rendell", 20);

	cout << p.getName() << endl;

	p.setName("Eline");

	cout << p.getName() << endl;

	system("pause");
	return 0;
}


Person::Person(char* name, int age)
{
	this->name = name;
	this->age = age;
}

char* Person::getName() const
{
	return name;
}

void Person::setName(char* name)
{
	this->name = name;
}