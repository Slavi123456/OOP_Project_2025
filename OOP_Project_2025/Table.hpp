#pragma once 
#include "Data.hpp"
#include <string>
#include <vector>

//encapsulation
class Table {
public:
	Table();
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
	void addLine(const std::vector<Data*>& row); 
	void print();
	void print(int rpn);
	void printTypes();


private:
	void printRows(int start, int end);
	int nextCappacityForVector(int currCap) const;
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