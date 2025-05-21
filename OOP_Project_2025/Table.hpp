#pragma once 
#include "Data.hpp"

//encapsulation
class Table {
public:
	
	//Serialization, Deserialization
private:
	/*class Row {
	public:
		//BIG4/6
	private:
		Data** row;
	};*/
	char* name;
};

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
	int size;
	int cap;
	Data** row = nullptr;
};