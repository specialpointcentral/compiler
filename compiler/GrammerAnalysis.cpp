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


// ��ʼ�﷨����
void GrammerAnalysis::beginAnalysis()
{
	while (1) {
		std::pair<int, std::string> posLex = this->tokenList->getNextTokne();
		// ��������������﷨�����м���
		// KEYWORDS ����
		// INT10 ������
		// ID ������
		// OP ����
		// END һ��
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
			// ͨ��
			std::cout << "Grammer Analysis Complete!" << std::endl;
			return;
		}
		else  if (action[0] == 's') {
			// �������
			this->stauts.push(nextStep);
			this->sym.push(posLex);
			// ָ�����
			if (!this->tokenList->posNext()) {
				// TODO error
				std::cout << "error!";
				return;
			}
		}
		else if (action[0] == 'r') {
			// ��Լ����
			AnalysisTable::GramRule gramrule = analysisTable->realGram[nextStep];
			for (int i = 0; i < gramrule.right.size(); ++i) {
				// ȫ����ջ
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
			// ��ѹջ
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


