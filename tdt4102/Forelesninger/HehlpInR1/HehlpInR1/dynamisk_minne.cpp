/*
Skriv en funksjon som tar inn en st�rrelse n. Funksjonen 
skal returnere en peker som peker til et dynamisk allokert 
array av st�rrelse n. 
*/

int* allocateDynamicArray(int size)
{
	int* p = new int[size];
	return p;
	// return new int[size];
}