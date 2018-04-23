#include "Person.h"
#include <cstring>
#include <iostream>
using namespace std;

void Person::copy_name(char* name)
{
	int length = strlen(name);
	this->name = new char[30];
	for (int i = 0; i < length; i++) {
		this->name[i] = name[i];
	}
	this->name[length] = 0;
}

Person::Person(char* name, int age)
{
	copy_name(name);
	this->age = age;
}

Person::Person(const Person& p)
{
	cout << "Copy-constructor called!" << endl;
	copy_name(p.name);
	this->age = p.age;

}