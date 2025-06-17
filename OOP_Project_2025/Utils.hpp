#pragma once
#include <string>
#include <vector>

void splitLineInWords(const std::string& line, std::vector<std::string>& words,char symbol);

bool canStringToNumericType(const std::string& str);
bool canStringToDate(const std::string& str);

bool isLeapYear(int year);
