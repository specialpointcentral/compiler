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
		// J 中的每个项
		for (auto J_it = J.begin(); J_it != J.end(); ++J_it) {
			if (J_it->gramRule.right.size() == J_it->status) continue;
			std::pair<int, std::string> nextLex = J_it->gramRule.right[J_it->status];
			if (nextLex.first == BODER) {
				// 是非终结符，准备加入其它部分
				for (int j = 0; j < realGram.size(); ++j) {
					// 找到加入的东西
					if (realGram[j].left == nextLex) {
						// 可能可以加入
						if (J.find(statusGram(0, realGram[j])) == J.end()) {
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
		// x->x.
		if (I_it->gramRule.right.size() <= I_it->status) continue;
		// else
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
	tmp.left.second = std::string(BEGINITEM).append("'");
	tmp.right.push_back(std::pair<int, std::string>(BODER, BEGINITEM));
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
				// 对于空串，和规约项
				if (X_it->gramRule.right.size() <= X_it->status || (X_it->gramRule.right.size() == 1 && X_it->gramRule.right[0].first == EMPTY)) {
					// x->x.
					if (X_it->gramRule.right[X_it->gramRule.right.size() - 1].second == BEGINITEM) {
						// S'->S.
						setAction("acc", C_it->status, std::pair<int, std::string>(END, "$"));
					}
					else {
						// x->x. SLR分析法
						// 执行归约操作
						auto followSet = AnalysisTable::FOLLOW(X_it->gramRule.left);
						int index;
						for (auto itor = realGram.begin(); itor != realGram.end(); ++itor) {
							if (itor->second == X_it->gramRule) {
								index = itor->first;
								break;
							}
						}
						std::stringstream ss;
						ss << "r" << index;
						std::string tmp;
						ss >> tmp;
						// 所有的放进去
						for (auto it = followSet.begin(); it != followSet.end(); ++it) {
							AnalysisTable::setAction(tmp, C_it->status, *it);
						}
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
	this->printToFile();
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

// 返回first集合
std::set<std::pair<int, std::string>> AnalysisTable::FIRST(const std::pair<int, std::string> &input)
{
	if (input.first != BODER) {
		// 终结符
		std::set<std::pair<int, std::string>> first;
		first.insert(input);
		return first;
	}
	else {
		if (this->FIRSTSet.size() != 0) {
			// 说明已经构建过了
			return this->FIRSTSet[input];
		}
		int before, next;
		do {
			before = 0;
			for (auto i = FIRSTSet.begin(); i != FIRSTSet.end(); ++i) {
				before += i->second.size();
			}
			// 外层整个语法遍历
			for (auto it = realGram.begin(); it != realGram.end(); ++it) {
				// 内层进行遍历
				std::pair<int, std::string> left = it->second.left;
				std::pair<int, std::string> right = it->second.right[0];
				if (right.first == BODER) {
					// 查找里面
					for (auto p = it->second.right.begin(); p != it->second.right.end(); ++p) {
						// 是非终结符，加入
						auto tmp = FIRSTSet[right];
						// 去除空
						FIRSTSet[left].erase(std::pair<int, std::string>(EMPTY, ""));
						FIRSTSet[left].insert(tmp.begin(), tmp.end());
						// 有空串
						if (FIRSTSet[right].find(std::pair<int, std::string>(EMPTY, "")) != FIRSTSet[right].end()) {
							// 是最后一个
							if (p + 1 == it->second.right.end()) {
								// 加入空串
								FIRSTSet[right].insert(std::pair<int, std::string>(EMPTY, ""));
							}
						}
						else break;
					}
				}
				else {
					// 终结符加入
					FIRSTSet[left].insert(right);
				}
			}
			next = 0;
			for (auto i = FIRSTSet.begin(); i != FIRSTSet.end(); ++i) {
				next += i->second.size();
			}
		} while (before != next);
	}
	// 找first集合
	return FIRSTSet[input];
}
std::set<std::pair<int, std::string>> AnalysisTable::FIRST(const std::vector<std::pair<int, std::string>> &input) {
	std::set<std::pair<int, std::string>> tmp;
	for (auto it = input.begin(); it != input.end(); ++it) {
		// 此时是不是终结符
		if (it->first != BODER) {
			tmp.insert(*it);
			break;
		}
		// 最后一个
		std::set<std::pair<int, std::string>> p = FIRST(*it);
		if (it + 1 == input.end()) {
			tmp.insert(p.begin(), p.end());
		}
		else {
			if (p.find(std::pair<int, std::string>(EMPTY, "")) != p.end()) {
				// 有空串
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

// 返回follow集合
std::set<std::pair<int, std::string>> AnalysisTable::FOLLOW(const std::pair<int, std::string> &input)
{
	if (this->FOLLOWSet.size() != 0) {
		// 说明已经构建过了
		return this->FOLLOWSet[input];
	}
	// 加入$
	FOLLOWSet[std::pair<int, std::string>(BODER, BEGINITEM)].insert(std::pair<int, std::string>(END, "$"));
	int before, next;
	do {
		before = 0;
		for (auto i = FOLLOWSet.begin(); i != FOLLOWSet.end(); ++i) {
			before += i->second.size();
		}
		// 外层整个语法遍历
		for (auto it = realGram.begin(); it != realGram.end(); ++it) {
			// 内部一层遍历所有右边变量
			for (auto p = it->second.right.begin(); p != it->second.right.end(); ++p) {
				if (p->first != BODER) continue;
				// p代表了p的follow
				bool hasEmpty = false;
				if (p + 1 != it->second.right.end()) {	// 不是最后一个
					std::set<std::pair<int, std::string>> first = this->FIRST(std::vector<std::pair<int, std::string>>(p + 1, it->second.right.end()));
					if (hasEmpty = (first.find(std::pair<int, std::string>(EMPTY, "")) != first.end())) {
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

	return this->FOLLOWSet[input];
}


// 设置语法分析表
void AnalysisTable::setRealGram(const std::vector<std::pair<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>>> &input, std::ofstream *outf)
{
	for (int i = 0; i < input.size(); ++i) {
		this->realGram[i] = AnalysisTable::GramRule(input[i].first, input[i].second);
	}
	this->outf = outf;
}



// 文件输出
void AnalysisTable::printToFile()
{
	// 输出first
	*outf << "### Grammar Analysis" << std::endl;
	*outf << "#### First Table" << std::endl;
	*outf << "| First |  |" << std::endl;
	*outf << "|---|---|" << std::endl;
	for (auto it = this->FIRSTSet.begin(); it != this->FIRSTSet.end(); ++it) {
		*outf << "| < " << it->first.first << " , " << it->first.second << " > |";
		for (auto p = it->second.begin(); p != it->second.end(); ++p) {
			*outf << " < " << p->first << ", " << p->second << " >";
		}
		*outf << " |" << std::endl;
	}
	// 输出follow
	*outf << "#### Follow Table" << std::endl;
	*outf << "| Follow |  |" << std::endl;
	*outf << "|---|---|" << std::endl;
	for (auto it = this->FOLLOWSet.begin(); it != this->FOLLOWSet.end(); ++it) {
		*outf << "| < " << it->first.first << " , " << it->first.second << " > |";
		for (auto p = it->second.begin(); p != it->second.end(); ++p) {
			*outf << " < " << p->first << ", " << p->second << " >";
		}
		*outf << " |" << std::endl;
	}
	// 输出原始的语法
	*outf << "#### Grammar Table" << std::endl;
	*outf << "| # | Left | Right |" << std::endl;
	*outf << "|---|---|---|" << std::endl;
	for (auto it = this->realGram.begin(); it != this->realGram.end(); ++it) {
		*outf << "| " << it->first << " | < " << it->second.left.first << " , " << it->second.left.second << " > |";
		for (auto p = it->second.right.begin(); p != it->second.right.end(); ++p) {
			*outf << " < " << p->first << ", " << p->second << " >";
		}
		*outf << " |" << std::endl;
	}
	// 输出状态转换
	*outf << "#### Transfer Machine" << std::endl;
	for (auto s = this->itemSet.begin(); s != this->itemSet.end(); ++s) {
		*outf << "| Status:" << s->status << " | Left | Right |" << std::endl;
		*outf << "|---|---|---|" << std::endl;
		for (auto it = s->grams.begin(); it != s->grams.end(); ++it) {
			*outf << "| " << it->status << " | < " << it->gramRule.left.first << " , " << it->gramRule.left.second << " > |";
			int count = 0;	// 位置定位
			for (auto p = it->gramRule.right.begin(); p != it->gramRule.right.end(); ++p) {
				if (count == it->status) *outf << ".";
				*outf << " < " << p->first << ", " << p->second << " >";
				++count;
			}
			if (count == it->status) *outf << ".";
			*outf << " |" << std::endl;
		}
		*outf << std::endl;
	}

	// 输出状态表
	*outf << "#### Transfer Table" << std::endl;
	// 统计所有状态
	std::set<std::pair<int, std::string>> t_action, t_goto;
	for (auto p = this->Table.begin(); p != this->Table.end(); ++p) {
		for (auto it = p->second.t_action.actionMap.begin(); it != p->second.t_action.actionMap.end(); ++it) {
			t_action.insert(it->first);
		}
		for (auto it = p->second.t_goto.gotoMap.begin(); it != p->second.t_goto.gotoMap.end(); ++it) {
			t_goto.insert(it->first);
		}
	}
	*outf << "<table>" << std::endl;
	// 输出表头
	*outf << "<tr>" << std::endl
		<< "<th rowspan=\"2\"> # </th>" << std::endl
		<< "<th colspan=\"" << t_action.size() << "\">ACTION</th>" << std::endl
		<< "<th colspan=\"" << t_goto.size() << "\">GOTO</th>" << std::endl
		<< "</tr>" << std::endl
		<< "<tr>" << std::endl;
	for (auto it = t_action.begin(); it != t_action.end(); ++it) {
		*outf << "<th>< " << it->first << " , " << it->second << " ></th>" << std::endl;
	}
	for (auto it = t_goto.begin(); it != t_goto.end(); ++it) {
		*outf << "<th>< " << it->first << " , " << it->second << " ></th>" << std::endl;
	}
	*outf << "</tr>" << std::endl;
	// 按行输出
	for (auto p = this->Table.begin(); p != this->Table.end(); ++p) {
		*outf << "<tr>" << std::endl;
		*outf << "<td>" << p->first << "</td>" << std::endl;
		for (auto it = t_action.begin(); it != t_action.end(); ++it) {
			auto s = p->second.t_action.actionMap.find(*it);
			if (s != p->second.t_action.actionMap.end())
				*outf << "<td> " << s->second << " </td>" << std::endl;
			else
				*outf << "<td> </td>" << std::endl;
		}
		for (auto it = t_goto.begin(); it != t_goto.end(); ++it) {
			auto s = p->second.t_goto.gotoMap.find(*it);
			if(s != p->second.t_goto.gotoMap.end())
				*outf << "<td> " << s->second << " </td>" << std::endl;
			else
				*outf << "<td> </td>" << std::endl;
		}
		*outf << "</tr>" << std::endl;
	}

	*outf << "</table>" << std::endl;
}