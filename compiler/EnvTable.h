#pragma once
#include "headerInclude.h"
class EnvTable
{
public:
	class envTableItem
	{
	protected:
		int size;			// 分配的长度
		int addr;			// 偏移量
		int kind;			// 变量种属
		std::string type;	// 变量类型
		std::string val;	// 值
	public:
		envTableItem() {
			size = addr = 0;
			kind = KINDNULL;
		}
	};
	EnvTable();
	~EnvTable();
	// 添加表项
	void createItem(std::pair<int, std::string>);
private:
	std::map<std::pair<int, std::string>, EnvTable::envTableItem> Table;
public:
	// 查找表项并返回找到的数据
	EnvTable::envTableItem findEnvItem(std::pair<int, std::string> input);
};

