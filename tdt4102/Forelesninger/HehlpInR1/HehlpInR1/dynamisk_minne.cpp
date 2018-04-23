/*
Skriv en funksjon som tar inn en størrelse n. Funksjonen 
skal returnere en peker som peker til et dynamisk allokert 
array av størrelse n. 
*/

int* allocateDynamicArray(int size)
{
	int* p = new int[size];
	return p;
	// return new int[size];
}