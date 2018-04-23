#pragma once
#include <memory>
#include <cassert>

//#define INDEX_DEBUG

/*	T need copy-constructor

*/
template<typename T>
class Array2D {
private:
	std::unique_ptr<T[]> data;
	const size_t width;
	const size_t height;

	size_t index(size_t row, size_t col) const {
		assert(row < height && col < width);
		size_t calcIndex = row*width + col;
		assert(calcIndex < width*height);

		#ifdef INDEX_DEBUG
		std::cout << "Height= " << height << ", Width= " << width
			<< ", (row,col)= (" << row << ", " << col << "), calcIndex= "
			<< calcIndex << "\n";
		#endif // INDEX_DEBUG

		return calcIndex;
	}
public:
	/*  Creates array */
	Array2D(size_t height, size_t width)
		: height(height), width(width)
		, data(new T[height*width])
	{}

	/*  Copy-constructor */
	Array2D(const Array2D<T>& rhs)
		: height(rhs.height), width(rhs.width)
		, data(new T[rhs.height*rhs.width])
	{
		// copy rhs.data over to *this
		for (size_t row = 0; row < width; ++row) {
			for (size_t col = 0; col < height; ++col) {
				this->set(row, col, rhs.get(row, col));
			}
		}
	}

	/*  Assignment operator */
	Array2D<T>& operator= (Array2D<T> rhs) {
		swap(*this, rhs);
		return *this;
	}


	void set(size_t row, size_t col, const T& element) {
		data[index(row, col)] = element;
	}

	T get(size_t row, size_t col) const {
		return data[index(row, col)];
	}


	friend void swap(Array2D<T>& lhs, Array2D<T>& rhs);
};

/*  Swap function overload */
template<typename T>
void swap(Array2D<T>& lhs, Array2D<T>& rhs) {
	using std::swap;

	swap(lhs.height, rhs.height);
	swap(lhs.width, rhs.width);
	std::swap(data, rhs.data);
}

#undef INDEX_DEBUG