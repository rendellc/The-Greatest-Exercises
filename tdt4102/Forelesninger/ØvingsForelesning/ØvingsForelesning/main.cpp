#include <iostream>
//#include "uke5_struct_class.h"
#include "basic_vector.h"
#include "uke7.h"
#include "ComplexNumbers.h"
#include "Person.h"

using namespace std;

void uke9();

int main()
{
	//uke5_tests();
	//basic_vector();
	//main_uke7();

	//Complex a;
	//Complex b(5);
	//Complex c(2, 3);

	uke9();

	system("pause");
	return 0;
}

void uke9()
{
	Person person("John", 24);
	cout << person.getName() << endl;
}