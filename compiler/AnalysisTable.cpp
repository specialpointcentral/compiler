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
	int beforeflag;
	do {
		beforeflag = this->itemSet.size();
		// 对所有的项集分析
		for (auto C_it = AnalysisTable::itemSet.begin(); C_it != AnalysisTable::itemSet.end(); ++C_it) {
			// 项集里每个文法的后一个元素
			for (auto X_it = C_it->grams.begin(); X_it != C_it->grams.end(); ++X_it) {
				// 此时的状态 C_it->status;
				if (X_it->gramRule.right.size() <= X_it->status) {
					// x->x.
					if (X_it->gramRule.right[X_it->gramRule.right.size() - 1].second == "S") {
						// S'->S.
						setAction("acc", C_it->status, std::pair<int, std::string>(END, "$")); 
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
						int next = findItem(AnalysisTable::GOTO(C_it->grams, nextPos));
						AnalysisTable::setGOTO(next, C_it->status, nextPos);
					}
					else {
						// x->xx.xx
						int next = findItem(AnalysisTable::GOTO(C_it->grams, nextPos));
						std::string tmp;
						std::stringstream ss;
						ss << "s" << next;
						ss >> tmp;
						AnalysisTable::setAction(tmp, C_it->status, nextPos);
					}
				}

			}
		}

	} while (beforeflag != this->itemSet.size());
	
}
// 设置GOTO表格内容
void AnalysisTable::setGOTO(const int &setT, const int &i, const std::pair<int, std::string> &B)
{
	this->Table[i].t_goto.gotoMap[B] = setT;
}

// 设置Action项目
void AnalysisTable::setAction(const std::string &setT, const int &i, const std::pair<int, std::string> &a)
{
	this->Table[i].t_action.actionMap[a] = setT;
}


// 寻找item项目
int AnalysisTable::findItem(const std::set<AnalysisTable::statusGram> &item)
{
	// 寻找相应的状态
	for (auto it = this->itemSet.begin(); it != this->itemSet.end(); ++it) {
		if (it->grams == item) return it->status;
	}
	// 如果没有则创建
	AnalysisTable::item tmp;
	tmp.status = this->itemSet.size();
	tmp.grams = item;
	this->itemSet.insert(tmp);
	return tmp.status;
}