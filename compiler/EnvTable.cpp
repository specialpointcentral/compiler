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
	if (this->Table.find(input) == this->Table.end()) {
		auto tmp = EnvTable::envTableItem();
		if (input.first == INT10) {
			tmp.kind = KINDINT10;	// 常数
			tmp.val = input.second;
		}
		this->Table[input] = tmp;
	}
		
}


// 查找表项并返回找到的数据
EnvTable::envTableItem EnvTable::findEnvItem(std::pair<int, std::string> input)
{
	return this->Table[input];
}

// 设置offset
void EnvTable::setOffset(int input)
{
	this->offset = input;
}

// 获取offset
int EnvTable::getOffset()
{
	return this->offset;
}

bool EnvTable::enter(std::pair<int,std::string> lex, std::string type, int width)
{
	auto tmp = this->Table.find(lex);
	if (tmp != this->Table.end()) {
		tmp->second.addr = offset;
		tmp->second.size = width;
		tmp->second.type = type;
		this->offset += width;
		if (type == "int" || type == "float")
			tmp->second.kind = KINDSIMID;	// 简变
		return true;
	}
		
	else return false;
}
