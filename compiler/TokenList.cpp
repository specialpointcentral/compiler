#include "TokenList.h"


TokenList::TokenList()
{
	pos = 0;
}

TokenList::~TokenList()
{
}


// ����Token
void TokenList::Toke(int type,std::string value="")
{
	std::pair<int, std::string> token;
	token.first = type;
	token.second = value;
	tokenList.push_back(token);
}



// �õ���һ��Token
std::pair<int, std::string> TokenList::getNextTokne()
{
	if (pos < tokenList.size()) {
		return tokenList[pos];
	}
	else
		return std::pair<int, std::string>(END,"$");
}
// pos���ƣ�Խ�緵��false
bool TokenList::posNext() {
	this->pos++;
	return (pos <= tokenList.size());
}