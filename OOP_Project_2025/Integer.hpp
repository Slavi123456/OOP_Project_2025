#pragma once
#include "Data.hpp"

class Integer: public Data{
public:
	Integer(int integer);
	//Serialization & deserialization
	int getData() const;
	void setData(int data);
	void print() override;
	
	
	const char* getName() const override;
private:
	int integer;
	//could have restriction said in the cons
};

