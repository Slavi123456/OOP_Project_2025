#pragma once 
#include "Data.hpp"

class Decimal: public Data {
public:
	Decimal();
	Decimal(double decimal); //explicit??
	//Serialization & deserialization
	double getValue() const;
	std::string getData() const override;

	void setData(double data);
	void print() override; //needs to fill zeros behind the comma

	const char * getName() const override;
	
	Data* clone() const override;
	Data* emptyClone() const override;
private:
	double decimal; //do i have to have float
};