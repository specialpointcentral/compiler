#include "EnvTable.h"


EnvTable::EnvTable()
{
}


EnvTable::~EnvTable()
{
}


// 添加表项
void EnvTable::createItem(std::pair<int, std::string> input)
{
	if (this->Table.find(input) == this->Table.end())
		this->Table[input] = EnvTable::envTableItem();
}


// 查找表项并返回找到的数据
EnvTable::envTableItem EnvTable::findEnvItem(std::pair<int, std::string> input)
{
	return this->Table[input];
}
