#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>  
#include "SimpleSet.h"
#include "templateOppg.h"
#include "Person.h"


void iteratorOppgave1();
void replace(std::vector<std::string>& vec, std::string old, std::string replacement);

void setOppgave2();
void printSet(const std::set<int>& set);
void removeDivBy(std::set<int>& set, int n);

void treeTest();


void simpleSetOppgave();
void removeDivBySimple(SimpleSet& set, int n);
void testPerson();

int main() {
	
	//iteratorOppgave1();
	//setOppgave2();

	//simpleSetOppgave();

	//shuffleTest();

	testPerson();
	
	system("pause");
	return 0;
}

void iteratorOppgave1() {
	std::vector<std::string> vec{ "Lorem", "Ipsum", "Dolor", "Sit", "Amet", "Consectetur" };

	std::cout << "--- Vanlig Rekkefølge:\n";
	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << '\n';
	}


	std::cout << "--- Reversert Rekkefølge:\n";
	for (std::vector<std::string>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it) {
		std::cout << *it << '\n';
	}

	replace(vec, "Dolor", "SomethingSomethingChange");
	replace(vec, "Lorem", "NyLorem");
	replace(vec, "NotInVector", "ShouldNotBeInVector");
	std::cout << "--- Endret rekkefølge:\n";
	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << '\n';
	}

}

void replace(std::vector<std::string>& vec, std::string old, std::string replacement) {
	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if (*it == old) {
			it = vec.erase(it);
			it = vec.insert(it, replacement);
		}
	}
}

void setOppgave2() {
	const int limit = 10000;
	const int primeLimit = static_cast<int>(sqrt(limit));

	std::set<int> set;
	for (int i = 2; i <= limit; ++i) {
		set.insert(i);
	}
	//std::cout << "--- start set:\n";
	//printSet(set);


	for (int i = 2; i <= primeLimit; ++i) {
		removeDivBy(set, i);
	}
	std::cout << "--- Primtallset:\n";
	printSet(set);
}

void simpleSetOppgave() {
	SimpleSet simpleset;
	for (int i = 0; i <= 100; ++i) {
		simpleset.insert(i);
	}

	std::cout << "--- Simpelset 0 to 100\n";
	simpleset.print();

	std::cout << "--- Simpleset primes\n";
	for (int i = 2; i < 100; ++i) {
		removeDivBySimple(simpleset, i);
	}
	simpleset.print();
}

void printSet(const std::set<int>& set) {
	for (const auto& it : set) {
		std::cout << it << '\n';
	}
}

void removeDivBy(std::set<int>& set, int n) {
	for (std::set<int>::iterator it = set.begin(); it != set.end(); ) {
		if (*it % n == 0 && *it != n)
			it = set.erase(it);
		else
			++it;
	}
}

void removeDivBySimple(SimpleSet& set, int n) {
	for (int i = 0, end = set.getCurrentSize(); i < end; ++i) {
		auto element = set.getElement(i);
		if (element % n == 0 && element != n)
			set.remove(element);
	}
}


void testPerson() {
	Person a("Knut", "Knuten");
	Person b("Bjarne", "Baat");
	Person c("John Hansen");

	//std::cout << a << '\n' << b << '\n' << c << std::endl;
	
	std::forward_list<Person> list;
	insertSorted(list, a);
	insertSorted(list, b);
	insertSorted(list, c);
	for (std::forward_list<Person>::const_iterator it = list.cbegin(); it != list.cend(); ++it) {
		std::cout << *it << '\n';
	}
}