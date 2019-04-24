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
		// J �е�ÿ����
		for (auto J_it = J.begin(); J_it != J.end(); ++J_it) {
			std::pair<int, std::string> nextLex = J_it->gramRule.right[J_it->status];
			if (nextLex.first == BODER) {
				// �Ƿ��ս����׼��������������
				for (int j = 0; j < realGram.size(); ++j) {
					// �ҵ�����Ķ���
					if (realGram[j].left == nextLex) {
						// ���ܿ��Լ���
						if (J.count(statusGram(0, realGram[j])) == 0) {
							// ����
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
		if (I_it->gramRule.right[I_it->status] == X || //���INT10��ID
			((I_it->gramRule.right[I_it->status].first == ID || I_it->gramRule.right[I_it->status].first == INT10) &&
				I_it->gramRule.right[I_it->status].first == X.first)) {
			// ���뼯��
			AnalysisTable::statusGram tmp = *I_it;
			tmp.status++;
			J.insert(tmp);
		}
	}
	return AnalysisTable::closure(J);
}


// ���table
void AnalysisTable::insertTable()
{
	// ������ʹ�����
	// ��һ��������0�
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
	// ��ʼ�𲽷���
	bool flag = false;
	do {
		// �����е������
		for (auto C_it = AnalysisTable::itemSet.begin(); C_it != AnalysisTable::itemSet.end(); ++C_it) {
			// ���ÿ���ķ��ĺ�һ��Ԫ��
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
