#include <iostream>
#include "data.hpp"
#include "integer.hpp"
#include "decimal.hpp"
#include "table.hpp"
#include <fstream>
#include <string>
#include "date.hpp"
#include "String.hpp"
#include "DataBase.hpp"

///////////===testTypes===////////////
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

void testForAllTypes() {
	Table tab(std::string("tab"));
	tab.print();

	Decimal dec(55.89);
	Date date(1, 2, 3000);
	MyString str("123\"4");

	std::vector<Data*> vec{ &dec, &date, &str };
	tab.addLine(vec);

	tab.print();


	Integer inte(4); //this 4 can be like default value for every cell
	tab.addColumn(&inte); //in add columns adds only Integer and not the value 

	MyString str2; //if its str2() its interpreted like function declaration
	tab.addColumn(&str2); //in add columns adds only Integer and not the value 

	tab.print();

}
///////////===Types convertion to one another===////////////
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

///////////===Test table's constructors===////////////
void testTableCopyConstructor() {
	//testing Table copyContructor
	Table tab(std::string("tab"));

	Decimal dec(55.89);
	Date date(1, 2, 3000);
	MyString str("123\"4");

	std::vector<Data*> vec{ &dec, &date, &str }; //this works only because its a test

	tab.addLine(vec);

	Table tab1(tab);

	std::cout << "Tab: " << std::endl;
	tab.print();

	std::cout << "Tab1: " << std::endl;
	tab1.print();

	std::cout << "Tab after update: " << std::endl;
	tab.update(0, &dec, 1, &str);
	tab.print();
	//tab.update(0, &dec, 1, &date); ??

	std::cout << "Tab1: " << std::endl;
	tab1.print();

}

