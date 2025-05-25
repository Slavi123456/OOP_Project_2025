#pragma once 
#include "Data.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

constexpr int DEFAULT_SPACING = 3; //does it have to be static to not be seen by other files ?
constexpr int SPACING_FOR_FILES = 1;

static Data* dataFactory(std::string& type, std::string& value);

//encapsulation
class Table {
public:
	Table() = default;
	//Table(int rows,int colums);
	~Table();
	//Serialization, Deserialization
	/*
	void addLine(const Data* data);
	void addLine(Data&& data);

	void addData(const Data* data, int tableIndex);
	void addData(Data&& data, int tableIndex);
	
	void insertType(const Data* data);
	void insertType(Data&& data);
	*/
	void addLine(const std::vector<Data*>& row); //insert types
	void addColumn(const Data* data); //addcolumn
	
	void print() const;
	void print(int rpn) const; //need functionallity like first page ...
	void printTypes(int count = DEFAULT_SPACING, std::ostream& os = std::cout) const; //describe //is it a problem to make so much default values

	void select(unsigned indexColumn, const Data* value); //select
	std::ostream& writeToStream(std::ostream& os) const; //export
private:

	void printRows(int start, int end) const;
	void printSelectedRows(const std::vector<int>& indexRows) const;
	void printRow(int indexRow, std::ostream& os = std::cout) const;
	void printRowData(std::ostream& os,int indexRow, int spacingSize = DEFAULT_SPACING) const;
	
	int nextCappacityForVector(int currCap) const;
	int columnsCount() const;
	int rowsCount() const;
	/*class Row {
	public:
		//BIG4/6
	private:
		Data** row;
	};*/
	std::string name;
	std::vector<std::vector<Data*>> data; //some kind of a system to have already resized the first vector and just add in the second till the limit
	//int currSize; //is it really needed //no if you controll your reserve and make sure to create first vector then push it
};

/*
//can write one dynamic vec which can be used for the container instead of Row
class Row {
public:
	//BIG4/6
	Row() : size(0), cap(0) {}
	Row(const Row& other);
	Row(Row&& other);
	Row& operator=(const Row& other);
	Row& operator=(Row&& other);
	~Row();

	
private:
	void setData(const Data** arr, int size, int cap);
	void swapAllData(const Row& other);
	int size;
	int cap;
	Data** data = nullptr;
};


template<typename T>
class  MyVec {
public: 
	MyVec();
	MyVec(const MyVec& other);
	MyVec(MyVec&& other);
	MyVec<T>& operator=(const MyVec& other);
	MyVec<T>& operator=(MyVec&& other);
	~MyVec();

	//these if needed
	//void setSize(int size);
	//void setCap(int cap);

	int getCappacity() const;
	int getSize() const;

private:
	bool setData(const T* data, const int size, const int cap); //does it have to be const T* const data
	void swapAllData(const MyVec& other);
	int size;
	int cap;
	T* data = nullptr;
};
*/