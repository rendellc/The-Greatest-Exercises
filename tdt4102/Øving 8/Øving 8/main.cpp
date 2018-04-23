#include "basicFileIO.h"
#include "CourseCatalog.h"
#include <iostream>
#include <ctime>
#include <clocale>
using namespace std;

void testMap();

int main()
{
	setlocale(LC_ALL, "nb-NO");
	writeLineToFile("oppgave_1a.txt");
	readFromFileToFile("oppgave_1b_input.txt", "oppgave_1b_output.txt");
	countCharactersInFile("Teh_bible.txt");
	
	testMap();

	wordStatistics("Oving 1 - exphil.txt");
	system("pause");
	return 0;
}

void testMap()
{
	CourseCatalog cat;

	cat.addCourse("MA0301", "Elementær Diskret Matematikk");
	cat.addCourse("MA3301", "Beregnings- og kompleksitetsteori");
	cat.addCourse("TDT4110", "Informasjonsteknologi Grunnkurs");
	cat.addCourse("TDT4102", "Prosedyre- og Objektorientert Programmering");
	cat.addCourse("TMA4100", "Matematikk 1");
	cat.addCourse("TMA4105", "Matematikk 2");

	cout << "\n" << cat;
	
	//oppdater tdt4102 til c++
	cat.addCourse("TDT4102", "C++");
	//cout << "\n" << cat;

	// save to file
	string filename("Course Catalog.txt");
	cout << endl;
	cat.saveToFile(filename);

	// load from file
	CourseCatalog newCat(filename);
	cout << "\n" << newCat;
}
