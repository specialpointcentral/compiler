#pragma once
#include "headerInclude.h"

class TokenList
{
public:
	std::vector<std::pair<int, std::string>> tokenList;
	TokenList();
	~TokenList();
	
	// ����Token
	void Toke(int, std::string);

};

