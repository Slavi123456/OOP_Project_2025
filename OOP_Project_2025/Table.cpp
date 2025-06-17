#include "Table.hpp"
//#include <cmath> //in the standart library there is abs
#include "Factory.hpp"
#include "Integer.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename T>
static void swap(T& lhs, T& rhs) {
	T helper = lhs;
	lhs = rhs;
	rhs = helper;
}
////////////////////////////////////////////////////////////////////////////////

//it's needed because we hold pointers which have to be deleted
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
		this->data.reserve(nextCappacityForVector(rowCappacity)); //this only allocates //NO calling default constructor
	}

	//check if there is any rows already
	int rowSize = row.size();
	if (currSize != 0) {
		//checking if the row has equal to the table fields
		if (rowSize != this->data[0].size()) throw "kvo praim";

		//check if the types are equal // could be rewritten if can transfer one type to another like Integer to Double or something other
		for (size_t i = 0; i < rowSize; i++) //won't it be better to make class Row 
		{
			if (!row[i]) throw "there is nullptr in the row vector in addLine";
			if (strcmp(this->data[0][i]->getName(), row[i]->getName()) != 0) throw "types doesnt match";
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
	if (!data) return; //do i need to throw ?


	//if it's empty i want to add one row and then the column; 
	//Because this doesnt add rows: checking for resize it's not needed
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
	printTypes(std::cout, DEFAULT_SPACING);

	for (size_t i = start; i < end; i++)
	{
		printRow(i);
	}
}
void Table::printSelectedRows(const std::vector<int>& indexRows) const
{
	printTypes(std::cout, DEFAULT_SPACING);

	int sizeArr = indexRows.size();
	for (size_t i = 0; i < sizeArr; i++)
	{
		printRow(indexRows[i]);
	}
}
void Table::printRow(int indexRow, std::ostream& os) const
{
	std::cout << indexRow << std::string(DEFAULT_SPACING, ' ');
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

	os << std::endl;
}
void Table::printTypes(std::ostream& os, int count) const
{
	if (this->data.empty()) {
		//os << "This table is empty" << std::endl; //wouldnt it be better to throw "cannot print types that are empty"?? 
		return;
	}
	std::string spacing(count, ' '); 
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
	if (!value)
	{
		throw "Cannot select by nullptr value";
	}
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
	
	
	std::vector<int> indexSelectedRows;
	getRowIndWithValue(indexColumn, value, indexSelectedRows);

	printSelectedRows(indexSelectedRows);
}

void Table::writeToStream(std::ostream& os) const {
	
	if (this->data.empty()) {
		return;
	}

	printTypes(os, SPACING_FOR_FILES);
	
	int rowsCount = this->data.size();
	for (size_t i = 0; i < rowsCount; i++)
	{
		printRowData(os, i, SPACING_FOR_FILES);
	}
}
void Table::readFromStream(std::istream& is) //refactoring!!! 
{
	//how to make the exception safety here ?
	//which is better: reading line by line / the whole at one
	
	//getting the line with types
	std::string line;
	std::getline(is, line); //can this throw??

	std::vector<std::string> types;
	splitLineInWords(line, types, ' '); //can this be changed to reading string till end of line //becuase stream >> string will skip the '\n'

	while (std::getline(is, line)) //if it's with is.eof() it will make one cycle more for the eof symbol
	{
		std::vector<std::string> values;
		splitLineInWords(line, values, ' ');
		
		/*if (values.size() != types.size()) //this wont work from now on becuase the Date want 3arguments 
		{
			throw "Count of the needed parameters doesn't match the count of the wanted types";
		}*/

		std::vector<Data*> dataValues;
		int sizeTypes = types.size();
		int indTypes = 0;
		int sizeValues = values.size();
		int indValues = 0;

		while (indTypes < sizeTypes && indValues < sizeValues) //had to make it while because: values.size() != types.size()
		{
			//try catch ?
			dataValues.push_back(dataFactory(types[indTypes], values, indValues));
			indValues++;
			indTypes++;
		}
		
		addLine(dataValues);
	}
}

void Table::update(unsigned indexColumn, const Data* value, unsigned targetColumn, const Data* targetValue)
{
	if (!value)
	{
		throw "Cannot update by nullptr value";
	}
	if (!targetValue)
	{
		throw "Target value for update is nullptr";
	}
	if (this->data.size() <= 0)
	{
		throw "cannot do update before adding values";
	}
	if (this->data[0].empty())
	{
		throw "the table doesn't have any columns";
	}
	if (indexColumn >= this->data[0].size()) {
		throw "indexcolumn is bigger then the table's column count";
	}
	if (targetColumn >= this->data[0].size()) {
		throw "target column is bigger then the table's column count";
	}

	std::vector<int> indexSelectedRows;
	getRowIndWithValue(indexColumn, value, indexSelectedRows);

	int rowsCount = this->data.size();
	int currIndSelectedRows = 0;
	
	//is this okay by project description
	for (size_t i = 0; i < rowsCount; i++)
	{
		Data* swapData = nullptr;
		//check if its in the selected rows
		if (currIndSelectedRows < indexSelectedRows.size() && i == indexSelectedRows[currIndSelectedRows])
		{
			//for throwing from not enough memory
			try
			{
				swapData = targetValue->clone();
			}
			catch (...)
			{
				throw "Couldn't update the target column";
			}
			currIndSelectedRows++;
		}
		else
		{
			//for throwing from a convertion problem
			try
			{
				swapData = this->data[i][targetColumn]->converTo(targetValue->getName());
			}
			catch (...) 
			{
				//for throwing from not enough memory
				try
				{
					//if not put default state
					swapData = targetValue->emptyClone();
				}
				catch (...)
				{
					throw "Couldn't update the target column";
				}
			}
		}
		if (!swapData) throw "Couldn't assign value to swap in the update";

		//delete it
		delete[]this->data[i][targetColumn];
		swap(this->data[i][targetColumn], swapData);
	}
}

//void Table::changeOneValue()
//{
//	delete[]this->data[0][2];
//	Integer* inte = new Integer(1);
//	data[0][2] = inte;
//}

int Table::nextCappacityForVector(int currCap) const
{
	int res = 2;
	while (currCap > res)
	{
		res *= 2;
	}
	return res;
}

void Table::getRowIndWithValue(unsigned searchColumn, const Data* searched, std::vector<int>& indexSelectedRows)
{
	int rowsCount = this->data.size();

	for (size_t i = 0; i < rowsCount; i++)
	{
		if (*searched == data[i][searchColumn])
		{
			indexSelectedRows.push_back(i);
		}
	}

}
void Table::swapData(unsigned currIndex, unsigned selectedRow, unsigned targetColumn, const Data* targetValue, int& currIndSelectedRows)
{
	delete[]this->data[currIndex][targetColumn];
	if (currIndex > selectedRow)
	{
		currIndSelectedRows++;
	}
	else if (currIndex == selectedRow)
	{
		Data* swapData = targetValue->clone();
		swap(this->data[currIndex][targetColumn], swapData);
		currIndSelectedRows++;
	}
	else
	{
		Data* swapData = targetValue->emptyClone();
		swap(this->data[currIndex][targetColumn], swapData);
	}
}
////////////////////////////////////////////////////////////////////////////////