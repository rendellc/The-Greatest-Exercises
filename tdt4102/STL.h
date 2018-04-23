// *** Standard Template Library

// felles
    // iteratorer, begin(), begin() + 2 etc...
    // størelse: size(), empty()
    // insetting/sletting
#include <iostream>
#inlcude <vector>

vector<int> v;
v.insert(v.begin(), 2) // setter inn 2 ved begin()
int tall = 0;
vector<int>::iterator it;
for (int i = 0; i < 10; ++i){
    // it = v.begin(); it != v.end(); ++it
    //v.insert(it, tall); 
    // kræsjer fordi vi setter inn mens vi itereter gjennom, dette endrer strukturen og iteratoren blir "ugyldig"
    // løsning
    it = v.insert(it+1, i);
}

for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter){
    std::cout << *iter << std::endl;
}