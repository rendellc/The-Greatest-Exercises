using namespace std;

class Person {
private:
	int age;
	char* name;
	char gender;
public:
	Person();
	Person(const Person& p);
	Person(char* name, int age);
	~Person();

	void copy_name(char* name);
	char* getName() const { return name; }
	int getAge() const { return age; }
};