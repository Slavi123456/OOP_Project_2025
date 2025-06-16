#pragma once
#include <string>
#include <iostream>
#include "Data.hpp"
#include <vector>

class MyString: public Data {
private:
	std::string str;
	static const std::vector<char> SPECIAL_SYMBOLS;
public:	
	MyString() = default;
	MyString(const std::string& str);
	MyString(const char* str);
	////////////--From Data--////////////
	void print(std::ostream& os) const override;

	const char* getName() const override;
	//std::string getData() const override;

	MyString* clone() const override;
	MyString* emptyClone() const override;

	bool operator==(const Data* other) const override;
	bool operator!=(const Data* other) const override;
	////////////////////////////////////
private:
	void formatString(std::string& str);
	std::string deformatString(const std::string& str) const;
};