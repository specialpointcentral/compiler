#pragma once
#include "headerInclude.h"
#include "TokenList.h"
#include "AnalysisTable.h"
class GrammerAnalysis
{
public:
	GrammerAnalysis(TokenList*, AnalysisTable*);
	~GrammerAnalysis();

	// ��ʼ�﷨����
	void beginAnalysis();
private:
	// stack
	std::stack<int> stauts;
	std::stack<std::pair<int,std::string>> sym;

	TokenList *tokenList;
	AnalysisTable *analysisTable;
};

