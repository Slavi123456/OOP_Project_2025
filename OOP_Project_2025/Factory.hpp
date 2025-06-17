#pragma once 
#include <string>
#include <vector>

class Data; 

Data* dataFactory(std::string& type,const std::vector<std::string>& value, int& startingInd);

Data* dataFactoryForEmpty(const std::string& type);