
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
	//tab.insertType(Decimal(55.89));
	//tab.addData(Decimal(55.89), 0);
	//tab.addData(Integer(4), 1);
	//tab.addData(Integer(), 1);
	tab.print();
}
void testTableRPN_Print() {
	Table tab;
	//tab.addData(Decimal(55.89), 0);
	//tab.addData(Integer(4), 1);
	//tab.addData(Integer(), 1);
	tab.print(1);
}
int main()
{
	testTableAdd_Print();

}

void reserveVecFunc() {
	std::vector<int> a;
	a.push_back(1);
	std::cout << a.size() << " " << a.capacity() << std::endl;

	a.reserve(8);
	std::cout << a.size() << " " << a.capacity();
	
}
