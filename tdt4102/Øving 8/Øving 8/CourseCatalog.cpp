#include "CourseCatalog.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// default constructor, does nothing
CourseCatalog::CourseCatalog() {}

// Construct from file
CourseCatalog::CourseCatalog(string filename)
{
	importFromFile(filename);
}

// returns true if course exists
bool CourseCatalog::checkCourseExist(string code) const
{
	// keys are unique so count method will return 0 or 1
	return courseTable.count(code) == 1;
}

void CourseCatalog::addCourse(string code, string name)
{
	courseTable[code] = name;
}

void CourseCatalog::removeCourse(string code)
{
	if (checkCourseExist(code)) {
		courseTable.erase(code);
	}
	else {
		cerr << "Course doesn't exist" << endl;
	}
}

string CourseCatalog::getCourse(string code) const
{
	if (checkCourseExist(code)) {
		return courseTable.at(code);
	}
	else {
		cerr << "Course doesn't exist" << endl;
		return "";
	}
}

void CourseCatalog::printAllCourses() const
{
	for (auto& iter : courseTable) {
		cout << iter.first << ": " << iter.second << endl;
	}
}

ostream& operator<<(ostream& out, const CourseCatalog& catalog)
{
	for (auto& iter : catalog.courseTable) {
		out << iter.first << " " << iter.second << endl;;
	}

	return out;
}

void CourseCatalog::saveToFile(string filename) const
{
	cout << "Saving as " << filename << ": ";
	// open file
	ofstream file(filename);
	
	if (file.fail()) {
		file.close();
		cout << "Failed" << endl;
		return;
	}
	
	file << *this;
	
	file.close();
	cout << "Complete" << endl;
}

void CourseCatalog::importFromFile(string filename)
{
	cout << "Importing " << filename << ": ";

	ifstream file(filename);
	if (file.fail()) {
		file.close(); // er dette egentlig lurt?
		cout << "Failed" << endl;
		return;
	}

	string input = "";
	const int KEY_LENGTH = 7;
	while (getline(file, input)) {
		string key = input.substr(0,KEY_LENGTH);
		string name = input.substr(KEY_LENGTH, string::npos);
		addCourse(key, name);
		
	}
	// close file
	file.close();
	cout << "Complete" << endl;
}










