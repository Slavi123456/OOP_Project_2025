#pragma once 
#include "Data.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

constexpr int DEFAULT_SPACING = 3; //does it have to be static to not be seen by other files ?
constexpr int SPACING_FOR_FILES = 1;

static void splitLineInWords(const std::string& line, std::vector<std::string>& words);

class Table {
public:
	Table() = default;
	//Table(int rows,int colums);
	~Table();
	
	void addLine(const std::vector<Data*>& row); //insert types //needs refactoring
	void addColumn(const Data* data); //addcolumn 
	
	void print() const;
	void print(int rpn) const; //need functionallity like first page ...
	void printTypes(std::ostream& os, int count = DEFAULT_SPACING) const; //describe //is it a problem to use default values

	void select(unsigned indexColumn, const Data* value); //select
	
	//Serialization, Deserialization
	void writeToStream(std::ostream& os) const; //export
	void readFromStream(std::istream& is); //that function here means: we have to create firstly Table through the default constructor //needs refactoring
private:

	void printRows(int start, int end) const;
	void printSelectedRows(const std::vector<int>& indexRows) const;
	void printRow(int indexRow, std::ostream& os = std::cout) const;
	void printRowData(std::ostream& os,int indexRow, int spacingSize = DEFAULT_SPACING) const;
	
	int nextCappacityForVector(int currCap) const;
	
	//will these be a good idea?
	//int columnsCount() const;
	//int rowsCount() const;
	
	//would it be good idea to have insight class Row { vec<Data*> }
	std::string name;
	std::vector<std::vector<Data*>> data; 
};