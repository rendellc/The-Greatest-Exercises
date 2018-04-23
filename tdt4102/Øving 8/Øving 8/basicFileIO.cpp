#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include "basicFileIO.h"
using namespace std;

void writeLineToFile(string filename)
{
	const string EXIT_WORD = "QUIT";

	ofstream file;
	file.open(filename);
	
	string input = "";
	do {
		file << input;
		cin >> input;
		input += "\n";
	} while (input != EXIT_WORD + "\n");

	file.close();
}

void readFromFileToFile(string oldFilename, string newFilename)
{
	ifstream inputFile;
	inputFile.open(oldFilename);

	if (inputFile.fail()) {
		// cancel function and return void
		inputFile.close();
		return;
	}

	ofstream outputFile;
	outputFile.open(newFilename);
	
	if (outputFile.fail()) {
		inputFile.close();
		outputFile.close();
		return;
	}
	
	int lineCounter = 1;
	string input;
	while (getline(inputFile, input)) {
		outputFile << lineCounter << " - " << input << endl;
		lineCounter++;
	}

	// close both files
	outputFile.close();
	inputFile.close();
}

void countCharactersInFile(string filename)
{
	ifstream infile(filename);

	if (infile.fail()) {
		infile.close(); // er dette egentlig kanskje nødvendig?
		return;
	}

	// generate map
	map<char, int> count;
	char input = 0;
	unsigned int totalCount = 0;
	while (infile.get(input)) {
		input = tolower(input);
		// count if characther is between 'a' and 'z'
		if (input >= 'a' && input <= 'z') {
			count[input]++;
			totalCount++;
		}
	}

	infile.close();

	// format and display results
	cout << "Character statistics for " << filename << endl;
	cout << "Total number of characters: " << totalCount << endl;
	int CHARS_PER_LINE = 4;
	for (char firstChar = 'a'; firstChar <= 'z'; firstChar += CHARS_PER_LINE - 1) {
		char lastCharOfLine = min(firstChar + CHARS_PER_LINE - 1, (int)'z');
		for (char ch = firstChar; ch <= lastCharOfLine; ch++) {
			cout << ch << ": " << setw(6) << count[ch] << '\t';
		}
		cout << endl;
	}
}


void wordStatistics(string filename)
{
	ifstream file(filename);
	if (file.fail()) {
		file.close();
		return;
	}

	map<string, int> wordMap;
	string line;
	int lineCounter = 0;
	while (getline(file, line)) {
		lineCounter++;

		// extract word from line
		stringstream ss(line);
		string word;
		while (ss >> word) {

			// remove non-normal characteers
			string newWord("");
			for (unsigned int i = 0; i < word.length(); i++) {
				// make lowercase
				char ch = tolower(word[i]);

				// check if character is between a and z
				if ('a' <= ch && ch <= 'z') {
					newWord.push_back(ch);
				}
			}

			// add to map
			wordMap[newWord]++;
		}
	}

	file.close();

	// print statistics
	cout << "Statistics for " << filename << endl;
	cout << "Longest word: " << longestWord(wordMap) << endl;
	cout << "Number of Words: " << wordMap.size() << endl;
	cout << "Number of lines: " << lineCounter << endl;
	cout << "Average word length: " << avgWordLength(wordMap) << endl;
	printMap(wordMap);
}

string mostFrequentWord(map<string, int> wordMap)
{
	string mostFrequent;
	int max = 0;
	for (auto& iter : wordMap) {
		if (iter.second > max) {
			mostFrequent = iter.first;
			max = iter.second;
		}
	}
	return mostFrequent;
}

string longestWord(map<string, int> wordMap) 
{
	string longestWord;
	for (auto& iter : wordMap) {
		if (iter.first.length() > longestWord.length()) {
			longestWord = iter.first;
		}
	}
	return longestWord;
}

int avgWordLength(std::map<std::string, int> wordMap)
{
	int totalLength = 0;
	for (auto& iter : wordMap) {
		totalLength += iter.first.length();
	}

	return totalLength/wordMap.size();
}

void printMap(map<string, int> map)
{
	for (auto& iter : map) {
		cout << iter.first << ": " << iter.second << endl;
	}
}
