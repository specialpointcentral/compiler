#include "TokenList.h"


TokenList::TokenList()
{
}

TokenList::~TokenList()
{
}


// Ôö¼ÓToken
void TokenList::Toke(int type,std::string value="")
{
	std::pair<int, std::string> token;
	token.first = type;
	token.second = value;
	tokenList.push_back(token);
}

