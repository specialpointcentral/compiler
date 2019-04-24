#include "AnalysisTable.h"



AnalysisTable::AnalysisTable()
{
}


AnalysisTable::~AnalysisTable()
{
}


std::set<AnalysisTable::statusGram> AnalysisTable::closure(std::set<AnalysisTable::statusGram> input)
{
	std::set<AnalysisTable::statusGram> J(input);
	int inputFlag = false;
	do {
		// J 中的每个项
		for (auto J_it = J.begin(); J_it != J.end(); ++J_it) {
			std::pair<int, std::string> nextLex = J_it->gramRule.right[J_it->status];
			if (nextLex.first == BODER) {
				// 是非终结符，准备加入其它部分
				for (int j = 0; j < realGram.size(); ++j) {
					// 找到加入的东西
					if (realGram[j].left == nextLex) {
						// 可能可以加入
						if (J.count(statusGram(0, realGram[j])) == 0) {
							// 加入
							inputFlag = true;
							J.insert(statusGram(0, realGram[j]));
						}
					}
				}
			}
		}
	} while (inputFlag);
	return J;
}


std::set<AnalysisTable::statusGram> AnalysisTable::GOTO(std::set<AnalysisTable::statusGram> I, std::pair<int, std::string> X)
{
	std::set<AnalysisTable::statusGram> J;
	for (auto I_it = I.begin(); I_it != I.end(); I_it++)
	{
		// 
		if (I_it->gramRule.right[I_it->status] == X || //针对INT10和ID
			((I_it->gramRule.right[I_it->status].first == ID || I_it->gramRule.right[I_it->status].first == INT10) &&
				I_it->gramRule.right[I_it->status].first == X.first)) {
			// 加入集族
			AnalysisTable::statusGram tmp = *I_it;
			tmp.status++;
			J.insert(tmp);
		}
	}
	return AnalysisTable::closure(J);
}


// 填充table
void AnalysisTable::insertTable()
{
	// 不首先使用项集族
	// 第一步，创造0项集
	item set0;
	set0.status = 0;
	AnalysisTable::GramRule tmp;
	tmp.left.first = BODER;
	tmp.left.second = "S'";
	tmp.right.push_back(std::pair<int, std::string>(BODER, "S"));
	std::set<AnalysisTable::statusGram> tmps;
	tmps.insert(AnalysisTable::statusGram(0, AnalysisTable::GramRule(tmp)));
	set0.grams = closure(tmps);
	AnalysisTable::itemSet.insert(set0);
	// 开始逐步分析
	bool flag = false;
	do {
		// 对所有的项集分析
		for (auto C_it = AnalysisTable::itemSet.begin(); C_it != AnalysisTable::itemSet.end(); ++C_it) {
			// 项集里每个文法的后一个元素
			for (auto X_it = C_it->grams.begin(); X_it != C_it->grams.end(); ++X_it) {
				if (X_it->gramRule.right.size() <= X_it->status) {
					// x->x.
					if (X_it->gramRule.right[X_it->gramRule.right.size() - 1].second == "S") {
						// S'->S.
					}
					else {
						// x->x.
					}
				}
				else {
					// x->xxx.xxx
					std::pair<int, std::string> nextPos = X_it->gramRule.right[X_it->status];
					if (nextPos.first == BODER) {
						// x->xx.Xxx
					}
					else {
						// x->xx.xx
					}
				}

			}
		}

	} while (flag);
}
