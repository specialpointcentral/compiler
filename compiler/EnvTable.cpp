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
	if (this->Table.find(input) == this->Table.end())
		this->Table[input] = EnvTable::envTableItem();
}


// ���ұ�������ҵ�������
EnvTable::envTableItem EnvTable::findEnvItem(std::pair<int, std::string> input)
{
	return this->Table[input];
}
