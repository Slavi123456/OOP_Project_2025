
#include <iostream>
#include "data.hpp"
#include "integer.hpp"
#include "decimal.hpp"
#include "table.hpp"
#include <fstream>
#include <string>
#include "date.hpp"
#include "String.hpp"

void testInteger() {
	Integer inte(4);
	std::cout << inte.getName() << " ";
	inte.print(std::cout);
	std::cout << std::endl;
}
void testDecimal() {
	Decimal dece(6.01);
	std::cout << dece.getName() << " ";
	dece.print(std::cout);
	std::cout << std::endl;

}
void testDataArr() {
	Decimal dece(6.01);
	Integer inte(4);

	Data** arr = new Data * [2];
	arr[0] = &dece;
	arr[1] = &inte;

	for (size_t i = 0; i < 2; i++)
	{
		std::cout << arr[i]->getName() << " ";
		arr[i]->print(std::cout);
		std::cout << std::endl;
		//delete arr[i]; NO CANT DELETE variables on the stack
	}
	delete[]arr;

}
void testDataDate() {
	Date date(1, 2, 3000);
	std::cout << date.getName() << " ";
	date.print(std::cout);
	std::cout << std::endl;

	Date* emptyDate = date.emptyClone();
	std::cout << emptyDate->getName() << " ";
	emptyDate->print(std::cout);
	std::cout << std::endl;

	Date* date2 = date.clone();

	std::cout << std::boolalpha << (date == date2) << std::endl;
	delete emptyDate;
	delete date2;
}
void testDataString() {
	MyString str("1\\23\"4");
	std::cout << str.getName() << " ";
	str.print(std::cout);
	std::cout << std::endl;

	MyString* empStr = str.emptyClone();
	std::cout << empStr->getName() << " ";
	empStr->print(std::cout);
	std::cout << std::endl;

	MyString* str2 = str.clone();

	std::cout << std::boolalpha << (str == str2) << std::endl;
	delete empStr;
	delete str2;
}

void testTableAdd_Print() {
	Table tab;

	Decimal dec(55.89);
	std::vector<Data*> vec;
	vec.push_back(&dec);
	
	tab.addLine(vec);
	tab.addLine(vec);
	tab.print();
}
void testTableAddColumn() {
	Table tab;
	tab.print();

	Decimal dec(55.89);
	
	std::vector<Data*> vec;
	vec.push_back(&dec);
	
	tab.addColumn(&dec);
	tab.print(); //there is a problem if it's empty

	tab.addLine(vec);
	tab.addLine(vec);
	tab.print();

	Integer inte(4);
	tab.addColumn(&inte);

	tab.print();
}
void testTableRPN_Print() {
	Table tab;
	//tab.addData(Decimal(55.89), 0);
	//tab.addData(Integer(4), 1);
	//tab.addData(Integer(), 1);
	Decimal dec(55.89);
	Integer inte;
	Integer inte2(4);

	std::vector<Data*> vec;
	vec.push_back(&dec);
	vec.push_back(&inte);
	vec.push_back(&inte2);

	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);

	tab.print(2);
}
void testTablePrint_Types() {
	Table tab;
	std::cout << "Table types: ";
	tab.printTypes(std::cout);

	Decimal dec(55.89);
	Integer inte;
	Integer inte2(4);

	std::vector<Data*> vec;
	vec.push_back(&dec);
	vec.push_back(&inte);
	vec.push_back(&inte2);

	tab.addLine(vec);
	
	tab.print();

	std::cout << "Table types: ";
	tab.printTypes(std::cout);
}
void testTableSelect() {
	Table tab;

	Decimal dec(55.89);
	Decimal dec1(432.5);
	Decimal dec2(4654.5);
	Integer inte1;
	Integer inte2 (1);
	Integer inte3 (2);
	Integer inte4(4);
	Integer inte5(5);

	std::vector<Data*> vec = { &dec, &inte1, &inte2 };
	std::vector<Data*> vec2 = { &dec2, &inte4, &inte5 };
	std::vector<Data*> vec3 = { &dec1, &inte3, &inte2 };
	
	tab.addLine(vec);
	tab.addLine(vec2);
	tab.addLine(vec3);

	tab.print();
	std::cout <<std::endl << "Selection by third column for Integer(1)" <<std::endl;
	tab.select(2, &inte2);

	std::cout << std::endl << "Selection by second column for Null" << std::endl;
	tab.select(1, &inte1);

	std::cout << std::endl << "Selection by third column for Integer(2)" << std::endl;
	tab.select(2, &inte3);
}
void testTableExport(const std::string& fileName) {
	Table tab;

	Decimal dec(55.89);
	Integer inte;
	Date date(1,2,1900);
	MyString str("13\"2\\1"); 
	std::cout << std::endl;

	std::vector<Data*> vec = { &dec, &inte, &date, &str};
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);

	std::ofstream os(fileName);
	if (!os) {
		std::cerr << "Could not open file.\n";
		return;
	}
	tab.writeToStream(os);
}
void testTableDesirialization(const std::string& fileName){
	Table tab;
	
	std::ifstream is(fileName);
	if (!is) {
		std::cerr << "Could not open file.\n";
		return;
	}

	tab.readFromStream(is);
	tab.print();
}

