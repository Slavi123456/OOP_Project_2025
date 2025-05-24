#include "Table.hpp"
#include <iostream> //does it have to be in the hpp
#include <cmath>
/*
Row::Row() : cap(0), size(0)
{
}

Row::Row(const Row& other)
	: cap(other.cap), size(other.size)
{
	if (!setData) throw "could not construct"; //better exception
}

Row::Row(Row&& other)
	: cap(other.cap), size(other.size)
{
	swap(this->data, other.data);
}

Row& Row::operator=(const Row& other) //does it have to be const MyVec<T>& other
{
	if (this != &other)
	{
		Row copy(other);
		(*this) = std::move(copy);
	}
	return *this;
}

Row& Row::operator=(Row&& other) 
{
	if (this != &other)
	{
		swapAllData(other);
	}
	return *this;
}

Row::~Row()
{
	for (size_t i = 0; i < size; i++)
	{
		
	}
}

void Row::setData(const Data** arr, int size, int cap)
{
}

void Row::swapAllData(const Row& other)
{
	this->cap = other.cap;
	this->size = other.size;
	swap(this->data, other.data);
}

////////////////////////////////////////////////////////////////////////
template<typename T>
MyVec<T>::MyVec(): cap(0), size(0)
{
}

template<typename T>
MyVec<T>::MyVec(const MyVec& other)
	: cap(other.cap), size(other.size)
{
	if (!setData) throw "could not construct"; //better exception
}

template<typename T>
MyVec<T>::MyVec(MyVec&& other)
	: cap(other.cap), size(other.size)
{
	swap(this->data, other->data);
}

template<typename T>
MyVec<T>& MyVec<T>::operator=(const MyVec& other) //does it have to be const MyVec<T>& other
{
	if (this != &other)
	{
		MyVec copy(other);
		(*this) = std::move(copy);
	}
	return *this;
}

template<typename T>
MyVec<T>& MyVec<T>::operator=(MyVec&& other)
{
	if (this != &other)
	{
		swapAllData(other);
	}
	return *this;
}

template<typename T>
MyVec<T>::~MyVec()
{
	//how to check if it's pointer in the T
	//Example for Data* = T  so Data**
	//it will be with for() { delete[] } 
	// that will be blocked if it's int = T so T* 
	//cant be made with for() { delete[] } because we will try to delete data on the stack;
	
	///////BEST SCENARIO////////////
	//is to make sure when its pointer, and when it's not//
	//BUT i dont know if i can you std::is_pointer<T>
}

template<typename T>
int MyVec<T>::getCappacity() const
{
	return 0;
}

template<typename T>
int MyVec<T>::getSize() const
{
	return 0;
}

template<typename T>
bool MyVec<T>::setData(const T* data, const int size, const int cap)
{
}

template<typename T>
void MyVec<T>::swapAllData(const MyVec& other)
{
	this->cap = other.cap;
	this->size = other.size;
	swap(this->data, other->data);
}
*/

Table::Table()//: data(), name()//, currSize(0)
{
}

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

void Table::addLine(const std::vector<Data*>& row)
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
/*
void Table::addLine(const Data* data)
{
	Data* copy = data->clone();
	this->data[currSize++].push_back(copy);
}
void Table::addLine(Data&& data)
{
	Data* copy = data.clone();
	this->data[currSize++].push_back(copy);
}

void Table::addData(const Data* data, int tableIndex) //tableIndex will be given from the search by name from DataBase
{
	if (tableIndex > currSize) throw "Bad";

	if (tableIndex + 1 > currSize)
	{
		int vecCap = this->data.capacity();
		if (tableIndex > vecCap)
		{
			this->data.resize(nextCappacityForVector(vecCap));
		}
	}
	

	//Data* copy = new Data(data); //error: Data is abstract class 
	// also we don't know if it's only Data and not Integer, Decimal //so we make clone 
	for (size_t i = 0; i < currSize; i++)
	{
		if (i == tableIndex)
		{
			Data* copy = data->clone(); //exception safety ??
			this->data[i].push_back(copy);
		}
		else
		{
			Data* empty = data->emptyClone();
			this->data[i].push_back(empty);
		}
	}
	
}
void Table::addData(Data&& data, int tableIndex) 
{

	//Data* copy = new Data(data); //error: Data is abstract class 
	// also we don't know if it's only Data and not Integer, Decimal //so we make clone 
	for (size_t i = 0; i < currSize; i++)
	{
		if (i == tableIndex)
		{
			Data* copy = data.clone(); //exception safety ??
			this->data[i].push_back(copy);
		}
		else
		{
			Data* empty = data.emptyClone();
			this->data[i].push_back(empty);
		}
	}

}

void Table::insertType(const Data* data)
{
	currSize++;
	for (size_t i = 0; i < currSize; i++)
	{
		Data* empty = data->emptyClone();
		this->data[i].push_back(empty);
	}
}
void Table::insertType(Data&& data)
{
	for (size_t i = 0; i < currSize; i++)
	{
		Data* empty = data.emptyClone();
		this->data[i].push_back(empty);
	}
}
*/
void Table::print()
{
	printRows(0, this->data.size());
}

void Table::print(int rpn)
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

void Table::printRows(int start, int end)
{
	printTypes();
	for (size_t i = start; i < end; i++)
	{
		//printing the index of the row
		std::cout << i << "  "; //better spacing way
		
		//printing row values
		int columsCount = data[i].size();
		for (size_t c = 0; c < columsCount; c++)
		{
			std::cout << data[i][c]->getData() << "   "; //couldnt the data prints outself without returning string thats uneccesary copy
		}
		std::cout << std::endl;
	}
}
void Table::printTypes()
{
	std::cout << "   "; //better way for spacing
	int columsCount = data[0].size();
	for (size_t c = 0; c < columsCount; c++)
	{
		std::cout << data[0][c]->getName() << "   ";
	}
	std::cout << std::endl;
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
