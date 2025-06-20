#include "Date.hpp"
#include <iostream>
#include "String.hpp"
#include "Integer.hpp"
#include "Utils.hpp" //only for Leap Year its needed because Integer also use it
#include "Decimal.hpp"

static void dateToInteger(const Date* date, int& result) {
    result = 0;
    const int dayInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    result += date->getDay();

    int month = date->getMonth();
    //adding the month
    for (size_t i = 0; i < month - 1; i++)
    {
        if (i == 1 && isLeapYear(date->getYear())) //february leap year
        {
            result += 29;
            continue;
        }
        result += dayInMonth[i];
    }

    int year = date->getYear();
    //adding the year
    for (int y = 1900; y < year; ++y) {
        result += isLeapYear(y) ? 366 : 365;
    }

}

////////////--Constructors--////////////

Date::Date(int date, int month, int year):
    date(date), month(month), year(year), Data()
{
    if (!isDateValid()
        || !isMonthValid()
        || !isYearValid())
    {
        throw "Invalid date";
    }
    this->isNull = false;
}

////////////--Functions--////////////

bool Date::isDateValid()
{
    return this->date >= STARTING_DATE && this->date <= MAX_DATE;
}

bool Date::isMonthValid()
{
    return this->month >= STARTING_MONTH && this->month <= MAX_MONTH;
}

bool Date::isYearValid()
{
    return this->year >= STARTING_YEAR;
}

////////////--From Data--////////////
void Date::print(std::ostream& os) const
{
    if (isNull) {
        os << "NULL";
        return;
    }

    os << this->date << " " << this->month << " " << this->year;
}

void Date::read(std::istream& is)
{
    is >> this->date >> this->month >>this->year;
}

const char* Date::getName() const
{
    return "Date";
}

//std::string Date::getData() const
//{
//    return std::string();
//}

Date* Date::clone() const
{
    return new Date(*this);
}
Date* Date::emptyClone() const
{
    return new Date();
}

bool Date::operator==(const Data* other) const
{
    if (this->isNull && other->isDataNull()) return true;
    else if (this->isNull) return false;
    else if (other->isDataNull()) return false;

    const Date* otherDate = dynamic_cast<const Date*>(other); //can it be avoided?
    if (!otherDate) return false;

    return this->date == otherDate->date && this->month == otherDate->month && this->year == otherDate->year;
    //cannot be done by only this 
    //because class Data doesn't have getValue, because it doesn't know what type to return
}
bool Date::operator!=(const Data* other) const
{
    return !(this == other);
}


Data* Date::converTo(const char* wantedType) const
{
    if (strcmp(wantedType, "Date") == 0)
    {
        return nullptr; //i am not sure if this is correct way to do it
    }

    if (strcmp(wantedType, "String") == 0)
    {
        if (isNull)
        {
            return new MyString;
        }
        std::string res = std::to_string(this->date) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year);
        return new MyString(res);
    }
    else if (strcmp(wantedType, "Decimal") == 0)
    {
        //there is no convertion between Date and Decimal
        /*if (isNull)
        {
            return new Decimal;
        }*/
        return new Decimal;

        //throw "Date to Decimal is not supported";
    }
    else if (strcmp(wantedType, "Integer") == 0)
    {
        if (isNull)
        {
            return new Integer;
        }
        int integer = 0;
        dateToInteger(this, integer);
        return new Integer(integer);
    }
    

    throw "Unsupported convertion";
}

int Date::getDay() const
{
    return this->date;
}
int Date::getMonth() const
{
    return this->month;
}
int Date::getYear() const
{
    return this->year;
}

