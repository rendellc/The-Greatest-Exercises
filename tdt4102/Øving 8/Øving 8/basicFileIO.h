#pragma once
#include <string>
#include <map>

void writeLineToFile(std::string filename);

void readFromFileToFile(std::string oldFilename, std::string newFilename);

void countCharactersInFile(std::string filename);

void wordStatistics(std::string filename);

// *** helper functions ***
std::string mostFrequentWord(std::map<std::string, int> wordMap);
std::string longestWord(std::map<std::string, int> wordMap);
int avgWordLength(std::map<std::string, int> wordMap);
void printMap(std::map<std::string, int> map);