#include "TokenList.h"

TokenList::TokenList()
{
	pos = 0;
}

TokenList::~TokenList()
{
}


// 增加Token
void TokenList::Toke(int type,std::string value="")
{
	std::pair<int, std::string> token;
	token.first = type;
	token.second = value;
	tokenList.push_back(token);
}



// 得到下一个Token
std::pair<int, std::string> TokenList::getNextTokne()
{
	if (pos < tokenList.size()) {
		return tokenList[pos];
	}
	else
		return std::pair<int, std::string>(END,"$");
}
// pos下移，越界返回false
bool TokenList::posNext() {
	this->pos++;
	return (pos <= tokenList.size());
}