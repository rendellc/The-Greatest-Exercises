#include <cstdlib>
#include <random>

int randomWithLimits(int lowerLimit, int upperLimit)
{
	using namespace std;
	int randomNumber = std::rand(); //generer et tilfeldig tall
	
	// tilpasser tallet til grensene
	upperLimit += 1; //inkluderer øvre grense
	randomNumber = randomNumber % (upperLimit - lowerLimit);
	randomNumber = randomNumber + lowerLimit;

	return randomNumber;
}

int modernRandomWithLimits(int lowerLimit, int upperLimit)
{
	using namespace std;
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> uniform(lowerLimit, upperLimit);
	
	int randomNumber = uniform(generator);

	return randomNumber;

}