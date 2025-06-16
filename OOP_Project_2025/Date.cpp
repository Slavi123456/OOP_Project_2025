#include "Date.hpp"
#include <iostream>

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
    return this->date > 0 && this->date < 32;
}

bool Date::isMonthValid()
{
    return this->month > 0 && this->month < 13;
}

bool Date::isYearValid()
{
    return this->year >= 1900;
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

