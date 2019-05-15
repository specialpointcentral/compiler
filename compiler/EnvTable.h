#pragma once
#include "headerInclude.h"
class EnvTable
{
public:
	class envTableItem
	{
	public:
		int size;			// ����ĳ���
		int addr;			// ƫ����
		int kind;			// ��������
		std::string type;	// ��������
		std::string val;	// ֵ
		envTableItem() {
			size = addr = 0;
			kind = KINDNULL;
		}
	};
	EnvTable();
	~EnvTable();
	// ��ӱ���
	void createItem(std::pair<int, std::string>);
	std::map<std::pair<int, std::string>, EnvTable::envTableItem> Table;
	// ���ұ�������ҵ�������
	EnvTable::envTableItem findEnvItem(std::pair<int, std::string> input);
	// ����offset��ֵ
	void setOffset(int);
	// ��ȡoffsetֵ
	int getOffset();
	// �������enter
	bool enter(std::pair<int,std::string>,std::string,int);
private:
	int offset = 0;
};

