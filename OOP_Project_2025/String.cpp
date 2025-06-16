#include "String.hpp"

const std::vector<char> MyString::SPECIAL_SYMBOLS{ '\\', '\"' };
////////////--Constructors--////////////
MyString::MyString(const std::string& str): 
	Data(), str("")
{
	try
	{
		std::string copy = str; //can throw on allocation
		formatString(copy);
		this->str = std::move(copy);
	}
	catch (...)
	{
		throw "Problem with the string";
	}
	this->isNull = false;
}

MyString::MyString(const char* str):
	Data(), str("")
{
	try
	{
		std::string copy = str; //can throw on allocation
		formatString(copy);
		this->str = std::move(copy);
	}
	catch (...)
	{
		throw "Problem with the string";
	}
	this->isNull = false;
}

////////////--Functions--////////////

void MyString::formatString(std::string& str)
{
	std::vector<int> indSpecialSymbols;
	int sizeStr = str.size();
	int countSpecial = SPECIAL_SYMBOLS.size();

	//find ind of all specials 
	for (size_t i = 0; i < sizeStr; i++)
	{

		for (size_t y = 0; y < countSpecial; y++)
		{
			if (str[i] == SPECIAL_SYMBOLS[y])
			{
				indSpecialSymbols.push_back(i);
			}
		}
	}

	//add the needed symbol
	int countInd = indSpecialSymbols.size();
	for (int i = countInd - 1; i >= 0; i--)//its reversed because the indexes will be changed from the insert //also int because of size_t its unsigned
	{
		str.insert(indSpecialSymbols[i], "\\");
	}

	//surround with quotations
	sizeStr = str.size();
	str.insert(0, "\"");
	str.push_back('\"');
}

//For this i used ChatGPT's help
std::string MyString::deformatString(const std::string& input) const
{
	std::string result;
	
	size_t start = 0;
	size_t end = input.length();

	if (input.length() >= 2 && input.front() == '"' && input.back() == '"') {
		start = 1;
		end = input.length() - 1;
	}

	for (size_t i = start; i < end; ++i) {
		if (input[i] == '\\' && i + 1 < end) {
			char next = input[i + 1];
			if (next == '\\') {
				result += '\\'; 
				++i;
			}
			else if (next == '"') {
				result += '"';   
				++i;
			}
			else {
				result += next;  // Unknown escape, still eat the backslash
				++i;
			}
		}
		else {
			result += input[i];
		}
	}
	
	return result;
}

////////////--From Data--////////////

void MyString::print(std::ostream& os) const
{
	if (isNull) {
		os << "NULL";
		return;
	}
	std::string subStr;
	try
	{
		subStr = deformatString(this->str);
	}
	catch (...)
	{
		throw "problem with the subString function in MyString::print";
	}
	os << subStr;
}

const char* MyString::getName() const
{
	return "String";
}

MyString* MyString::clone() const
{
	return new MyString(*this);
}
MyString* MyString::emptyClone() const
{
	return new MyString();
}

bool MyString::operator==(const Data* other) const
{
	if (this->isNull && other->isDataNull()) return true;
	else if (this->isNull) return false;
	else if (other->isDataNull()) return false;

	const MyString* otherString = dynamic_cast<const MyString*>(other); //can it be avoided?
	if (!otherString) return false;
	return this->str == otherString->str;
}
bool MyString::operator!=(const Data* other) const
{
	return !(this == other);;
}

