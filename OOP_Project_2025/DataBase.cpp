#include "DataBase.hpp"
#include <fstream>

Database::Database(const std::string& filePath)
{
	this->filePath = filePath;
}

void Database::setFilePath(const std::string& filePath)
{
	if (filePath.empty())
	{
		throw "Cannot initialize file path with empty string";
	}
	this->filePath = filePath;
}

////////===functionality===////////
void Database::addTable(const Table& newTable)
{
	if (getIndexOfTable(newTable.getName()) != -1)
	{
		throw "There is already table with this name in the data base";
	}
	Table copy(newTable);
	this->tables.push_back(copy); //it may be better to be with std::move(copy)
}
void Database::showTables()
{
	int countTables = this->tables.size();

	std::cout << "Data base currently has tables with names: " << std::endl;
	for (size_t i = 0; i < countTables; i++)
	{
		std::cout << i << " " << this->tables[i].getName() << std::endl;
	}
}
void Database::describe(const std::string& tableName) const
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}
	std::cout << std::endl << "Database's table with name " << tableName << " have types: " << std::endl;
	tables[indexOfTable].printTypes(std::cout);
	std::cout << std::endl;
}
void Database::printAllTables()
{
	std::cout << std::endl << "Database's table has these tables: " << std::endl;
	
	int countTables = this->tables.size();
	for (size_t i = 0; i < countTables; i++)
	{
		this->tables[i].print();
	}
	std::cout << std::endl;

}
void Database::print(const std::string& tableName)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}
	std::cout << std::endl << "Database's table with name " << tableName << " is: " << std::endl;
	tables[indexOfTable].print();
	std::cout << std::endl;

}
void Database::print(const std::string& tableName, int rpn)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}
	std::cout << std::endl << "Database's table with name " << tableName << " is: " << std::endl;
	tables[indexOfTable].print(rpn);
	std::cout << std::endl;

}

void Database::exportTable(const std::string& tableName, const std::string& filePath)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}
	std::ofstream ost(filePath); //should it be ostream?
	if (!ost.is_open())
	{
		throw "The file couldn't be open";
	}
	tables[indexOfTable].writeToStream(ost); //it can throw
	std::cout << std::endl;
}

void Database::select(unsigned columnN,const Data* value, const std::string& tableName)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}
	
	tables[indexOfTable].select(columnN,value);
	std::cout << std::endl;
}
void Database::modify(unsigned columnN, const std::string& newType, const std::string& tableName)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}

	tables[indexOfTable].modify(columnN, newType);
	std::cout << std::endl;
}
void Database::addColumn(const std::string& columnName, const Data* value, const std::string& tableName)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}

	tables[indexOfTable].addColumn(value); //should be add the columnName
	std::cout << std::endl;
}
void Database::update(unsigned searchColumnN, const Data* searchValue, unsigned targetColumn, const Data* targetValue, const std::string& tableName)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}

	tables[indexOfTable].update(searchColumnN, searchValue, targetColumn, targetValue);
	std::cout << std::endl;
}
void Database::deleteTableRows(unsigned searchColumnN, const Data* searchValue, const std::string& tableName)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		throw "There is no existing table with that name. To create a table use insert";
	}

	tables[indexOfTable].deleteSelectedRows(searchColumnN, searchValue);
	std::cout << std::endl;
}
void Database::insert(const std::vector<Data*>& row, const std::string& tableName)
{
	int indexOfTable = getIndexOfTable(tableName);
	if (indexOfTable == -1)
	{
		std::cout << "Creating table with name: " << tableName << std::endl;
		Table newTb(tableName);
		newTb.addLine(row);
		addTable(newTb);
		return;
	}
	tables[indexOfTable].addLine(row);
	std::cout << std::endl;
}

void Database::save()
{
	saveAs(this->filePath);
}
void Database::saveAs(const std::string& filePath)
{
	if (filePath.empty())
	{
		throw "cannot save on empty filePath";
	}
	std::ofstream ofs(filePath);
	if (!ofs.is_open())
	{
		throw "Couldn't save the database";
	}
	int countTables = this->tables.size();
	ofs << countTables << std::endl;
	for (size_t i = 0; i < countTables; i++)
	{
		this->tables[i].writeToStream(ofs);
	}
}

void Database::load()
{
	load(this->filePath);
}
void Database::load(const std::string& filePath)
{
	if (filePath.empty())
	{
		throw "Cannot load database on empty filePath";
	}
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
	{
		throw "Couldn't load the database";
	}
	std::vector<Table> copy;
	int countTables;
	try
	{
		ifs >> countTables;
		for (size_t i = 0; i < countTables; i++)
		{
			Table newTb("");
			newTb.readFromStream(ifs);
			copy.push_back(std::move(newTb));
		}

		this->tables = std::move(copy);
	}
	catch (...)
	{
		throw "Failed to load the database";
	}
}

////////===helper functions===////////
int Database::getIndexOfTable(const std::string& name) const
{
	int countTables = this->tables.size();

	for (size_t i = 0; i < countTables; i++)
	{
		if (name == this->tables[i].getName()) return i;
	}
	return -1;
}
