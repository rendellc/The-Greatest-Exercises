#pragma once


#ifndef PROJECT_PERSON_H
#define PROJECT_PERSON_H
#include <iostream>

int main_klasser();

class Person {
private:
	int age;
	char* name;
public:
	Person(char* name, int age);

	// *** access ***
	char* getName() const;
	void setName(char* name);
};


#endif // !PROJECT_PERSON_H


