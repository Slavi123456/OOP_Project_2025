
#include <iostream>
#include "data.hpp"
#include "integer.hpp"
#include "decimal.hpp"
#include "table.hpp"

void testInteger() {
	Integer inte(4);
	std::cout << inte.getName() << " ";
	inte.print();
	std::cout << std::endl;
}
void testDecimal() {
	Decimal dece(6.01);
	std::cout << dece.getName() << " ";
	dece.print();
	std::cout << std::endl;

}
void testDataArr() {
	Decimal dece(6.01);
	Integer inte(4);

	Data** arr = new Data * [2];
	arr[0] = &dece;
	arr[1] = &inte;

	for (size_t i = 0; i < 2; i++)
	{
		std::cout << arr[i]->getName() << " ";
		arr[i]->print();
		std::cout << std::endl;
		//delete arr[i]; NO CANT DELETE variables on the stack
	}
	delete[]arr;

}

void testTableAdd_Print() {
	Table tab;

	Decimal dec(55.89);
	std::vector<Data*> vec;
	vec.push_back(&dec);
	
	tab.addLine(vec);
	tab.print();
}
void testTableAddColumn() {
	Table tab;
	tab.print();

	Decimal dec(55.89);
	
	std::vector<Data*> vec;
	vec.push_back(&dec);
	
	tab.addColumn(&dec);
	tab.print(); //there is a problem if it's empty

	tab.addLine(vec);
	tab.addLine(vec);
	tab.print();

	Integer inte(4);
	tab.addColumn(&inte);

	tab.print();
}
void testTableRPN_Print() {
	Table tab;
	//tab.addData(Decimal(55.89), 0);
	//tab.addData(Integer(4), 1);
	//tab.addData(Integer(), 1);
	Decimal dec(55.89);
	Integer inte;
	Integer inte2(4);

	std::vector<Data*> vec;
	vec.push_back(&dec);
	vec.push_back(&inte);
	vec.push_back(&inte2);

	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);
	tab.addLine(vec);

	tab.print(2);
}
void testTablePrint_Types() {
	Table tab;
	std::cout << "Table types: ";
	tab.printTypes();

	Decimal dec(55.89);
	Integer inte;
	Integer inte2(4);

	std::vector<Data*> vec;
	vec.push_back(&dec);
	vec.push_back(&inte);
	vec.push_back(&inte2);

	tab.addLine(vec);
	
	tab.print();

	std::cout << "Table types: ";
	tab.printTypes();
}
void testTableSelect() {
	Table tab;

	Decimal dec(55.89);
	Decimal dec1(432.5);
	Decimal dec2(4654.5);
	Integer inte1;
	Integer inte2 (1);
	Integer inte3 (2);
	Integer inte4(4);
	Integer inte5(5);

	std::vector<Data*> vec = { &dec, &inte1, &inte2 };
	std::vector<Data*> vec2 = { &dec2, &inte4, &inte5 };
	std::vector<Data*> vec3 = { &dec1, &inte3, &inte2 };
	
	tab.addLine(vec);
	tab.addLine(vec2);
	tab.addLine(vec3);

	tab.print();
	std::cout <<std::endl << "Selection by third column for Integer(1)" <<std::endl;
	tab.select(2, &inte2);

	std::cout << std::endl << "Selection by second column for Null" << std::endl;
	tab.select(1, &inte1);

	std::cout << std::endl << "Selection by third column for Integer(2)" << std::endl;
	tab.select(2, &inte3);
}
void testTableExport() {
	Table tab;

	Decimal dec(55.89);
	Integer inte;
	Integer inte2(4);

	std::vector<Data*> vec = { &dec, &inte, &inte2 };
	tab.addLine(vec);

	tab.writeToStream(std::cout);
}

int main()
{
	//testTablePrint_Types();
	//testTableRPN_Print();
	testTableExport();
}

void reserveVecFunc() {
	std::vector<int> a;
	a.push_back(1);
	std::cout << a.size() << " " << a.capacity() << std::endl;

	a.reserve(8);
	std::cout << a.size() << " " << a.capacity();
	
}
