#pragma once 

#include <string>

//abstract class for all types for the database
//what is the logic behind it: because if they are in different
//classes they are more flexible and open to changes 
// as if they were in one type of data like
//temp<typename T> class Data{...T data;} this would work 
//if we wanted them to have the same functionality for every one
class Data {
public:
	//virtual serialization/ deserialization //no
	Data() = default;
	Data(const Data& other) = default;
	Data(Data&& other) = default;
	Data& operator=(const Data& other) = default;
	Data& operator=(Data&& other) = default;
	virtual ~Data() = default;

	//it can be made by taking a stream and be write()
	virtual void print() = 0;
	//with virtual void read(stream){}
	
	virtual const char* getName() const = 0; //for printing type name
	virtual std::string getData() const = 0; //i need explanation on why did i choose this over making a template with type which is restricted

	virtual Data* clone() const = 0; //virutal copy constructor
	virtual Data* emptyClone() const = 0; //can it be done other way //wont it be better to make them static 
protected:
	bool isNull = true;
private:
};