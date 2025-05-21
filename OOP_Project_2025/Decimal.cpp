#include "Decimal.hpp"
#include "iostream"

Decimal::Decimal(double decimal): Data()
{
    setData(decimal);
}

double Decimal::getData() const
{
    return decimal;
}

void Decimal::setData(double data) 
{
    //any condition on the data // round?
    this->decimal = data;
    this->isNull = false;
}

void Decimal::print()
{
    if (isNull) {
        std::cout << " NULL " << std::endl;
        return;
    }
    std::cout << this->decimal << std::endl;
}

const char* Decimal::getName() const 
{ 
    return "Decimal";
}
