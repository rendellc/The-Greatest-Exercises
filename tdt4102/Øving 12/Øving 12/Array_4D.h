#pragma once
#include <memory>
#include <cassert>

template<typename T>
class Array_4D{
private:
	std::unique_ptr<T[]> data;
	const size_t size;

	size_t index(size_t mainRow, size_t mainCol, size_t smallRow, size_t smallCol) const {
		size_t calcIndex = mainRow*size*size*size + mainCol*size*size
			+ smallRow*size + smallCol;
		assert(calcIndex < size*size*size*size);
		return calcIndex;
	}
public:
	/*  Creates array of size size^4 */
	Array_4D(size_t inputSize) 
		: size(inputSize)
		, data(new T[inputSize*inputSize * inputSize*inputSize])		 
	{}

	void set(size_t mainRow, size_t mainCol, size_t smallRow, size_t smallCol, const T& element) {
		data[index(mainRow, mainCol, smallRow, smallCol)] = element;
	}

	void get(size_t mainRow, size_t mainCol, size_t smallRow, size_t smallCol) const {
		return data[index(mainRow, mainCol, smallRow, smallCol)];
	}


};