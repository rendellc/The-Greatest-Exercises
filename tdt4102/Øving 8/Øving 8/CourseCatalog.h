#pragma once
#include <string>
#include <map>

using namespace std;

class CourseCatalog {
private:
	map<string, string> courseTable;

	// private utils
	bool checkCourseExist(string code) const;
public:
	// default constructor
	CourseCatalog();
	// construct from file
	CourseCatalog(string filename);

	// *** access methods ***
	void addCourse(string code, string name);
	void removeCourse(string code);
	string getCourse(string code) const;
	void printAllCourses() const;
	friend ostream& operator<<(ostream& out, const CourseCatalog& catalog);

	// *** files ***
	void saveToFile(string filename) const;
	void importFromFile(string filename);
};