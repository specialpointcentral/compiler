#include "GrammerAnalysis.h"



GrammerAnalysis::GrammerAnalysis(TokenList *tokenList, AnalysisTable *analysisTable)
{
	this->stauts.push(0);
	this->sym.push(std::pair<int, std::string>(END, "$"));
	this->tokenList = tokenList;
	this->analysisTable = analysisTable;
}


GrammerAnalysis::~GrammerAnalysis()
{
}


// 开始语法分析
void GrammerAnalysis::beginAnalysis()
{
	while (1) {
		std::pair<int, std::string> posLex = this->tokenList->getNextTokne();
		// 进入分析，按照语法，会有几类
		// KEYWORDS 区分
		// INT10 不区分
		// ID 不区分
		// OP 区分
		// END 一种
		if (posLex.first == INT10 || posLex.first == ID) {
			// save string
			std::string value = posLex.second;
			posLex.second = "";
		}
		std::string action = analysisTable->Table[this->stauts.top()].t_action.actionMap[posLex];
		int nextStep;
		if (action.size() == 0) {
			// TODO error
			std::cout << "error!";
			return;
		}
		std::stringstream ss;
		ss << action.substr(1);
		ss >> nextStep;
		if (action == "acc") {
			// 通过
			std::cout << "Grammer Analysis Complete!" << std::endl;
			return;
		}
		else  if (action[0] == 's') {
			// 移入操作
			this->stauts.push(nextStep);
			this->sym.push(posLex);
			// 指针后移
			if (!this->tokenList->posNext()) {
				// TODO error
				std::cout << "error!";
				return;
			}
		}
		else if (action[0] == 'r') {
			// 归约操作
			AnalysisTable::GramRule gramrule = analysisTable->realGram[nextStep];
			for (int i = 0; i < gramrule.right.size(); ++i) {
				// 全部出栈
				if (!this->stauts.empty() && !this->sym.empty()) {
					this->stauts.pop();
					this->sym.pop();
				}
				else {
					// TODO error
					std::cout << "error!";
					return;
				}
				
			}
			// 左部压栈
			this->sym.push(gramrule.left);
			// GOTO
			this->stauts.push(analysisTable->Table[this->stauts.top()].t_goto.gotoMap[gramrule.left]);
		}
		else {
			// TODO error
			std::cout << "error!";
			return;
		}
	}
}


