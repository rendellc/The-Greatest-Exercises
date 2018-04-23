
class Test123 {
private:
	int a = 1;
public:
	void printInt() const;
};

namespace Test123 {
	void printInt() const {
		cout << a
	}
}


int main(void) 
{
	int* p = nullptr;

	delete p;


	return 0;
}