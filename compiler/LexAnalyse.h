#pragma once
#include "headerInclude.h"
#include "TokenList.h"

class LexAnalyse
{
public:
	class errors
	{
	public:
		std::string line;
		int begin, end, lines;
	};
	LexAnalyse(std::vector<std::string>,std::ofstream *);
	~LexAnalyse();
	// �ʷ���������
	bool lexAnalysic();
private:
	std::vector<std::string> op = { "+","-","*","/",">","<","=","(",")",";","'","==",">=","<=","!=" };
	std::vector<std::string> keywords = { "int","if","then","else","while","do" };
	std::vector<std::string> inputLex;
	std::vector<LexAnalyse::errors> errorStack;
	TokenList *tokenList;
	std::ofstream *outf;
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
public:
	// ����TokenList
	void setTokenList(TokenList*);
	// �ж��Ƿ��д�����Ҫ����
	bool hasError();
	// ��ȡ��������
	std::vector<LexAnalyse::errors> getError();
};

