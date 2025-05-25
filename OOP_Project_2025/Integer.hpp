#pragma once
#include "Data.hpp"

class Integer: public Data{
public:
	Integer();
	Integer(int integer);
	
	int getValue() const;
	std::string getData() const override;
	
	//Serialization
	void print(std::ostream& os) const override;
	
	Data* clone() const override;
	Data* emptyClone() const;

	const char* getName() const override;

	bool operator==(const Data* other) const override;
	bool operator!=(const Data* other) const override;

private:
	void setData(int data);

	int integer;
	//could have restriction said in the constructors
};

