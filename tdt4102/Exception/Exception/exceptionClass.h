#pragma once
#include <stdexcept>
#include <string>
#include <iostream>

class superfeil : public std::exception {
private:

public:
	superfeil() { what(); }
	superfeil(int i) { std::cerr << i << " was thrown" << std::endl; }
	superfeil(std::string e) { std::cerr << "\"" << e << "\" was thrown" << std::endl; }
	std::string what() {
		std::cerr << "Generisk feil" << std::endl;
	}
};