#pragma once 
#include "Table.hpp"

class Database {
private:
	std::string filePath;
	std::vector<Table> tables;
	//is it better to have another variable for the tables size or should i just call it every it thorugh tables.size();
public:
	//Database() = default;
	Database(const std::string& filePath);

	void setFilePath(const std::string& filePath);

	////////===functionality===////////
	void addTable(const Table& newTable);
	void showTables(); //printing the names of the table
	void describe(const std::string& tableName)const;

	//is there a way to make them in one //with default ?
	void printAllTables(); 
	void print(const std::string& tableName); 
	void print(const std::string& tableName, int rpn);

	void exportTable(const std::string& tableName, const std::string& filePath);
	void select(unsigned columnN, const Data* value, const std::string& tableName);
	void modify(unsigned columnN, const std::string& newType, const std::string& tableName);
	void addColumn(const std::string& columnName, const Data* value, const std::string& tableName);
	void update(unsigned searchColumnN, const Data* searchValue, unsigned targetColumn, const Data* targetValue, const std::string& tableName);
	void deleteTableRows(unsigned searchColumnN, const Data* searchValue, const std::string& tableName);
	
	void insert(const std::vector<Data*>& row, const std::string& tableName);
	
	void save();
	void saveAs(const std::string& filePath);
	void load();
	void load(const std::string& filePath);
	////////===functionality===////////
private:
	int getIndexOfTable(const std::string& name) const; //returns -1 if its doesn't exist
};