void testTableSerAndDes(const std::string& fileName) {
	testTableExport(fileName);
	testTableDesirialization(fileName);
}

void formatingString(std::string& str)
{

	std::vector<char> SPECIAL_SYMBOLS{ '\\', '"' };
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
	str.push_back('"');
}
void testFormatingStr() {
	std::string s("123\"4");
	s.insert(2, "\\");
	std::cout << s << std::endl;
	formatingString(s);
	std::cout << s;
}

void testForAllTypes() {
	Table tab;
	tab.print();
	Decimal dec(55.89);
	Date date(1, 2, 3000);
	MyString str("123\"4");

	std::vector<Data*> vec;
	vec.push_back(&dec);
	vec.push_back(&date);

	vec.push_back(&str);
	tab.addLine(vec);

	tab.print();


	Integer inte(4); //this 4 can be like default value for every cell
	tab.addColumn(&inte); //in add columns adds only Integer and not the value 

	MyString str2; //if its str2() its interpreted like function declaration
	tab.addColumn(&str2); //in add columns adds only Integer and not the value 

	tab.print();

}
void testTableUpdateStringToDate() {
	Table tab;
	tab.print();
	Decimal dec(55.89);
	Integer inte(3);
	Integer inte1(5);
	Date date(1, 2, 3000);
	MyString str("12/3/1901");

	
	std::vector<Data*> vec{ &inte,&dec,&str };
	std::vector<Data*> vec1{ &inte1,&dec,&str };

	tab.addLine(vec);
	tab.addLine(vec1);
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec1);
	tab.addLine(vec1);

	tab.print();

	std::cout << std::endl;
	std::cout << "Will change " << str.getName() << " to " << date.getName() << ": ";
	date.print(std::cout);
	std::cout << std::endl;
	std::cout << "Only by rows which have " << inte.getName() << ": ";
	inte.print(std::cout);
	std::cout << std::endl;
	std::cout << std::endl;
	
	tab.update(0, &inte, 2, &date);
	tab.print();
}

