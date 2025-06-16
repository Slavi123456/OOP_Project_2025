#include "Decimal.hpp"
#include <fstream>

////////////--Constructors--////////////
Decimal::Decimal()
{
}

Decimal::Decimal(double decimal): Data()
{
    setData(decimal);
}

////////////--Functions--////////////
double Decimal::getValue() const
{
    return decimal;
}
void Decimal::setData(double data)
{
    //any condition on the data // round?
    this->decimal = data;
    this->isNull = false;
}

////////////--From Data--////////////
void Decimal::print(std::ostream& os) const
{
    if (isNull) {
        os << "NULL";
        return;
    }
    os << this->decimal;
}

const char* Decimal::getName() const 
{ 
    return "Decimal";
}

//std::string Decimal::getData() const
//{
//    if (isNull) {
//        return std::string("NULL");
//    }
//    return std::to_string(decimal);
//}

Decimal* Decimal::clone() const
{
    return new Decimal(*this);
}

Decimal* Decimal::emptyClone() const
{
    return new Decimal();
}

bool Decimal::operator==(const Data* other) const
{
    if (this->isNull && other->isDataNull()) return true; //this to be in the Data class
    else if (this->isNull) return false;
    else if (other->isDataNull()) return false;

    const Decimal* otherDece = dynamic_cast<const Decimal*>(other);
    if (!otherDece)  return false;

    return otherDece->decimal == this->decimal;
}

bool Decimal::operator!=(const Data* other) const
{
    return !(this == other);
}
////////////----////////////