///////////===Test table's functionality===////////////
void testTableAdd_Print() {
	Table tab(std::string("tab"));

	Decimal dec(55.89);
	std::vector<Data*> vec;
	vec.push_back(&dec);
	
	tab.addLine(vec);
	tab.addLine(vec);
	tab.print();
}
void testTableAddColumn() {
	Table tab(std::string("tab"));
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
	Table tab(std::string("tab"));
	//tab.addData(Decimal(55.89), 0);
	//tab.addData(Integer(4), 1);
	//tab.addData(Integer(), 1);
	Decimal dec(55.89);
	Integer inte;
	Integer inte2(4);
	Integer inte3(5);
	Integer inte4(6);
	Integer inte5(7);

	std::vector<Data*> vec;
	vec.push_back(&dec);
	vec.push_back(&inte);
	vec.push_back(&inte2);

	tab.addLine(vec);
	vec[2] = &inte2;
	tab.addLine(vec);
	vec[2] = &inte3;
	tab.addLine(vec);
	vec[2] = &inte4;
	tab.addLine(vec);
	vec[2] = &inte5;
	tab.addLine(vec);

	tab.print();
	std::cout << "Now RPN print: " << std::endl;
	tab.print(2);
}
void testTablePrint_Types() {
	Table tab(std::string("tab"));
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
	Table tab(std::string("tab"));

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
	Table tab(std::string("tab"));

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
	Table tab(std::string("tab"));
	
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

void testTableUpdateStringToDate() {
	Table tab(std::string("tab"));
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

	Table tab(std::string("tab"));
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
void testTableModify() {
	Table tab(std::string("tab"));
	tab.print();

	Decimal dec(55.89);
	Date date(1, 2, 3000);
	MyString str("1234");

	std::vector<Data*> vec{ &dec, &date, &str };
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);

	tab.print();

	std::cout << std::endl << "Now this is the modified version of the table where String -> Int" << std::endl << std::endl;

	std::string inte("Integer");
	tab.modify(2, inte);
	tab.print();

	std::cout << std::endl << "Now this is the modified version of the table where Date -> Decimal" << std::endl << std::endl;

	std::string dece("Decimal");
	tab.modify(1, dece);
	tab.print();

	std::cout << std::endl << "Now this is the modified version of the table where Integer -> String" << std::endl << std::endl;

	std::string strName("String");
	tab.modify(2, strName);
	tab.print();
}

void testTableDelete() {
	Table tab(std::string("tab"));
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

	int wantedColumn = 0;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Will delete rows which have " << inte.getName() << ": ";
	inte.print(std::cout);
	std::cout << " on column " << wantedColumn << std::endl;
	std::cout << std::endl;

	tab.deleteSelectedRows(wantedColumn, &inte);
	tab.print();

	wantedColumn = 0;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Will delete rows which have " << inte1.getName() << ": ";
	inte1.print(std::cout);
	std::cout << " on column " << wantedColumn << std::endl;
	std::cout << std::endl;

	tab.deleteSelectedRows(wantedColumn, &inte1);
	tab.print();

}
///////////===String data formating function===////////////
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

///////////////====testing the delete function of Table====///////////////
void testDeleteSelectedRows(const std::vector<int>& indexSelectedRows, std::vector<std::vector<Data*>>& matrix, int wantedRow, int wantedColumn)
{
	std::vector<std::vector<Data*>> backupRows; //that will initialize with nullptr right? //no default values
	int indexColumnFail = -1;
	int indexRowFail = -1;
	
	int columnSize = matrix[0].size(); //should be equal for every row
	try
	{
		//firstly make back of the selected rows
		int sizeSelectedRows = indexSelectedRows.size();
		for (size_t i = 0; i < sizeSelectedRows; i++)
		{
			std::vector<Data*> row;
			for (size_t c = 0; c < columnSize; c++)
			{
				row.push_back(matrix[indexSelectedRows[i]][c]->clone());
			}
			backupRows.push_back(std::move(row));
		}

		//try to delete row
		for (size_t i = 0; i < sizeSelectedRows; i++)
		{
			for (size_t c = 0; c < columnSize; c++)
			{
				if (i == wantedRow && c == wantedColumn)
				{
					throw "";
				}
				delete matrix[indexSelectedRows[i]][c];//if this fails
				matrix[indexSelectedRows[i]][c] = nullptr; //for operator = move
				
				//saving the last success
				indexRowFail= i;
				indexColumnFail = c + 1;
			}
		}

		int dataRowsSize = matrix.size();
		int indToDelete = 0;
		int indForTraveresed = indexSelectedRows[indToDelete];
		//shift the undeleted
		for (size_t i = indexSelectedRows[indToDelete]; i < dataRowsSize; i++)
		{
			if (indToDelete < sizeSelectedRows && i == indexSelectedRows[indToDelete]) //if its in the selectedRows skip it
			{
				indToDelete++;
				continue;
			}
			if (indForTraveresed != i) //after skipped selected Rows move the next one to it
			{
				matrix[indForTraveresed] = std::move(matrix[i]);
			}
			indForTraveresed++;
		}
		
		//shrinking
		matrix.resize(dataRowsSize - sizeSelectedRows);
	}
	catch (...)
	{
		//bool partialFailure = indexRowFail != -1 && indexColumnFail != columnSize;

		////restore the back up for the deleted rows
		//for (size_t i = 0; i < indexRowFail; i++)
		//{
		//	//copy from the back up
		//	matrix[indexSelectedRows[i]] = std::move(backupRows[i]);
		//}

		////restore from the back up if its midRow 
		//for (size_t i = 0; i < indexColumnFail; i++)
		//{
		//	//copy from the back up
		//	matrix[indexSelectedRows[countSuccededRowsDeletes - 1]][i] = std::move(backupRows[- 1][i]); 
		//}
		if (indexRowFail == -1)
		{
			//do nothing
		}
		else
		{
			bool isPartialColumn = (indexColumnFail != 0 && indexColumnFail != columnSize); //checks if the failed is first one of a row
			int restoreRows = isPartialColumn ? indexRowFail : indexRowFail + 1; //+1 for the cycle later

			// Restore full rows
			for (int i = 0; i < restoreRows; i++) {
				matrix[indexSelectedRows[i]] = std::move(backupRows[i]);
			}

			// Restore partially failed row
			if (isPartialColumn) {
				int failedMatrixRow = indexSelectedRows[indexRowFail];
				for (int c = 0; c < indexColumnFail; c++) {
					swap(matrix[failedMatrixRow][c], backupRows[indexRowFail][c]); //why does it not work with operator = std::move()
				}
				// Delete remaining backup cells
				/*for (size_t c = indexColumnFail; c < backupRows[indexRowFail].size(); c++) {
					delete backupRows[indexRowFail][c];
					backupRows[indexRowFail][c] = nullptr;
				}*/
			}
		}
	}
	//clearing the back up
	int rowsCount = backupRows.size();
	for (size_t i = 0; i < rowsCount; i++)
	{
		int columsCount = backupRows[i].size();
		for (size_t c = 0; c < columsCount; c++)
		{
			delete backupRows[i][c];
		}
	}
}

void printMatrixOfData(const std::vector<std::vector<Data*>>& matrix) {
	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::cout << i << "|";
		for (size_t y = 0; y < matrix[0].size(); y++)
		{
			if (matrix[i][y]) matrix[i][y]->print(std::cout);
			std::cout << " ";
		}
		std::cout << '\n';
	}
}
void deleteMatrixOfData(std::vector<std::vector<Data*>>& matrix)
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t y = 0; y < matrix[0].size(); y++)
		{
			delete matrix[i][y];
		}
	}
}
void testTestDelete() {
	int counter = 0;
	std::vector<std::vector<Data*>> matrix(5, std::vector<Data*>(3));
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix[i].size(); j++) {
			matrix[i][j] = new Integer(counter);
			counter++;
		}
	}

	// Print the original matrix
	std::cout << "\nOriginal matrix:\n";
	printMatrixOfData(matrix);

	// Select rows to delete
	std::vector<int> toDelete = { 0, 1 };
	std::cout << "Will delete these rows: ";
	for (size_t i = 0; i < toDelete.size(); i++) std::cout << toDelete[i] << " ";


	std::cout << std::endl;
	int throwRowInSelected = 1;
	int throwColum = 0;
	std::cout << "Where it should throw on " << toDelete[0] << " " << throwColum << std::endl;

	// Perform transactional delete
	testDeleteSelectedRows(toDelete, matrix, throwRowInSelected, throwColum);

	// Show the result
	std::cout << "\nAfter deletion:\n";
	printMatrixOfData(matrix);

	/////////////////////////////////////////////////
	
	std::cout << "Where it should throw on " << toDelete[1] << " " << throwColum << std::endl;

	// Perform transactional delete
	testDeleteSelectedRows(toDelete, matrix, throwRowInSelected, throwColum);

	// Show the result
	std::cout << "\nAfter deletion:\n";
	printMatrixOfData(matrix);

	/////////////////////////////////////////////////
	std::cout << "Where it shouldn't throw" << std::endl;

	// Perform transactional delete
	testDeleteSelectedRows(toDelete, matrix, -1, -1);

	// Show the result
	std::cout << "\nAfter deletion:\n";
	printMatrixOfData(matrix);

	/////////////////////////////////////////////////
	deleteMatrixOfData(matrix);
}
///////////////////////////////////////////////////////////////////////////
//how exceptions should be tested ??
void testDBshowtables() {
	std::string filePath;
	Database db(filePath);
	try
	{
		//db.setFilePath(filePath); this should fail

		filePath = "db.txt";
		db.setFilePath(filePath); //this should not fail

		///////////////////////////////////
		//create some tables
		Table tab(std::string("tab"));
		Table tab1(std::string("tab1"));

		Decimal dec(55.89);
		Date date(1, 2, 3000);
		MyString str("123\"4");

		std::vector<Data*> vec{ &dec, &date, &str };

		tab.addLine(vec);

		tab1.addLine(vec);
		tab1.addLine(vec);


		db.addTable(tab);
		db.addTable(tab1);

		/*Table tab2(tab1); 
		db.addTable(&tab2);*/ //should throw

		db.showTables();
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void testDBprints() {
	std::string filePath;
	Database db(filePath);
	try
	{
		std::string filePath;
		//db.setFilePath(filePath); this should fail

		filePath = "db.txt";
		db.setFilePath(filePath); //this should not fail

		///////////////////////////////////
		//create some tables
		std::string tableName("tab1");
		Table tab1(tableName);

		Decimal dec(55.89);
		Date date(1, 2, 3000);
		MyString str("123\"4");

		std::vector<Data*> vec{ &dec, &date, &str };

		tab1.addLine(vec);
		tab1.addLine(vec);
		tab1.addLine(vec);
		tab1.addLine(vec);
		tab1.addLine(vec);

		db.addTable(tab1);
		db.print(tableName);
		db.print(tableName, 3);


	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void testDBexport() {
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some tables
		std::string tableName("tab1");
		Table tab1(tableName);

		Decimal dec(55.89);
		Date date(1, 2, 3000);
		MyString str("123\"4");

		std::vector<Data*> vec{ &dec, &date, &str };

		tab1.addLine(vec);
		tab1.addLine(vec);

		db.addTable(tab1);
		db.print(tableName);

		std::string filePath("db.txt");
		db.exportTable(tableName, filePath);
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void testDBSelect() {
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some tables
		std::string tableName("tab1");
		Table tab(tableName);

		Decimal dec(55.89), dec1(432.5), dec2(4654.5);
		Integer inte1, inte2(2), inte3(3), inte4(4), inte5(5);

		std::vector<Data*> vec = { &dec, &inte1, &inte2 };
		std::vector<Data*> vec2 = { &dec2, &inte4, &inte5 };
		std::vector<Data*> vec3 = { &dec1, &inte3, &inte2 };

		tab.addLine(vec);
		tab.addLine(vec2);
		tab.addLine(vec3);

		db.addTable(tab);
		db.print(tableName);

		std::cout << std::endl << "Selection by third column for Integer(3)" << std::endl;
		db.select(2, &inte3, tableName);

		std::cout << std::endl << "Selection by second column for Null" << std::endl;
		db.select(1, &inte1, tableName);

		std::cout << std::endl << "Selection by third column for Integer(2)" << std::endl;
		db.select(2, &inte2, tableName);
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}
void testDBmodify() {
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some tables
		std::string tableName("tab1");
		Table tab(tableName);

		Decimal dec(55.89);
		Date date(1, 2, 3000);
		MyString str("1234");
		MyString str1("12/34");

		std::vector<Data*> vec{ &dec, &date, &str };
		tab.addLine(vec);
		tab.addLine(vec);
		vec[2] = &str1;
		tab.addLine(vec);

		db.addTable(tab);
		db.print(tableName);
		/////////////////the modify
		std::cout << std::endl << "Now this is the modified version of the table where String -> Int" << std::endl << std::endl;

		std::string inte("Integer");
		db.modify(2, inte, tableName);
		db.print(tableName);
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void testDBaddColumn() {
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some tables
		std::string tableName("tab1");
		Table tab(tableName);

		Decimal dec(55.89);
		Date date(1, 2, 3000);
		MyString str("1234");
		MyString str1("12/34");

		std::vector<Data*> vec{ &dec, &date, &str };
		tab.addLine(vec);
		tab.addLine(vec);
		vec[2] = &str1;
		tab.addLine(vec);

		db.addTable(tab);
		db.print(tableName);
		/////////////////action/////////////////
		Integer inte(4);
		std::string columnName("age"); //it doesn't do anything for now
		db.addColumn(columnName, &inte, tableName);
		/////////////////action/////////////////

		std::cout << "=============After adding column Integer=============" << std::endl;
		db.print(tableName);
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}
void testDBupdate() {
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some tables
		std::string tableName("tab1");
		Table tab(tableName);
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

		db.addTable(tab);
		db.print(tableName);
		/////////////////action/////////////////
		std::cout << std::endl << "Will change " << str.getName() << " to " << date.getName() << ": ";
		date.print(std::cout);
		std::cout << std::endl << "Only by rows which have " << inte.getName() << ": ";
		inte.print(std::cout);
		std::cout << std::endl << std::endl;

		db.update(0, &inte, 2, &date, tableName);
		/////////////////action/////////////////

		std::cout << "=============After update=============" << std::endl;
		db.print(tableName);
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void testDBdelete() {
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some tables
		std::string tableName("tab1");
		Table tab(tableName);

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

		db.addTable(tab);
		db.print(tableName);
		/////////////////action/////////////////
		int wantedColumn = 0;
		std::cout << std::endl << std::endl << "Will delete rows which have " << inte.getName() << ": ";
		inte.print(std::cout);
		std::cout << " on column " << wantedColumn << std::endl << std::endl;

		db.deleteTableRows(wantedColumn, &inte, tableName);
		/////////////////action/////////////////

		std::cout << "=============After delete=============" << std::endl;
		db.print(tableName);
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void testDBinsert() 
{
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some data
		Decimal dec(55.89);
		Integer inte(3);
		Integer inte1(5);
		Date date(1, 2, 3000);
		MyString str("12/3/1901");

		std::vector<Data*> vec{ &inte,&dec,&str };
		std::vector<Data*> vec1{ &inte1,&dec,&str };

		std::string tableName("tab");
		std::string tableName1("tab1");
		/////////////////action/////////////////
		std::cout << "//////////////////////////////////////////////" << std::endl;
		std::cout << "Inserting line in \"" << tableName << "\"" << std::endl;
		db.insert(vec, tableName);
		db.print(tableName);

		std::cout << "//////////////////////////////////////////////" << std::endl;
		std::cout << "Inserting line in \"" << tableName << "\"" << std::endl;
		db.insert(vec1, tableName);
		db.print(tableName);
		///////////////////////////
		std::cout << "//////////////////////////////////////////////" << std::endl;
		std::cout << "Inserting line in \"" << tableName1 << "\"" << std::endl;
		db.insert(vec1, tableName1);
		db.print(tableName1);

		db.insert(vec1, tableName1);
		db.insert(vec1, tableName1);
		std::cout << "//////////////////////////////////////////////" << std::endl;
		std::cout << "After some inserting \"" << tableName1 << "\"" << std::endl;
		db.print(tableName1);
		/////////////////action/////////////////
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void testDBloadAndSave() {
	std::string filePath;
	Database db(filePath);
	try
	{
		///////////////////////////////////
		//create some data
		Decimal dec(55.89);
		Integer inte(3);
		Integer inte1(5);
		Date date(1, 2, 3000);
		MyString str("12/3/1901");

		std::vector<Data*> vec{ &inte,&dec,&str };
		std::vector<Data*> vec1{ &inte1,&dec,&str };

		std::string tableName("tab");
		std::string tableName1("tab1");

		db.insert(vec, tableName);
		db.insert(vec1, tableName);

		db.insert(vec1, tableName1);
		db.insert(vec1, tableName1);
		db.insert(vec1, tableName1);

		db.printAllTables();
		std::string filePath("dbSer.txt");
		db.saveAs(filePath);

		std::cout << "===========Loading on db2===========" << std::endl;
		std::string filePath2;
		Database db2(filePath2);
		db2.load(filePath);
		db2.printAllTables();
	}
	catch (const char* exp) {
		std::cout << exp << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

int main()
{
	//testDBexport();
	/*std::string fileName("opit2.txt");
	testTableSerAndDes(fileName);*/

	return 0;	
}

void reserveVecFunc() {
	std::vector<int> a;
	a.push_back(1);
	std::cout << a.size() << " " << a.capacity() << std::endl;

	a.reserve(8);
	std::cout << a.size() << " " << a.capacity();
	
}
