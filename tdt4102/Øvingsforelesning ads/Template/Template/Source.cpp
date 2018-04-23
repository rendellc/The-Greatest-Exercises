#include <vector>
#include <iostream>
#include <initializer_list>

template<typename T>
class Class {
private:
	std::vector<T> vec;
public:
	Class(std::initializer_list<T> list);
	void print() const;
};

template<typename T>
void Class::print() const {
	for (std::vector<T>::iterator iter = vec.begin(); iter != v.end(); ++iter) {
		cout << *iter << '\n';
	}
}

template<typename T>
Class::Class(std::initializer_list<T> list) {
	std::vector<T>::iterator vecIter = vec.begin();
	for (std::initializer_list<T>::iterator iter = list.begin(); iter != list.end(); ++iter) {
		vecIter = vec.insert(vecIter, *iter);
	}
}