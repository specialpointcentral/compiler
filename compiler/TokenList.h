#pragma once
#include "headerInclude.h"

class TokenList
{
public:
	std::vector<std::pair<int, std::string>> tokenList;
	int pos;
	TokenList();
	~TokenList();
	
	// 增加Token
	void Toke(int, std::string);

	// 得到下一个Token
	std::pair<int, std::string> getNextTokne();
	// pos下移
	bool posNext();
};

