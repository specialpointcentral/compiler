#pragma once
#include "headerInclude.h"
#include "TokenList.h"
#include "AnalysisTable.h"
class GrammerAnalysis
{
public:
	GrammerAnalysis(TokenList*, AnalysisTable*);
	~GrammerAnalysis();

	// 开始语法分析
	void beginAnalysis();
private:
	// stack
	std::stack<int> stauts;
	std::stack<std::pair<int,std::string>> sym;

	TokenList *tokenList;
	AnalysisTable *analysisTable;
};

