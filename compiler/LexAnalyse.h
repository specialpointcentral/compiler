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
	// 词法分析函数
	bool lexAnalysic();
private:
	std::vector<std::string> op = { "+","-","*","/",">","<","=","(",")",";","'","==",">=","<=","!=" };
	std::vector<std::string> keywords = { "int","if","then","else","while","do" };
	std::vector<std::string> inputLex;
	std::vector<LexAnalyse::errors> errorStack;
	TokenList *tokenList;
	std::ofstream *outf;
	// 是否是字母
	bool isLetter(char);
	// 是否是数字
	bool isNumber(char);
	// 判断是否是OP
	bool isOp(std::string);
	bool isOp(char);
	// 是否是关键字
	bool isKeyword(std::string);
public:
	// 得到LexToken表
	std::vector<std::pair<int, std::string>> getTokenTable();
private:
	// 处理分析error
	void error(std::string, int, int, int);
public:
	// 设置TokenList
	void setTokenList(TokenList*);
	// 判断是否有错误需要处理
	bool hasError();
	// 获取错误数据
	std::vector<LexAnalyse::errors> getError();
};

