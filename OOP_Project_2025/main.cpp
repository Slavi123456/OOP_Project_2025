
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

int main()
{
}
