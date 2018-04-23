#pragma once
#include <string>
#include <iostream>
#include <forward_list>

class Person {
private:
	std::string firstName;
	std::string lastName;
public:
	Person(std::string firstName, std::string lastName) : firstName(firstName), lastName(lastName) {}
	Person(std::string fullName) {
		setFullName(fullName);
	}
	Person(const Person& person) : firstName(person.firstName), lastName(person.lastName) {}

	std::string getFirstName() const { return firstName; }
	std::string getLastName() const { return lastName; }
	std::string getName() const { return firstName + " " + lastName; }

	void setFirstName(std::string firstName) { this->firstName = firstName; }
	void setLastName(std::string lastName) { this->lastName = lastName; }
	void setFullName(std::string name) {
		char space = name.find(' ');
		firstName = name.substr(0,space);
		lastName = name.substr(space + 1);
	}

	bool operator<(const Person& rhs) const {
		if (lastName < rhs.lastName)
			return true;
		if (lastName > rhs.lastName)
			return false;

		// last names are equal
		return firstName < rhs.firstName;
	}

	friend std::ostream& operator<<(std::ostream& out, const Person& person); // allows inline
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
	out << person.getName();
	return out;
}

void insertSorted(std::forward_list<Person>& list, Person p) {
	if (list.empty()) {
		list.push_front(p);
		return;
	}

	
	std::forward_list<Person>::iterator it = list.before_begin();
	while (p < *(++it)) {} // gets iterator before where p should be inserted
	list.insert_after(it, p);
}