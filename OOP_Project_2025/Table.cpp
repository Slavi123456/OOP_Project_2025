#include "Table.hpp"
//#include <cmath> //in the standart library there is abs
#include "Factory.hpp"
#include "Integer.hpp"
#include "Utils.hpp" //for swap
//#include <iostream> //for print
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
static const char* END_OF_TABLE_WRITE = "==============================================="; //there was a problem with constexpr 

Table::Table(const std::string& name): name(name)
{

}

Table::Table(std::string&& name): name(name)
{
}

Table::Table(const Table& other)
{
	if (!setName(other.name)
        || !setData(other.data))
	{
		throw "Cannot construct new table";
	}
}

//it's needed because we hold pointers which have to be deleted
Table::~Table()
{
	int rowsCount = data.size();
	for (size_t i = 0; i < rowsCount; i++)
	{
		int columsCount = data[i].size();
		for (size_t c = 0; c < columsCount; c++)
		{
			delete data[i][c];
		}
	}
}

std::string Table::getName() const
{
	return name;
}

bool Table::isEmpty() const
{
	return this->data.empty() || this->data[0].empty();
}

///////===functionality===///////
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
		if (rowSize != this->data[0].size()) throw "New row's size doesn't match with the size of Table's rows";

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
	if (!data) throw "Cannot add nullptr value";

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
	std::cout << "Table \"" << (this->name) << "\" is: " << std::endl;
	printRows(0, this->data.size());
	std::cout << std::endl;
}
void Table::print(int rpn) const //it needs functionalities like first page etc.
{
	//checks if the rpn is bigger than the row count to make regular print
	int currSize = this->data.size();
	if (rpn > currSize)
	{
		std::cout << "The rpn you've choosed is bigger than the count of rows in the Table so here is regular print: " << std::endl;
		printRows(0, currSize);
		return;
	}

	/*int startRow = 0;
	while (startRow + rpn < currSize) {
		
		printRows(startRow, startRow + rpn);
		startRow += rpn;
	}
	int diff = std::abs(startRow - currSize);
	if (diff != 0)
	{
		printRows(currSize - diff, currSize);
	}*/
	enum PageOptions {
		First = 0,
		Next,
		Previous,
		Last,
		Close
	};
	int currOption = (int)PageOptions::First;
	int currPage = 0;
	int maxPages = (currSize / rpn);
	while (true)
	{
		std::cout << "Choose an option: {First page = 0, Next page = 1, Previous page = 2,Last page = 3,Close = 4}" << std::endl;
		std::cin >> currOption;
		if (currOption > 4 || currOption < 0)
		{
			std::cout << "There is no option like this" << std::endl;
			continue;
		}
		switch (currOption)
		{
		case First: currPage = 0; break;
		case Next:
			if (currPage + 1 > maxPages)
			{
				std::cout << "Pages are from 0 to " << maxPages << std::endl;
				continue;
			}
			currPage++;
			break;
		case Previous:
			if (currPage - 1 < 0)
			{
				std::cout << "Pages are from 0 to " << maxPages << std::endl;
				continue;
			}
			currPage--;
			break;
		case Last: currPage = maxPages; break;
		case Close: return; break;
		default:break;
		}
		std::cout << "======== This is page is " << currPage << "========" << std::endl;
		
		int endRow = (currPage == maxPages) ? currSize :(currPage + 1) * rpn; //if currSize % rpn != 0
		printRows(currPage* rpn, endRow);
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
	if (isEmpty()) {
		//os << "This table is empty" << std::endl; //wouldnt it be better to throw "cannot print types that are empty"?? 
		//return;
		throw "The table is empty there is nothing to print";
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
	if (!value) throw "Cannot select by nullptr value";
	if (isEmpty()) throw "The table is empty cannot do select";
	if (indexColumn >= this->data[0].size()) throw "index of the Column for selection is bigger then the table's column count";
	
	std::vector<int> indexSelectedRows;
	getRowIndWithValue(indexColumn, value, indexSelectedRows);

	printSelectedRows(indexSelectedRows);
}

void Table::writeToStream(std::ostream& os) const {
	
	if (isEmpty()) throw "The table is empty cannot write it to stream";
	
	int rowsCount = this->data.size();
	int columnsCount = this->data[0].size();
	os << this->name << std::endl; // " " << rowsCount << " " << columnsCount << std::endl; //not needed 

	printTypes(os, SPACING_FOR_FILES);

	for (size_t i = 0; i < rowsCount; i++)
	{
		printRowData(os, i, SPACING_FOR_FILES);
	}
	os << END_OF_TABLE_WRITE << std::endl;

}
void Table::readFromStream(std::istream& is) //refactoring!!! 
{
	//how to make the exception safety here ?
	//which is better: reading line by line / the whole at one
	
	is >> this->name;
	//these are not needed
	/*int rowCount;
	int columnCount;
	is >> rowCount >> columnCount;*/

	is.ignore(); //because >> stop on ' ', '\0' and the getline will fail //also it won't tell you if failed

	//getting the line with types
	std::string line;
	std::getline(is, line); //can this throw??

	std::vector<std::string> types;
	splitLineInWords(line, types, ' '); //can this be changed to reading string till end of line //becuase stream >> string will skip the '\n'

	while (std::getline(is, line)) //if it's with is.eof() it will make one cycle more for the eof symbol
	{
		if (line == END_OF_TABLE_WRITE)
		{
			return;
		}
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
	
	//////////////////////////////////////////////////////////////////////this won't work because of NULL
	//std::vector<std::vector<Data*>> copy(rowCount, std::vector<Data*>(columnCount,nullptr));
	//try
	//{
	//	//loading the data
	//	for (size_t i = 0; i < rowCount; i++)
	//	{
	//		std::vector<Data*> row;
	//		for (size_t j = 0; j < columnCount; j++)
	//		{
	//			Data* newData = dataFactoryForEmpty(types[j]);
	//			newData->read(is);
	//			row.push_back(newData);
	//		}
	//		copy[i] = std::move(row);//because i have already initialized copy i need to use operator =
	//	}
	//	this->data = std::move(copy);
	//}
	//catch (...)
	//{
	//	//no need for anything
	//}
	////delete copy
	//for (size_t i = 0; i < rowCount; i++)
	//{
	//	for (size_t j = 0; j < columnCount; j++)
	//	{
	//		delete copy[i][j];
	//	}
	//}

}

void Table::update(unsigned indexColumn, const Data* value, unsigned targetColumn, const Data* targetValue)
{
	if (!value)
	{
		throw "Cannot update to nullptr value";
	}
	if (!targetValue)
	{
		throw "Target value for update is nullptr";
	}
	if (isEmpty()) throw "The table is empty cannot do update";
	if (indexColumn >= this->data[0].size()) {
		throw "indexcolumn is bigger then the table's column count";
	}
	if (targetColumn >= this->data[0].size()) {
		throw "target column is bigger then the table's column count";
	}

	std::vector<int> indexSelectedRows;
	getRowIndWithValue(indexColumn, value, indexSelectedRows);

	//int rowsCount = this->data.size();
	//int currIndSelectedRows = 0;
	//
	////is this okay by project description
	//for (size_t i = 0; i < rowsCount; i++)
	//{
	//	Data* swapData = nullptr;
	//	//check if its in the selected rows
	//	if (currIndSelectedRows < indexSelectedRows.size() && i == indexSelectedRows[currIndSelectedRows])
	//	{
	//		//for throwing from not enough memory
	//		try
	//		{
	//			swapData = targetValue->clone();
	//		}
	//		catch (...)
	//		{
	//			throw "Couldn't update the target column";
	//		}
	//		currIndSelectedRows++;
	//	}
	//	else
	//	{
	//		//for throwing from a convertion problem
	//		try
	//		{
	//			swapData = this->data[i][targetColumn]->converTo(targetValue->getName());
	//		}
	//		catch (...) 
	//		{
	//			//for throwing from not enough memory
	//			try
	//			{
	//				//if not put default state
	//				swapData = targetValue->emptyClone();
	//			}
	//			catch (...)
	//			{
	//				throw "Couldn't update the target column";
	//			}
	//		}
	//	}
	//	if (!swapData) throw "Couldn't assign value to swap in the update";

	//	//delete it
	//	delete[]this->data[i][targetColumn];
	//	swap(this->data[i][targetColumn], swapData);
	//}

	std::vector<Data*> bufferForSwap;
	try
	{
		canDataSwapWithSelect(bufferForSwap, targetValue->getName(), targetColumn, indexSelectedRows, targetValue);
		//if success
		swapRow(bufferForSwap, targetColumn);
	}
	catch (const std::exception&)
	{
		//deleting the buffer data because of a problem
		int bufferSize = bufferForSwap.size();
		for (size_t i = 0; i < bufferSize; i++)
		{
			delete[] bufferForSwap[i];
		}
	}
}

//by the project description this wants Null class//its a bit late to reform
void Table::modify(unsigned targetColumn, const std::string& targetType) 
{
	if (targetType.empty())
	{
		throw "Cannot modify to empty value";
	}
	if (isEmpty()) throw "The table is empty cannot do modify";
	if (targetColumn >= this->data[0].size()) {
		throw "target column is bigger then the table's column count";
	}

	std::vector<Data*> bufferForSwap;
	try
	{
		canDataSwap(bufferForSwap, targetType, targetColumn);
		//if success
		swapRow(bufferForSwap, targetColumn);
	}
	catch (const std::exception&)
	{
		//deleting the buffer data because of a problem
		int bufferSize = bufferForSwap.size();
		for (size_t i = 0; i < bufferSize; i++)
		{
			delete[] bufferForSwap[i];
		}
	}
}

void Table::deleteSelectedRows(unsigned searchColumn, const Data* searchValue)
{
	if (isEmpty()) throw "The table is empty cannot do modify"; //this should not be called 
	if (!searchValue || searchColumn > this->data[0].size())
	{
		throw "Cannot do delete operation because of the search Value and search Column";
	}

	std::vector<int> indexSelectedRows;
	getRowIndWithValue(searchColumn, searchValue, indexSelectedRows);
	if (indexSelectedRows.empty()) return;
	//std::vector<std::vector<Data*>> backupRows; //that will initialize with nullptr right?
	//int countSuccededRowsDeletes = 0;
	//int countSucceededColumnDeletes = 0;
	//try
	//{
	//	//firstly make back of the selected rows
	//	int sizeSelectedRows = indexSelectedRows.size();
	//	for (size_t i = 0; i < sizeSelectedRows; i++)
	//	{
	//		std::vector<Data*> row;
	//		int columnSize = this->data[0].size(); //should be equal for every one
	//		for (size_t c = 0; c < columnSize; c++)
	//		{
	//			row.push_back(this->data[i][c]->clone());
	//		}
	//		backupRows.push_back(std::move(row));
	//	}

	//	//try to delete row
	//	for (size_t i = 0; i < sizeSelectedRows; i++)
	//	{
	//		int columnSize = this->data[0].size(); //should be equal for every one
	//		for (size_t c = 0; c < columnSize; c++)
	//		{
	//			delete[] this->data[i][c]; //if this fails
	//			countSucceededColumnDeletes++;
	//		}
	//		countSucceededColumnDeletes = 0;
	//		countSuccededRowsDeletes++;
	//	}

	//	int dataRowsSize = this->data.size();
	//	int indexSelectedRow = 0;
	//	int indForTraveresed = indexSelectedRows[indexSelectedRow];
	//	//shift the undeleted
	//	for (size_t i = indexSelectedRows[indexSelectedRow]; i < dataRowsSize; i++)
	//	{
	//		if (indexSelectedRow < sizeSelectedRows && i == indexSelectedRows[indexSelectedRow])
	//		{
	//			indexSelectedRow++;
	//			continue;
	//		}
	//		if (indForTraveresed != i)
	//		{
	//			this->data[indexSelectedRow] = std::move(this->data[i]); //but this doesnt makes
	//			indForTraveresed = i;
	//		}
	//	}

	//	//shrinking
	//	this->data.resize(dataRowsSize - indexSelectedRows.size());
	//}
	//catch (...)
	//{
	//	//restore the back up for the deleted rows
	//	for (size_t i = 0; i < countSuccededRowsDeletes; i++)
	//	{
	//		//copy from the back up
	//		this->data[indexSelectedRows[i]] = backupRows[i]; //can this be made by move
	//	}

	//	//restore from the back up if its midRow 
	//	for (size_t i = 0; i < countSuccededRowsDeletes; i++)
	//	{
	//		//copy from the back up
	//		this->data[indexSelectedRows[countSuccededRowsDeletes - 1]][i] = backupRows[countSuccededRowsDeletes - 1][i]; //can this be made by move
	//	}
	//}
	////clearing the back up
	//int rowsCount = backupRows.size();
	//for (size_t i = 0; i < rowsCount; i++)
	//{
	//	int columsCount = backupRows[i].size();
	//	for (size_t c = 0; c < columsCount; c++)
	//	{
	//		delete[] backupRows[i][c];
	//	}
	//}
	std::vector<std::vector<Data*>> backupRows; //that will initialize with nullptr right? //no default values
	int indexColumnFail = -1;
	int indexRowFail = -1;

	int columnSize = this->data[0].size(); //should be equal for every row
	try
	{
		int sizeSelectedRows = indexSelectedRows.size();
		//firstly make back of the selected rows
		copySpecificRows(indexSelectedRows, backupRows);

		//try to delete row
		for (size_t i = 0; i < sizeSelectedRows; i++)
		{
			for (size_t c = 0; c < columnSize; c++)
			{
				delete this->data[indexSelectedRows[i]][c];
				this->data[indexSelectedRows[i]][c] = nullptr; //for operator = move

				//saving the last success
				indexRowFail = i;
				indexColumnFail = c + 1;
			}
		}

		int dataRowsSize = this->data.size();
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
				this->data[indForTraveresed] = std::move(this->data[i]);
			}
			indForTraveresed++;
		}

		//shrinking
		this->data.resize(dataRowsSize - sizeSelectedRows);
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
				this->data[indexSelectedRows[i]] = std::move(backupRows[i]);
			}

			// Restore partially failed row
			if (isPartialColumn) {
				int failedMatrixRow = indexSelectedRows[indexRowFail];
				for (int c = 0; c < indexColumnFail; c++) {
					swap(this->data[failedMatrixRow][c], backupRows[indexRowFail][c]); //why does it not work with operator = std::move()
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

//void Table::changeOneValue()
//{
//	delete[]this->data[0][2];
//	Integer* inte = new Integer(1);
//	data[0][2] = inte;
//}

///////===helper function===///////
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
//void Table::swapData(unsigned currIndex, unsigned selectedRow, unsigned targetColumn, const Data* targetValue, int& currIndSelectedRows)
//{
//	delete[]this->data[currIndex][targetColumn];
//	if (currIndex > selectedRow)
//	{
//		currIndSelectedRows++;
//	}
//	else if (currIndex == selectedRow)
//	{
//		Data* resData = targetValue->clone();
//		swap(this->data[currIndex][targetColumn], resData);
//		currIndSelectedRows++;
//	}
//	else
//	{
//		Data* resData = targetValue->emptyClone();
//		swap(this->data[currIndex][targetColumn], resData);
//	}
//}

void Table::canDataSwap(std::vector<Data*>& bufferForSwap, const std::string& targetType, unsigned targetColumn)
{
	int rowsCount = this->data.size();
	for (size_t i = 0; i < rowsCount; i++)
	{
		Data* swapData = nullptr;
		swapData = this->data[i][targetColumn]->converTo(targetType.c_str()); //if throws it will be captured by the update or modify
		bufferForSwap.push_back(swapData);
	}
}
void Table::canDataSwapWithSelect(std::vector<Data*>& bufferForSwap, const std::string& targetType, unsigned targetColumn, const std::vector<int>& indexSelectedRows, const Data* targetValue)
{
	int rowsCount = this->data.size();
	int currIndSelectedRows = 0;
	for (size_t i = 0; i < rowsCount; i++)
	{
		Data* swapData = nullptr;
		if (currIndSelectedRows < indexSelectedRows.size() && i == indexSelectedRows[currIndSelectedRows])
		{
			//for the selected rows
			swapData = targetValue->clone();//could throw from not enough memory 
			bufferForSwap.push_back(swapData);
			currIndSelectedRows++;
		}
		else
		{
			//for convertion or default 
			swapData = this->data[i][targetColumn]->converTo(targetType.c_str()); //if throws it will be captured by the update or modify
			bufferForSwap.push_back(swapData);
		}
	}
}
void Table::swapRow(std::vector<Data*>& bufferForSwap, unsigned targetColumn)
{
	int rowsCount = this->data.size();
	if (bufferForSwap.size() != rowsCount)
	{
		throw "Size doesnt match"; //from who will this be captured
	}

	for (size_t i = 0; i < rowsCount; i++)
	{
		delete[]this->data[i][targetColumn];
		this->data[i][targetColumn] = nullptr;
		swap(this->data[i][targetColumn], bufferForSwap[i]);
	}
}
void Table::copySpecificRows(const std::vector<int> selectedRows, std::vector<std::vector<Data*>> bufferForCopyRows)
{
	int sizeSelectedRows = selectedRows.size();
	int dataCountColumns = this->data[0].size();
	for (size_t i = 0; i < sizeSelectedRows; i++)
	{
		std::vector<Data*> row;
		for (size_t c = 0; c < dataCountColumns; c++)
		{
			row.push_back(this->data[selectedRows[i]][c]->clone());
		}
		bufferForCopyRows.push_back(std::move(row));
	}
}
bool Table::setData(const std::vector<std::vector<Data*>>& other)
{
	int countOtherRows = other.size();
	int countOtherColumns = other[0].size(); //should be equal for every one
	
	std::vector<std::vector<Data*>> copy(countOtherRows, std::vector<Data*> (countOtherColumns, nullptr)); //initializing the copy 
	try
	{
		//try making a copy
		for (size_t i = 0; i < countOtherRows; i++)
		{
			for (size_t c = 0; c < countOtherColumns; c++)
			{
				if (!other[i][c])
				{
					throw "The table cannot have nullptr";
				}
				copy[i][c] = other[i][c]->clone(); //copy allready has setted row for it with nullptr
			}
		}
		
		//if it's success 
		this->data = std::move(copy); //this will make swap
	}
	catch (...)
	{
		//copy will be cleared outside this
	}

	//clearing the copy //because if there is previous data in this->data it will be moved to copy so we should clear it for safety
	int rowsCount = copy.size();
	for (size_t i = 0; i < rowsCount; i++)
	{
		int columsCount = copy[i].size();
		for (size_t c = 0; c < columsCount; c++)
		{
			delete copy[i][c];
		}
	}
}
bool Table::setName(const std::string& name)
{
	try
	{
		this->name = name;
	}
	catch (...) //if there is no memory
	{
		return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////