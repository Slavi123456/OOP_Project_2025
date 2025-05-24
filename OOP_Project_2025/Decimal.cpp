#include "Decimal.hpp"
#include "iostream"

Decimal::Decimal()
{
}

Decimal::Decimal(double decimal): Data()
{
    setData(decimal);
}

double Decimal::getValue() const
{
    return decimal;
}

std::string Decimal::getData() const
{
    if (isNull) {
        return std::string("NULL");
    }
    return std::to_string(decimal);
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

Data* Decimal::clone() const
{
    return new Decimal(*this);
}

Data* Decimal::emptyClone() const
{
    return new Decimal();
}
