#pragma once 
#include "Data.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Utils.hpp"

constexpr int DEFAULT_SPACING = 3; //does it have to be static to not be seen by other files ?
constexpr int SPACING_FOR_FILES = 1;



class Table {
private:
	//would it be good idea to have insight class Row { vec<Data*> }
	std::string name;
	std::vector<std::vector<Data*>> data;
public:
	///////===constructors===///////
	//Table() = default; //cannot have this because of the desirialization of empty string
	Table(const std::string& name);
	Table(std::string&& name); //for testing purposes
	
	//Big six //because data is holding Data*
	Table(const Table& other);
	//Table(Table&& other) = delete;
	Table& operator=(const Table&& other) = delete;
	Table& operator=(Table&& other) = delete;
	//Table(int rows,int colums);
	~Table();
	
	///////===needed fucntions===///////
	

	std::string getName()const; //this makes a copy of it, could it be better if it's const char*
	
	bool isEmpty() const;
	///////===functionality===///////
	void addLine(const std::vector<Data*>& row); //insert types //needs refactoring
	void addColumn(const Data* data); //addcolumn 
	
	void print() const;
	void print(int rpn) const; //need functionallity like first page ...
	void printTypes(std::ostream& os, int count = DEFAULT_SPACING) const; //describe //is it a problem to use default values

	void select(unsigned indexColumn, const Data* value); //select
	
	//Serialization, Deserialization
	void writeToStream(std::ostream& os) const; //export
	void readFromStream(std::istream& is); //that function here means: we have to create first Table through the default constructor //needs refactoring

	//void changeOneValue();

	void update(unsigned indexColumn, const Data* value, unsigned targetColumn, const Data* targetValue); //update
	void modify(unsigned targetColumn, const std::string& targetValue); //modify

	void deleteSelectedRows(unsigned searchColumn, const Data* searchValue);//delete
	///////////////////////////////////
private:

	void printRows(int start, int end) const;
	void printSelectedRows(const std::vector<int>& indexRows) const;
	void printRow(int indexRow, std::ostream& os = std::cout) const;
	void printRowData(std::ostream& os,int indexRow, int spacingSize = DEFAULT_SPACING) const;
	
	int nextCappacityForVector(int currCap) const;
	
	void getRowIndWithValue(unsigned searchColumn, const Data* searched, std::vector<int>& indexSelectedRows); //can this throw 
	//void swapData(unsigned currIndex, unsigned selectedRow, unsigned targetColumn, const Data* targetValue, int& currIndSelectedRows);
	
	void canDataSwap(std::vector<Data*>& bufferForSwap, const std::string& targetType, unsigned targetColumn); //could change the name
	//could this be refactored and use the one above?
	void canDataSwapWithSelect(std::vector<Data*>& bufferForSwap, const std::string& targetType, unsigned targetColumn, const std::vector<int>& indexSelectedRows, const Data* targetValue); //could change the name
	void swapRow(std::vector<Data*>& bufferForSwap, unsigned targetColumn);
	
	void copySpecificRows(const std::vector<int> selectedRows, std::vector<std::vector<Data*>> bufferForCopyRows);
	//will these be a good idea?
	//int columnsCount() const;
	//int rowsCount() const;
	bool setData(const std::vector<std::vector<Data*>>& other);
	bool setName(const std::string& name); //it not needed for now
};