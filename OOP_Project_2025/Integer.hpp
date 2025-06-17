#pragma once
#include "Data.hpp"

class Integer: public Data{
private:
	void setData(int data);

	int integer;
	//could have restriction said in the constructors
public:
	Integer() = default;
	Integer(int integer);
	
	int getValue() const;

	////////////--From Data--////////////	
	//Serialization
	void print(std::ostream& os) const override;
	
	const char* getName() const override;
	//std::string getData() const override;

	Integer* clone() const override;
	Integer* emptyClone() const;

	bool operator==(const Data* other) const override;
	bool operator!=(const Data* other) const override;

	//have to implemented
	Data* converTo(const char* wantedType) const override;
	////////////////////////////////////
};