void testTableUpdateDecimalToDate() {

	Table tab;
	tab.print();
	Decimal dec(55.89);
	Integer inte(3);
	Integer inte1(5);
	Date date(1, 2, 3000);
	MyString str("12/3/1901");


	std::vector<Data*> vec{ &inte,&dec,&str };
	std::vector<Data*> vec1{ &inte1,&dec,&str };

	tab.addLine(vec);
	tab.addLine(vec1);
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec1);
	tab.addLine(vec1);

	tab.print();

	std::cout << std::endl;
	std::cout << "Will change " << dec.getName() << " to " << date.getName() << ": ";
	date.print(std::cout);
	std::cout << std::endl;
	std::cout << "Only by rows which have " << inte.getName() << ": ";
	inte.print(std::cout);
	std::cout << std::endl;
	std::cout << std::endl;

	tab.update(0, &inte, 1, &date);
	tab.print();
}
void testStringConvertionToNumeric() {
	MyString str("123\"4");
	MyString str1("1234");

	Data* intStr = nullptr;
	Data* intStr1 = nullptr;
	try
	{
		//success //it works with either Integer or Decimal
		intStr1 = str1.converTo("Integer");
		if (intStr1) intStr1->print(std::cout);
		std::cout << std::endl;

		//fail
		intStr = str.converTo("Integer");
		if (intStr) intStr->print(std::cout);
	}
	catch (...)
	{
		delete intStr;
		delete intStr1;
		std::cout << "Something happened";
	}
}
void testStringToDate() {
	MyString str("12/3/1901");
	MyString str1("12/3/dsa");

	Data* dateStr = nullptr;
	Data* dateStr1 = nullptr;
	try
	{
		//success 
		dateStr = str.converTo("Date");
		if (dateStr) dateStr->print(std::cout);
		std::cout << std::endl;

		//fail
		dateStr1 = str1.converTo("Date");
		if (dateStr1) dateStr1->print(std::cout);
	}
	catch (...)
	{
		delete dateStr;
		delete dateStr1;
		std::cout << "Something happened";
	}
}
void testIntToOthers() {
	Integer inte(4);
	Data* inteDate = nullptr;
	Data* inteStr = nullptr;
	Data* inteDecimal = nullptr;

	try
	{
		inteDate = inte.converTo("Date");
		inteStr = inte.converTo("String");
		inteDecimal = inte.converTo("Decimal");

		inteDate->print(std::cout);
		std::cout << std::endl;
		inteStr->print(std::cout);
		std::cout << std::endl;
		inteDecimal->print(std::cout);
		std::cout << std::endl;
	}
	catch (...)
	{
		delete inteDate;
		delete inteDecimal;
		delete inteStr;
		std::cout << "Something happened";
	}

	delete inteDate;
	delete inteDecimal;
	delete inteStr;
}
void testDecimalToOthers() {

	Decimal dece(4.8);
	Data* deceDate = nullptr;
	Data* deceStr = nullptr;
	Data* deceInteger = nullptr;

	try
	{
		//these should success
		deceStr = dece.converTo("String");
		std::cout << deceStr->getName() << " ";
		deceStr->print(std::cout);
		std::cout << std::endl;

		deceInteger = dece.converTo("Integer");
		std::cout << deceInteger->getName() << " ";
		deceInteger->print(std::cout);
		std::cout << std::endl;

		//this should fail
		deceDate = dece.converTo("Date");
		std::cout << deceDate->getName() << " ";
		deceDate->print(std::cout);
		std::cout << std::endl;
	}
	catch (...)
	{
		delete deceDate;
		delete deceInteger;
		delete deceStr;
		std::cout << "Something happened";
	}
}
void testDateToOthers() {
	Date date(26, 6, 2025);
	std::cout << date.getName() << " ";
	date.print(std::cout);
	std::cout << std::endl;

	Data* dateDecimal = nullptr;
	Data* dateString = nullptr;
	Data* dateInteger = nullptr;

	try
	{
		//these should success
		dateString = date.converTo("String");
		std::cout << dateString->getName() << " ";
		dateString->print(std::cout);
		std::cout << std::endl;

		dateInteger = date.converTo("Integer");
		std::cout << dateInteger->getName() << " ";
		dateInteger->print(std::cout);
		std::cout << std::endl;

		//this should fail
		dateDecimal = date.converTo("Decimal");
		std::cout << dateDecimal->getName() << " ";
		dateDecimal->print(std::cout);
		std::cout << std::endl;
	}
	catch (...)
	{
		delete dateDecimal;
		delete dateString;
		delete dateInteger;

		std::cout << "Something happened";
	}
}

int main()
{
	//testTableAdd_Print();
	//testTableRPN_Print();
	//testTableExport();
    //testTableSerAndDes("opit2.txt");
	
	
	//testTableUpdateStringToDate();

}

void reserveVecFunc() {
	std::vector<int> a;
	a.push_back(1);
	std::cout << a.size() << " " << a.capacity() << std::endl;

	a.reserve(8);
	std::cout << a.size() << " " << a.capacity();
	
}
