#pragma once 
#include "Data.hpp"

class Decimal: public Data {
private:
	double decimal; //do i have to have float
public:
	Decimal();
	Decimal(double decimal); //explicit??
	
	double getValue() const;
	////////////--From Data--////////////

	void setData(double data);

	//serialization
	void print(std::ostream& os) const override; //needs to fill zeros behind the comma
	void read(std::istream& is) override;

	const char * getName() const override;
	//std::string getData() const override;

	Decimal* clone() const override;
	Decimal* emptyClone() const override;

	bool operator==(const Data* other) const override;
	bool operator!=(const Data* other) const override;

	Data* converTo(const char* wantedType) const override;
	////////////////////////////////////
};