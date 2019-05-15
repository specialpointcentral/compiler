#pragma once
#include "headerInclude.h"
class EnvTable
{
public:
	class envTableItem
	{
	public:
		int size;			// 分配的长度
		int addr;			// 偏移量
		int kind;			// 变量种属
		std::string type;	// 变量类型
		std::string val;	// 值
		envTableItem() {
			size = addr = 0;
			kind = KINDNULL;
		}
	};
	EnvTable();
	~EnvTable();
	// 添加表项
	void createItem(std::pair<int, std::string>);
	std::map<std::pair<int, std::string>, EnvTable::envTableItem> Table;
	// 查找表项并返回找到的数据
	EnvTable::envTableItem findEnvItem(std::pair<int, std::string> input);
	// 设置offset的值
	void setOffset(int);
	// 获取offset值
	int getOffset();
	// 声明语句enter
	bool enter(std::pair<int,std::string>,std::string,int);
private:
	int offset = 0;
};

