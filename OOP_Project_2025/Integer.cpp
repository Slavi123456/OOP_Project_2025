#include "Integer.hpp"
#include <iostream> //is it better to be declarated here or not

Integer::Integer(int integer): Data()
{
    setData(integer);
}

int Integer::getData() const
{
    return integer;
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

const char* Integer::getName() const
{
    return "Integer";
}
