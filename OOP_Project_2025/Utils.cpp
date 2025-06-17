#include "Utils.hpp"


static bool isNumber(char c)
{
	return c >= '0' && c <= '9';
}

/////////////////////////////////////////////////////////////////////

void splitLineInWords(const std::string& line, std::vector<std::string>& words, char symbol)
{
	if (line.empty())
	{
		throw "String of the line is empty";
	}

	std::string word;
	int sizeLine = line.size();
	for (size_t i = 0; i < sizeLine; i++) {
		char c = line[i];
		if (c == symbol) {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		}
		else {
			word += c;
		}
	}

	//checking for any left
	if (!word.empty()) {
		words.push_back(word);
	}
}

bool canStringToNumericType(const std::string& str)
{
	int sizeStr = str.size();
	for (size_t i = 0; i < sizeStr; i++)
	{
		if (!isNumber(str[i])) return false;
	}
	return true;
}
bool canStringToDate(const std::string& str) {

	int sizeStr = str.size();
	for (size_t i = 0; i < sizeStr; i++)
	{
		if (!isNumber(str[i]) && str[i] != '/') return false;
	}
	return true;
}

bool isLeapYear(int year)
{
	return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));	
}


