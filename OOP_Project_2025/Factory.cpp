#include "Factory.hpp"

#include "Decimal.hpp" //why not forward declared them ? which is better?
#include "Integer.hpp"
#include "String.hpp"
#include "Date.hpp"


Data* dataFactory(std::string& type, const std::vector<std::string>& value, int& startingInd)
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
		if (value[startingInd] == "NULL")
		{ 
			res = new Decimal(); //is there a better way to represent NULL value
		}
		else {
			double val = atoi(value[startingInd].c_str()); //how to check if i got valid double
			res = new Decimal(val); //wouldn't it be better to have constructor with string and from there throw
		}
	}
	else if (type == "Integer")
	{
		if (value[startingInd] == "NULL")
		{
			res = new Integer();
		}
		else
		{
			int val = atoi(value[startingInd].c_str()); //how to check if i got valid int
			res = new Integer(val); //wouldn't it be better to have constructor with string and from there throw
		}
	}
	else if (type == "String")
	{
		if (value[startingInd] == "NULL")
		{
			res = new MyString();
		}
		else
		{
			res = new MyString(value[startingInd]); //wouldn't it be better to have constructor with string and from there throw
		}
	}

	else if (type == "Date")
	{
		if (value[startingInd] == "NULL")
		{
			res = new Date();
		}
		else
		{
			int date = atoi(value[startingInd].c_str()); 
			startingInd++;
			int month = atoi(value[startingInd].c_str()); 
			startingInd++;
			int year = atoi(value[startingInd].c_str()); 
			res = new Date(date, month, year); //wouldn't it be better to have constructor with string and from there throw //no bc of desirializing
		}
	}

	else
	{
		throw "unkown type";
	}
	return res;

}

