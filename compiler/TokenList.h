#pragma once
#include "headerInclude.h"

class TokenList
{
public:
	std::vector<std::pair<int, std::string>> tokenList;
	int pos;
	TokenList();
	~TokenList();
	
	// ����Token
	void Toke(int, std::string);

	// �õ���һ��Token
	std::pair<int, std::string> getNextTokne();
	// pos����
	bool posNext();
};

