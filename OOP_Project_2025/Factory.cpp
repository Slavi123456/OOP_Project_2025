#include "Factory.hpp"

#include "Decimal.hpp" //why not forward declared them ? which is better?
#include "Integer.hpp"
#include "String.hpp"
#include "Date.hpp"

#include "Utils.hpp"


/////////////////////////////////////////////////////////////////////
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

	if (type == "Decimal") {
		if (value[startingInd] == "NULL")
		{ 
			return new Decimal(); //is there a better way to represent NULL value
		}
		else {
			//double val = atoi(value[startingInd].c_str()); //how to check if i got valid double
			//res = new Decimal(val); //wouldn't it be better to have constructor with string and from there throw
			double res;
			try
			{
				res = atoi(value[startingInd].c_str());
			}
			catch (...)
			{
				throw "Atoi failed to transform String to integer";
			}
			return new Decimal(res);
		}
	}
	else if (type == "Integer")
	{
		if (value[startingInd] == "NULL")
		{
			return new Integer();
		}
		else
		{
			if (canStringToNumericType(value[startingInd])) //additional check 
			{
				int val;
				try
				{
					val = atoi(value[startingInd].c_str());
				}
				catch (...)
				{
					throw "Atoi failed to transform String to integer";
				}
				return new Integer(val);
			}
			else
			{
				throw "Could't transform String to integer";
			}
		}
	}
	else if (type == "String")
	{
		if (value[startingInd] == "NULL")
		{
			return new MyString();
		}
		else
		{
			return new MyString(value[startingInd]); //wouldn't it be better to have constructor with string and from there throw
		}
	}

	else if (type == "Date")
	{
		if (value[startingInd] == "NULL")
		{
			return new Date();
		}
		else
		{
			int date;
			int month;
			int year;
			try
			{
				date = atoi(value[startingInd].c_str());
				startingInd++;
				month = atoi(value[startingInd].c_str());
				startingInd++;
				year = atoi(value[startingInd].c_str());
			}
			catch (...)
			{
				throw "Atoi failed to transform String to integer";
			}
			//wouldn't it be better to have constructor with string and from there throw //no bc of desirializing // and i choosed that way
			return new Date(date, month, year);
		}		
	}
	
	throw "Unsupported type for factory";

}

Data* dataFactoryForEmpty(const std::string& type)
{
	if (type == "Integer") return new Integer;
	else if (type == "Decimal") return new Decimal;
	else if (type == "Date") return new Date;
	else if (type == "String") return new MyString;

	throw "Unsupported type";
}

