#pragma once
#include <string>
#include <vector>

void splitLineInWords(const std::string& line, std::vector<std::string>& words,char symbol);

bool canStringToNumericType(const std::string& str);
bool canStringToDate(const std::string& str);

bool isLeapYear(int year);


template<typename T>
static void swap(T& lhs, T& rhs);

template<typename T>
void swap(T& lhs, T& rhs)
{
	T helper = lhs;
	lhs = rhs;
	rhs = helper;
}
