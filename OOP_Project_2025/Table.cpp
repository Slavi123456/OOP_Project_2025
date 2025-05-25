#include "Table.hpp"
#include <iostream> //does it have to be in the hpp
#include <cmath>

Table::~Table()
{
	int rowsCount = data.size();
	for (size_t i = 0; i < rowsCount; i++)
	{
		int columsCount = data[i].size();
		for (size_t c = 0; c < columsCount; c++)
		{
			delete[] data[i][c];
		}
	}
}

void Table::addLine(const std::vector<Data*>& row) //needs refactoring
{
	//check if resize it's needed
	int rowCappacity = this->data.capacity();
	int currSize = this->data.size();
	if (currSize + 1 > rowCappacity)
	{
		this->data.reserve(nextCappacityForVector(rowCappacity)); //this only allocates 
	}

	//check if there is any rows already
	int rowSize = row.size();
	if (currSize != 0) {
		//checking if the row has equal to the table fields
		if (rowSize != this->data[0].size()) throw "kvo praim";

		//check if the types are equal // could be rewritten if can transfer one type to another like Integer to Double or something other
		for (size_t i = 0; i < rowSize; i++) //won't it be better to make class Row 
		{
			if (strcmp(this->data[0][i]->getName(), row[i]->getName()) != 0) throw "kvo praim";
		}
	}
	
	//filling already checked row
	std::vector<Data*> vec;
	for (size_t i = 0; i < rowSize; i++)
	{
		Data* copy = row[i]->clone();
		vec.push_back(copy);
	}
	this->data.push_back(vec);
}
void Table::addColumn(const Data* data)
{
	//if it's empty i want to add one row and then the column; 
	//Because this doesnt add rows: resize it's not needed
	if (this->data.empty()) {
		this->data.reserve(nextCappacityForVector(this->data.capacity())); 
		std::vector<Data* >vec;
		this->data.push_back(vec);
	}

	//add column
	int currSize = this->data.size();
	for (size_t i = 0; i < currSize; i++)
	{
		Data* empty = data->emptyClone(); //does it have to be with this
		this->data[i].push_back(empty);
	}
}

void Table::print() const
{
	printRows(0, this->data.size());
}
void Table::print(int rpn) const //it needs functionalities like first page etc.
{

	int currSize = this->data.size();
	if (rpn > currSize)
	{
		printRows(0, currSize);
		return;
	}

	int startRow = 0;
	while (startRow + rpn < currSize) {
		
		printRows(startRow, startRow + rpn);
		startRow += rpn;
	}
	int diff = std::abs(startRow - currSize);
	if (diff != 0)
	{
		printRows(currSize - diff, currSize);
	}
}
void Table::printRows(int start, int end) const
{
	if (this->data.empty() || start == end) return;
	printTypes(DEFAULT_SPACING);

	for (size_t i = start; i < end; i++)
	{
		printRow(i);
	}
}
void Table::printSelectedRows(const std::vector<int>& indexRows) const
{
	printTypes(DEFAULT_SPACING);

	int sizeArr = indexRows.size();
	for (size_t i = 0; i < sizeArr; i++)
	{
		printRow(indexRows[i]);
	}
}
void Table::printRow(int indexRow, std::ostream& os) const
{
	std::cout << indexRow << "  "; //better spacing way
	printRowData(os, indexRow, DEFAULT_SPACING);
}
void Table::printRowData(std::ostream& os, int indexRow, int spacingSize) const
{
	std::string spacing(spacingSize, ' ');
	int columsCount = data[indexRow].size();
	for (size_t c = 0; c < columsCount; c++)
	{
		data[indexRow][c]->print(os); 
		os << spacing;
	}

	std::cout << std::endl;
}
void Table::printTypes(int count, std::ostream& os) const
{
	if (this->data.empty()) {
		//os << "This table is empty" << std::endl; //wouldnt it be better to throw "cannot print types that are empty"?? 
		return;
	}
	std::string spacing(count, ' '); //need to check for the aligment of the values
	os << spacing; 
	
	int columsCount = data[0].size();
	for (size_t c = 0; c < columsCount; c++)
	{
		os << data[0][c]->getName() << spacing;
	}
	os << std::endl;
}

void Table::select(unsigned indexColumn, const Data* value)
{
	if (this->data.size() <= 0)
	{
		throw "cannot do select before adding values";
	}
	if (this->data[0].empty())
	{
		throw "the table doesn't have any columns";
	}
	if (indexColumn >= this->data[0].size()) {
		throw "indexcolumn is bigget then the table's column count";
	}

	int columnsCount = this->data[0].size(); 
	std::vector<int> indexSelectedRows;
	for (size_t i = 0; i < columnsCount; i++)
	{
		if (*value == data[i][indexColumn])
		{
			indexSelectedRows.push_back(i);
		}
	}

	printSelectedRows(indexSelectedRows);
}

std::ostream& Table::writeToStream(std::ostream& os) const {
	
	if (this->data.empty()) {
		return os;
	}

	printTypes(SPACING_FOR_FILES);
	
	int rowsCount = this->data.size();
	for (size_t i = 0; i < rowsCount; i++)
	{
		printRowData(os, i, SPACING_FOR_FILES);
	}

	return os;
}

int Table::nextCappacityForVector(int currCap) const
{
	int res = 2;
	while (currCap > res)
	{
		res *= 2;
	}
	return res;
}
////////////////////////////////////////////////////////////////////////////////
Data* dataFactory(std::string& type, std::string& value)
{
	return nullptr;
}
