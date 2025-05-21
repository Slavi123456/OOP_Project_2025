#pragma once 
#include "Data.hpp"

class Decimal: public Data {
public:
	Decimal(double decimal); //explicit??
	//Serialization & deserialization
	double getData() const;
	void setData(double data);
	void print() override; //needs to fill zeros behind the comma

	const char * getName() const override;
private:
	double decimal; //do i have to have float
};