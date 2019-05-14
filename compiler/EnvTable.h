#pragma once
#include "headerInclude.h"
class EnvTable
{
public:
	class envTableItem
	{
	protected:
		int size;			// ����ĳ���
		int addr;			// ƫ����
		int kind;			// ��������
		std::string type;	// ��������
		std::string val;	// ֵ
	public:
		envTableItem() {
			size = addr = 0;
			kind = KINDNULL;
		}
	};
	EnvTable();
	~EnvTable();
	// ��ӱ���
	void createItem(std::pair<int, std::string>);
private:
	std::map<std::pair<int, std::string>, EnvTable::envTableItem> Table;
public:
	// ���ұ�������ҵ�������
	EnvTable::envTableItem findEnvItem(std::pair<int, std::string> input);
};

