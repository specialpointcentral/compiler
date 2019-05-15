#include "EnvTable.h"


EnvTable::EnvTable()
{
}


EnvTable::~EnvTable()
{
}


// ��ӱ���
void EnvTable::createItem(std::pair<int, std::string> input)
{
	if (this->Table.find(input) == this->Table.end()) {
		auto tmp = EnvTable::envTableItem();
		if (input.first == INT10) {
			tmp.kind = KINDINT10;	// ����
			tmp.val = input.second;
		}
		this->Table[input] = tmp;
	}
		
}


// ���ұ�������ҵ�������
EnvTable::envTableItem EnvTable::findEnvItem(std::pair<int, std::string> input)
{
	return this->Table[input];
}

// ����offset
void EnvTable::setOffset(int input)
{
	this->offset = input;
}

// ��ȡoffset
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
			tmp->second.kind = KINDSIMID;	// ���
		return true;
	}
		
	else return false;
}
