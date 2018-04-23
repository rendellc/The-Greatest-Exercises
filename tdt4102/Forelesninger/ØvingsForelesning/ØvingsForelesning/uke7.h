#pragma once
/*
void main_uke7();

class Klasse {
private:
	int tall;
public:
	Klasse() { tall = 0; }
};
/*
class SafeArray {
private:
	int* data;
	int currentSize;
	int totalSize = 100;
public:
	SafeArray() {
		totalSize = 10;
		currentSize = 0;
	}

	int size() { return currentSize; }
	int& operator[] (const int index) {
		if (index >= currentSize && currentSize < totalSize) {
			currentSize++;
			index = currentSize
		} 
		else if (index >= totalSize) {
			cerr << "index out of bounds" << endl;
			index = totalSize - 1;
		}
		return data[index];
	}
};
*/