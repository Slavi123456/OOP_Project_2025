#pragma once 
#include "Data.hpp"

class Date: public Data{
private:
	//it could be better if its used int8, int8, int16 for less memory
	//no need of unsigned becuase i will check them for being in interval either way
	//or just one number int which will be the count of days from 01/01/1900 //but there will be calculations which may be slower
	int date; 
	int month;
	int year;
public:
	Date() = default; //will it be better to set them some values ?? like -1 
	Date(int date, int month, int year); //have to have checks
	//constructor Date(string date); ... 

	////////////--From Data--////////////
	void print(std::ostream& os) const override;

	const char* getName() const override; 
	//std::string getData() const override;

	Date* clone() const override;
	Date* emptyClone() const override;

	bool operator==(const Data* other) const override;
	bool operator!=(const Data* other) const override;
	////////////////////////////////////
private: 
	bool isDateValid();
	bool isMonthValid();
	bool isYearValid();
};