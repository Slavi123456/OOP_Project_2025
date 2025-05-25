#include "Integer.hpp"
#include <fstream>

Integer::Integer()
{
}

Integer::Integer(int integer): Data()
{
    setData(integer);
}

int Integer::getValue() const
{
    return integer;
}

std::string Integer::getData() const
{
    if (isNull) {
        return std::string("NULL");
    }
    return std::to_string(integer);
}

void Integer::setData(int data) 
{
    //any checking of the data
    this->integer = data;
    this->isNull = false;
}

void Integer::print(std::ostream& os) const
{
    if (isNull) {
        os << "NULL"; 
        return;
    }
    os << this->integer;
}

Data* Integer::clone() const
{ 
    return new Integer(*this);
}

Data* Integer::emptyClone() const
{
    return new Integer();
}

const char* Integer::getName() const
{
    return "Integer";
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
