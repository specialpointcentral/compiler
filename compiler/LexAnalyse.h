#pragma once
#include "headerInclude.h"
#include "TokenList.h"

class LexAnalyse
{
public:
	LexAnalyse(std::vector<std::string>);
	~LexAnalyse();
	// �ʷ���������
	bool lexAnalysic();
private:
	struct errors
	{
		std::string line;
		int begin, end, lines;
	};
	std::vector<std::string> op = { "+","-","*","/",">","<","=","(",")",";","'","==",">=","<=","!=" };
	std::vector<std::string> keywords = { "int","if","then","else","while","do" };
	std::vector<std::string> inputLex;
	std::vector<struct errors> errorStack;
	TokenList tokenLists;
	// �Ƿ�����ĸ
	bool isLetter(char);
	// �Ƿ�������
	bool isNumber(char);
	// �ж��Ƿ���OP
	bool isOp(std::string);
	bool isOp(char);
	// �Ƿ��ǹؼ���
	bool isKeyword(std::string);
public:

	// �õ�LexToken��
	std::vector<std::pair<int, std::string>> getTokenTable();
private:
	// �������error
	void error(std::string, int, int, int);
};

