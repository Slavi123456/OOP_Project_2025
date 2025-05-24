#pragma once
#include "Data.hpp"

class Integer: public Data{
public:
	Integer();
	Integer(int integer);
	//Serialization & deserialization
	int getValue() const;
	std::string getData() const override;
	void setData(int data);
	void print() override;
	
	Data* clone() const override;
	Data* emptyClone() const;

	const char* getName() const override;
private:
	int integer;
	//could have restriction said in the cons
};

