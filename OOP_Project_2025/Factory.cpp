#include "Factory.hpp"

#include "Decimal.hpp" //why not forward declared them ? which is better?
#include "Integer.hpp"

Data* dataFactory(std::string& type, std::string& value)
{
	if (type.empty())
	{
		throw "type string is empty";
	}
	if (value.empty())
	{
		throw "value string is empty";
	}
	Data* res = nullptr;
	if (type == "Decimal") {
		if (value == "NULL") 
		{ 
			res = new Decimal(); //is there a better way to represent NULL value
		}
		else {
			double val = atoi(value.c_str()); //how to check if i got valid double
			res = new Decimal(val); //wouldn't it be better to have constructor with string and from there throw
		}
	}
	else if (type == "Integer")
	{
		if (value == "NULL")
		{
			res = new Integer();
		}
		else
		{
			int val = atoi(value.c_str()); //how to check if i got valid int
			res = new Integer(val); //wouldn't it be better to have constructor with string and from there throw
		}
	}
	else
	{
		throw "unkown type";
	}
	return res;

}