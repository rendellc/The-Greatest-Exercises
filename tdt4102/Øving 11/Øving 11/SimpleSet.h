#include <memory>
#include <algorithm>
#include <cassert>
#include <iostream>

class SimpleSet{
private:
	/** Dynamic array containing set elements **/
	std::unique_ptr<int[]> data;
	/** Current number of elements **/
	int currentSize;
	/** Max capasity of data **/
	int maxSize;
	/** changes step size of capacity increases 
		Default = 10 **/
	const int incrementStepSize = 10;
	
	/** Returns the index where i may be found, else an invalid - 1. **/
	int find(int element) {
		// non-recursive binary search
		int startIndex = 0;
		int endIndex = currentSize;
		int middleIndex = startIndex + (startIndex + endIndex) / 2;// middle element, (maybe write a lambda function)
		if (element < data[middleIndex]) 



		// n not found, return invalid index
		return -1;
	}

	/** Resizes data, superflous elements are dropped. 
		Sets maxSize to size of resized data			  
		sets currentSize to minimum of currentSize and maxSize **/
	void resize(int newSize) {
		std::cout << "Resize called" << std::endl;
		
		maxSize = newSize;
		std::unique_ptr<int[]> tempData(new int[maxSize]);
		
		// copy to new table
		for (int i = 0, end = std::min(maxSize, currentSize); i < end; ++i) {
			tempData[i] = data[i];
		}

		data = std::move(tempData);
	}

	/** Shifts all one index to the left, data at fromIndex will be overwritten 
		Reduces current size by one **/
	void shiftDown(int fromIndex) {
		--currentSize;
		for (int i = fromIndex; i < currentSize; ++i) {
			data[i] = data[i + 1]; // accounts for --currentSize;
		}
	}
	/** Shifts all elements above fromIndex one element to the right
		Data in data[fromIndex] will be duplicated in data[fromIndex + 1]
		Increments currentSize
		Caller must make sure there is room ie. maxSize >= currentSize + 1 **/
	void shiftUp(int fromIndex) {
		assert(currentSize < maxSize);
		// ++currentSize;
		for (int i = currentSize; i > fromIndex; --i) {
			data[i - 1] = data[i]; // accounts for --currentSize;
		}
	}

public:
    /** Construct empty set **/
    SimpleSet(int incrementStepSize = 25, int maxSize = 10)
		: currentSize(0), maxSize(maxSize), incrementStepSize(incrementStepSize), data(nullptr) {}
    
	/** Insert i into set, return true if the element was inserted, else false **/
	bool insert(int element) {
		if (exists(element)) // check if element existed, equivalent to exists(element)
			return false;
		if (currentSize == maxSize){
			resize(maxSize + 30); // increase storage capacity
		}

		// add new data
		int index = find(element);
		shiftUp(index);
		data[index] = element;
		return true;
	}

    /** Returns true if i is in the set **/
	bool exists(int element) {
		return find(element) != -1;
	}
    
	/** Removes i from the set, return true if an element was removed,
		returns false if element not in set**/
	bool remove(int element) {
		int index = find(element);
		if (index == -1)
			return false; // element not in set
		assert(index < currentSize);
		shiftDown(index);
		return true;
	}

	int getCurrentSize() const {
		return currentSize;
	}
   
	// caller must make sure index is valid
	int getElement(int index) const {
		std::cout << "index: " << index << ", currentSize: " << currentSize << '\n';
		assert(0 <= index && index < currentSize);
		return data[index];
	}

	void print() const {
		std::cout << "currentSize = " << currentSize << std::endl;
		for (int i = 0; i < currentSize; ++i) {
			std::cout << data[i] << '\n';
		}
	}
};