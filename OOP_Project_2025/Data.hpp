#pragma once 

#include <string>

//abstract class for all types for the database
//what is the logic behind it: because if they are in different
//classes they are more flexible and open to changes 
// as if they were in one type of data like
//temp<typename T> class Data{...T data;} this would work 
//if we wanted them to have the same functionality for every one
class Data {
private:

protected:
	bool isNull = true;
public:
	
	Data() = default;
	//Data(const Data& other) = default;
	//Data(Data&& other) = default;
	//Data& operator=(const Data& other) = default;
	//Data& operator=(Data&& other) = default;
	virtual ~Data() = default;

	bool isDataNull() const {
		return isNull;
	}

	/////////////////////////////////////////////////////
	//serialization and also printing to the cout stream
	virtual void print(std::ostream& os) const = 0;

	virtual const char* getName() const = 0; //for printing type name
	//virtual std::string getData() const = 0; //i need explanation on why did i choose this over making a template with type which is restricted

	//wouldn't better to make these static?? //no it cant be both virual and static 
	virtual Data* clone() const = 0; //virtual copy constructor //because of the hetero container in Table
	virtual Data* emptyClone() const = 0; //can it be done other way

	//cant i make Template T getValue () and use it in the == instead of dynamic_cast
	virtual bool operator==(const Data* other) const = 0; 
	virtual bool operator!=(const Data* other) const = 0;

	//also convert can be done by factory but its less scalable 
	virtual Data* converTo(const char* wantedType) const = 0;
	/////////////////////////////////////////////////////
protected:
	
};

