#pragma once
#include "Data.hpp"

class Integer: public Data{
public:
	Integer();
	Integer(int integer);
	//Serialization & deserialization
	
	int getValue() const;
	std::string getData() const override;
	
	void print() override;
	
	Data* clone() const override;
	Data* emptyClone() const;

	const char* getName() const override;

	bool operator==(const Data* other) const override;
	bool operator!=(const Data* other) const override;

	void print(std::ostream& os) const override;
private:
	void setData(int data);

	int integer;
	//could have restriction said in the cons
};

