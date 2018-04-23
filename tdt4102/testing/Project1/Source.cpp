#include <iostream>
#include <vector>
#include <algorithm>

static void transmit_item(int i) {
	std::cout << i << std::endl;
}



int main() {
	struct filter {
		filter(int lim) : limit(lim) {}
		bool operator() (int i) { return i <= limit; }
		int limit;

	} firstFilter(50);

	struct factorial {
		factorial(int n) : n(n) {}
		int n;

		int operator() (int n) {
			return (n <= 1) ? 1 : n * this->operator() (n-1);
		}
	};

	std::cout << factorial(5) << std::endl;


	system("pause");
	return 0;
}