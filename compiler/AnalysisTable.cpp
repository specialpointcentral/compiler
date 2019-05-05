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
	int inputFlag;
	do {
		inputFlag = false;
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
	int beforeflag;
	do {
		beforeflag = this->itemSet.size();
		// �����е������
		for (auto C_it = AnalysisTable::itemSet.begin(); C_it != AnalysisTable::itemSet.end(); ++C_it) {
			// ���ÿ���ķ��ĺ�һ��Ԫ��
			for (auto X_it = C_it->grams.begin(); X_it != C_it->grams.end(); ++X_it) {
				// ��ʱ��״̬ C_it->status;
				if (X_it->gramRule.right.size() <= X_it->status) {
					// x->x.
					if (X_it->gramRule.right[X_it->gramRule.right.size() - 1].second == "S") {
						// S'->S.
						setAction("acc", C_it->status, std::pair<int, std::string>(END, "$"));
					}
					else {
						// x->x.
						// TODO
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

// ����GOTO�������
void AnalysisTable::setGOTO(const int &setT, const int &i, const std::pair<int, std::string> &B)
{
	this->Table[i].t_goto.gotoMap[B] = setT;
}

// ����Action��Ŀ
void AnalysisTable::setAction(const std::string &setT, const int &i, const std::pair<int, std::string> &a)
{
	this->Table[i].t_action.actionMap[a] = setT;
}


// Ѱ��item��Ŀ
int AnalysisTable::findItem(const std::set<AnalysisTable::statusGram> &item)
{
	// Ѱ����Ӧ��״̬
	for (auto it = this->itemSet.begin(); it != this->itemSet.end(); ++it) {
		if (it->grams == item) return it->status;
	}
	// ���û���򴴽�
	AnalysisTable::item tmp;
	tmp.status = this->itemSet.size();
	tmp.grams = item;
	this->itemSet.insert(tmp);
	return tmp.status;
}

// ����first����
std::set<std::pair<int, std::string>> AnalysisTable::FIRST(std::pair<int, std::string> input)
{
	if (input.first == BODER) {
		// �ս��
		std::set<std::pair<int, std::string>> first;
		first.insert(input);
		return first;
	}
	else {
		if (this->FIRSTSet.size() != 0) {
			// ˵���Ѿ���������
			return this->FIRSTSet[input];
		}
		int before, next;
		do {
			before = 0;
			for (auto i = FIRSTSet.begin(); i != FIRSTSet.end(); ++i) {
				before += i->second.size();
			}
			// ��������﷨����
			for (auto it = realGram.begin(); it != realGram.end(); ++it) {
				// �ڲ���б���
				std::pair<int, std::string> left = it->second.left;
				std::pair<int, std::string> right = it->second.right[0];
				if (right.first == BODER) {
					// ��������
					for (auto p = it->second.right.begin(); p != it->second.right.end(); ++p) {
						// �Ƿ��ս��������
						FIRSTSet[left].insert(FIRSTSet[right].begin(), FIRSTSet[right].end());
						// ȥ����
						FIRSTSet[left].erase(std::pair<int, std::string>(EMPTY, ""));
						// �пմ�
						if (FIRSTSet[right].find(std::pair<int, std::string>(EMPTY, "")) != FIRSTSet[right].end()) {
							// �����һ��
							if (p + 1 == it->second.right.end()) {
								// ����մ�
								FIRSTSet[right].insert(std::pair<int, std::string>(EMPTY, ""));
							}
						}
						else break;
					}
				}
				else {
					// �ս������
					FIRSTSet[left].insert(right);
				}
			}
			next = 0;
			for (auto i = FIRSTSet.begin(); i != FIRSTSet.end(); ++i) {
				next += i->second.size();
			}
		} while (before != next);
	}
	// ��first����
	return FIRSTSet[input];
}
std::set<std::pair<int, std::string>> AnalysisTable::FIRST(std::vector<std::pair<int, std::string>> input) {
	std::set<std::pair<int, std::string>> tmp;
	for (auto it = input.begin(); it != input.end(); ++it) {
		// ���һ��
		if (it + 1 == input.end()) {
			std::set<std::pair<int, std::string>> p;
			p = FIRST(*it);
			tmp.insert(p.begin(),p.end());
		}
		else {
			std::set<std::pair<int, std::string>> p;
			p = FIRST(*it);
			if (p.count(std::pair<int, std::string>(EMPTY, "")) != 0) {
				// �пմ�
				p.erase(std::pair<int, std::string>(EMPTY, ""));
				tmp.insert(p.begin(), p.end());
			}
			else {
				tmp.insert(p.begin(), p.end());
				break;
			}
		}
	}
	return tmp;
}

// ����follow����
std::set<std::pair<int, std::string>> AnalysisTable::FOLLOW(std::pair<int, std::string> input)
{
	if (input.first == BODER) {
		// �ս��
		std::set<std::pair<int, std::string>> follow;
		follow.insert(input);
		return follow;
	}
	else {
		if (this->FOLLOWSet.size() != 0) {
			// ˵���Ѿ���������
			return this->FOLLOWSet[input];
		}
		// ����$
		FOLLOWSet[std::pair<int, std::string>(BODER, "S")].insert(std::pair<int, std::string>(END, "$"));
		int before, next;
		do {
			before = 0;
			for (auto i = FOLLOWSet.begin(); i != FOLLOWSet.end(); ++i) {
				before += i->second.size();
			}
			// ��������﷨����
			for (auto it = realGram.begin(); it != realGram.end(); ++it) {
				// �ڲ�һ����������ұ߱���
				for (auto p = it->second.right.begin(); p != it->second.right.end(); ++p) {
					// p������p��follow
					bool hasEmpty = false;
					if (p + 1 != it->second.right.end()) {
						std::set<std::pair<int, std::string>> first = this->FIRST(std::vector<std::pair<int, std::string>>(p + 1, it->second.right.end()));
						if (hasEmpty = (bool)first.count(std::pair<int, std::string>(EMPTY, ""))) {
							first.erase(std::pair<int, std::string>(EMPTY, ""));
						}
						FOLLOWSet[*p].insert(first.begin(), first.end());
					}
					if (p + 1 == it->second.right.end() || hasEmpty) {
						FOLLOWSet[*p].insert(FOLLOWSet[it->second.left].begin(), FOLLOWSet[it->second.left].end());
					}
				}
			}
			next = 0;
			for (auto i = FOLLOWSet.begin(); i != FOLLOWSet.end(); ++i) {
				next += i->second.size();
			}
		} while (before != next);
	}
	return std::set<std::pair<int, std::string>>();
}
