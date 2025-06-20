#include "Integer.hpp"
#include <fstream>
#include "String.hpp"
#include "Decimal.hpp"
#include "Date.hpp"
#include "Utils.hpp" //if its only for isLeapYear, is it worth?
#include "Factory.hpp"

//this is from 1/1/1900
static void integerToDate(int integer, int& date, int& month, int& year) {

	int maxDaysInYear = 365;
	while (true) {
		int daysInYear = isLeapYear(year) ? 366 : 365;
		if (integer < daysInYear) break;
		integer -= daysInYear;
		++year;
	}

	const int dayInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	for (size_t i = 0; i < 12; i++)
	{
		if (integer < dayInMonth[i]) break;
		integer -= dayInMonth[i];
		++month;
	}
	date = (integer == 0 ? 1 : integer);
}
////////////--Constructors--////////////

Integer::Integer(int integer): Data()
{
    setData(integer);
}

////////////--Functions--////////////
void Integer::setData(int data)
{
    //any checking of the data
    this->integer = data;
    this->isNull = false;
}
int Integer::getValue() const
{
    return integer;
}

////////////--From Data--////////////
void Integer::print(std::ostream& os) const
{
    if (isNull) {
        os << "NULL"; 
        return;
    }
    os << this->integer;
}

void Integer::read(std::istream& is)
{
	is >> this->integer;
}

const char* Integer::getName() const
{
    return "Integer";
}
//std::string Integer::getData() const
//{
//    if (isNull) {
//        return std::string("NULL");
//    }
//    return std::to_string(integer);
//}

Integer* Integer::clone() const
{ 
    return new Integer(*this);
}
Integer* Integer::emptyClone() const
{
    return new Integer();
}


bool Integer::operator==(const Data* other) const
{
    if (this->isNull && other->isDataNull()) return true; //this to be in the Data class
    else if (this->isNull) return false;
    else if (other->isDataNull()) return false;

    const Integer* otherInte = dynamic_cast<const Integer*>(other); //can it be avoided?
    if (!otherInte) return false;

    return otherInte->integer == this->integer; //cannot be done by only this 
    //because class Data doesn't have getValue, because it doesn't know what type to return
}
bool Integer::operator!=(const Data* other) const
{
    return !(this == other);
}

Data* Integer::converTo(const char* wantedType) const
{
	if (strcmp(wantedType, "Integer") == 0)
	{
		return nullptr; //i am not sure if this is correct way to do it
	}
	
	if (strcmp(wantedType, "String") == 0)
	{
		if (isNull)
		{
			return new MyString; 
		}
		return new MyString(std::to_string(this->integer));
	}
	else if (strcmp(wantedType, "Decimal") == 0)
	{
		if (isNull)
		{
			return new Decimal;
		}
		return new Decimal((double)this->integer);
	}
	else if (strcmp(wantedType, "Date") == 0) //format for string to be date: %/%/%
	{
		if (isNull)
		{
			return new Date;
		}
        int date = STARTING_DATE;
        int month = STARTING_MONTH;
        int year = STARTING_YEAR;
		integerToDate(this->integer, date, month, year);
		return new Date(date, month, year);
	}

	throw "Unsupported convertion";
}
////////////----////////////