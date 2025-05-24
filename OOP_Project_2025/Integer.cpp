#include "Integer.hpp"
#include <iostream> //is it better to be declarated here or not

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

void Integer::print()
{
    if (isNull) {
        std::cout << " NULL " << std::endl; 
        return;
    }
    std::cout << this->integer << std::endl;
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
