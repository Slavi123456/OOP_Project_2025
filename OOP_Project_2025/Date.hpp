#pragma once 
#include "Data.hpp"


static constexpr int STARTING_DATE = 1;
static constexpr int STARTING_MONTH = 1;
static constexpr int STARTING_YEAR = 1900;

static constexpr int MAX_DATE = 31;
static constexpr int MAX_MONTH = 12;

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
	void read(std::istream& is) override;

	const char* getName() const override; 
	//std::string getData() const override;

	Date* clone() const override;
	Date* emptyClone() const override;

	bool operator==(const Data* other) const override;
	bool operator!=(const Data* other) const override;

	//have to be implemented
	Data* converTo(const char* wantedType) const override;
	////////////////////////////////////

	int getDay() const;
	int getMonth() const;
	int getYear() const;
private: 
	bool isDateValid();
	bool isMonthValid();
	bool isYearValid();
};