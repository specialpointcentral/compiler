#include "SyntaxAnalysis.h"

SyntaxAnalysis::SyntaxAnalysis(TokenList* tokenList, AnalysisTable* analysisTable, EnvTable* envTable)
{
	this->stauts.push(0);
	this->sym.push(std::pair<int, std::string>(END, "$"));
	this->tokenList = tokenList;
	this->analysisTable = analysisTable;
	this->envTable = envTable;
}


SyntaxAnalysis::~SyntaxAnalysis()
{
}


// 开始语法分析
void SyntaxAnalysis::beginAnalysis()
{
	while (1) {
		std::pair<int, std::string> posLex = this->tokenList->getNextTokne();
		std::string value;	// use to save string
		// 进入分析，按照语法，会有几类
		// KEYWORDS 区分
		// INT10 不区分
		// ID 不区分
		// OP 区分
		// END 一种
		if (posLex.first == INT10 || posLex.first == ID) {
			// save string
			value = posLex.second;
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
			this->printOut();
			std::cout << "Intermediate Code Generation Complete!" << std::endl;
			return;
		}
		else  if (action[0] == 's') {
			// 移入操作
			this->stauts.push(nextStep);
			this->sym.push(posLex);
			if (posLex.first == INT10 || posLex.first == ID) {
				posLex.second = value;	// 恢复数据
			}
			this->records.push_back(SyntaxAnalysis::Record(posLex));
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
			// 执行语义动作
			auto tmp = this->actionList.find(nextStep);
			if (tmp != this->actionList.end()) {
				(this->*tmp->second)();
			}
			// 消除空串影响
			std::size_t psize = (gramrule.right.size() == 1 && gramrule.right[0].first == EMPTY) ? 0 : gramrule.right.size();
			for (std::size_t i = 0; i < psize; ++i) {
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

void SyntaxAnalysis::setActionList(const std::map<int, std::string>& input)
{
	for (auto it = input.begin(); it != input.end(); ++it) {
		SyntaxAnalysis::_CALLBACK callback = &SyntaxAnalysis::ept;
		//TODO 
		if (it->second == "Q1") callback = &SyntaxAnalysis::Q1;
		else if (it->second == "Q2") callback = &SyntaxAnalysis::Q2;
		else if (it->second == "L1") callback = &SyntaxAnalysis::L1;
		else if (it->second == "L2") callback = &SyntaxAnalysis::L2;
		else if (it->second == "S") callback = &SyntaxAnalysis::S;
		else if (it->second == "M") callback = &SyntaxAnalysis::M;
		else if (it->second == "SF") callback = &SyntaxAnalysis::SF;
		else if (it->second == "N") callback = &SyntaxAnalysis::N;
		else if (it->second == "SW") callback = &SyntaxAnalysis::SW;
		else if (it->second == "SS") callback = &SyntaxAnalysis::SS;
		else if (it->second == "CA") callback = &SyntaxAnalysis::CA;
		else if (it->second == "CB") callback = &SyntaxAnalysis::CB;
		else if (it->second == "CE") callback = &SyntaxAnalysis::CE;
		else if (it->second == "EA") callback = &SyntaxAnalysis::EA;
		else if (it->second == "ES") callback = &SyntaxAnalysis::ES;
		else if (it->second == "ET") callback = &SyntaxAnalysis::ET;
		else if (it->second == "TF") callback = &SyntaxAnalysis::TF;
		else if (it->second == "TM") callback = &SyntaxAnalysis::TM;
		else if (it->second == "TD") callback = &SyntaxAnalysis::TD;
		else if (it->second == "F") callback = &SyntaxAnalysis::F;
		else if (it->second == "FID") callback = &SyntaxAnalysis::FID;
		else if (it->second == "FINT") callback = &SyntaxAnalysis::FINT;
		else if (it->second == "D1") callback = &SyntaxAnalysis::D1;
		else if (it->second == "D2") callback = &SyntaxAnalysis::D2;
		else callback = &SyntaxAnalysis::ept;
		this->actionList[it->first] = callback;
	}
}

void SyntaxAnalysis::setOutput(std::ofstream * input)
{
	this->outf = input;
}

void SyntaxAnalysis::gen(const std::string & input)
{
	this->codes.push_back(SyntaxAnalysis::Code(input));
}

int SyntaxAnalysis::nextquad()
{
	return (int)this->codes.size();
}

void SyntaxAnalysis::backpatch(std::vector<int> list, int quad)
{
	std::string tmp;
	std::stringstream ss;
	ss << quad;
	ss >> tmp;
	for (auto it = list.begin(); it != list.end(); ++it) {
		this->codes[*it].code += tmp;
	}
}

std::vector<int> SyntaxAnalysis::merge(const std::vector<int> & a, const std::vector<int> & b)
{
	std::vector<int> tmp(a);
	tmp.insert(tmp.end(), b.begin(), b.end());
	return tmp;
}

std::vector<int> SyntaxAnalysis::makelist(int i)
{
	std::vector<int> tmp;
	tmp.push_back(i);
	return tmp;
}

std::pair<int, std::string> SyntaxAnalysis::newTemp()
{
	return std::pair<int, std::string>(ID, "t");
}

void SyntaxAnalysis::printOut()
{
	*outf << "### Intermediate Code Generation" << std::endl << "```" << std::endl;
	int i = 0;
	for (auto it = this->codes.begin(); it != this->codes.end(); ++it) {
		*outf << i++ << ": " << it->code << std::endl;
	}
	*outf << "```" << std::endl;
}

void SyntaxAnalysis::ept()
{
}

void SyntaxAnalysis::Q1()
{
	this->envTable->setOffset(0);
	this->records.push_back(SyntaxAnalysis::Record(std::make_pair(BODER, "Q1")));
}

void SyntaxAnalysis::Q2()
{
	// L->top-2 id->top-1
	std::size_t top = this->records.size() - 1;
	this->envTable->enter(this->records[top - 1].lexeme, this->records[top - 2].type, this->records[top - 2].width);
	this->records.push_back(SyntaxAnalysis::Record(std::make_pair(BODER, "Q2")));
}

void SyntaxAnalysis::L1()
{
	this->records.back().type = "int";
	this->records.back().width = 4;
}

void SyntaxAnalysis::L2()
{
	this->records.back().type = "float";
	this->records.back().width = 8;
}

void SyntaxAnalysis::S()
{
	// id->top-3
	std::size_t top = this->records.size() - 1;
	auto tmps = this->envTable->findEnvItem(this->records[top - 3].lexeme);
	if (tmps.kind == KINDNULL) {
		// TODO 错误处理
		return;
	}
	std::pair<int, std::string> tmp = this->records[top - 3].lexeme;
	//gen
	std::string tmpss;
	std::stringstream ss;
	ss << tmp.second << " = " << this->records[top - 1].addr.second;
	std::getline(ss, tmpss);
	this->gen(tmpss);
	// 记录出栈
	this->records.erase(this->records.end() - 4, this->records.end());
	SyntaxAnalysis::Record S(std::make_pair(BODER, "S"));
	this->records.push_back(S);
}

void SyntaxAnalysis::M()
{
	SyntaxAnalysis::Record M(std::make_pair(BODER, "M"));
	M.quad = this->nextquad();
	this->records.push_back(M);
}

void SyntaxAnalysis::SF()
{
	std::size_t top = this->records.size() - 1;
	this->backpatch(this->records[top - 7].truelist, this->records[top - 5].quad);
	this->backpatch(this->records[top - 7].falselist, this->records[top - 1].quad);
	SyntaxAnalysis::Record S(std::make_pair(BODER, "S"));
	S.nextlist = merge(merge(this->records[top - 4].nextlist,
		this->records[top - 3].nextlist),
		this->records[top].nextlist);
	// pop out
	this->records.erase(this->records.end() - 10, this->records.end());
	this->records.push_back(S);
}

void SyntaxAnalysis::N()
{
	SyntaxAnalysis::Record N(std::make_pair(BODER, "N"));
	N.nextlist = this->makelist(this->nextquad());
	gen("goto ");
	this->records.push_back(N);
}

void SyntaxAnalysis::SW()
{
	std::size_t top = this->records.size() - 1;
	this->backpatch(this->records[top].nextlist, this->records[top - 3].quad);
	this->backpatch(this->records[top - 3].nextlist, this->records[top - 1].quad);
	SyntaxAnalysis::Record S(std::make_pair(BODER, "S"));
	S.nextlist = this->records[top - 3].falselist;
	std::string tmpss;
	std::stringstream ss;
	ss << "goto " << this->records[top - 5].quad;
	std::getline(ss, tmpss);
	gen(tmpss);
	// pop out
	this->records.erase(this->records.end() - 7, this->records.end());
	this->records.push_back(S);
}

void SyntaxAnalysis::SS()
{
	std::size_t top = this->records.size() - 1;
	this->backpatch(this->records[top - 2].nextlist, this->records[top - 1].quad);
	SyntaxAnalysis::Record S(std::make_pair(BODER, "S"));
	S.nextlist = this->records[top].nextlist;
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(S);
}

void SyntaxAnalysis::CA()
{
	std::size_t top = this->records.size() - 1;
	SyntaxAnalysis::Record C(std::make_pair(BODER, "C"));
	C.truelist = this->makelist(this->nextquad());
	C.falselist = this->makelist(this->nextquad() + 1);
	std::string tmpss;
	std::stringstream ss;
	ss << "if " << this->records[top - 2].addr.second << " > "
		<< records[top].addr.second << " goto ";
	std::getline(ss, tmpss);
	gen(tmpss);
	gen("goto ");
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(C);
}

void SyntaxAnalysis::CB()
{
	std::size_t top = this->records.size() - 1;
	SyntaxAnalysis::Record C(std::make_pair(BODER, "C"));
	C.truelist = this->makelist(this->nextquad());
	C.falselist = this->makelist(this->nextquad() + 1);
	std::string tmpss;
	std::stringstream ss;
	ss << "if " << this->records[top - 2].addr.second << " < "
		<< records[top].addr.second << " goto ";
	std::getline(ss, tmpss);
	gen(tmpss);
	gen("goto ");
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(C);
}

void SyntaxAnalysis::CE()
{
	std::size_t top = this->records.size() - 1;
	SyntaxAnalysis::Record C(std::make_pair(BODER, "C"));
	C.truelist = this->makelist(this->nextquad());
	C.falselist = this->makelist(this->nextquad() + 1);
	std::string tmpss;
	std::stringstream ss;
	ss << "if " << this->records[top - 2].addr.second << " == "
		<< records[top].addr.second << " goto ";
	std::getline(ss, tmpss);
	gen(tmpss);
	gen("goto ");
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(C);
}

void SyntaxAnalysis::EA()
{
	SyntaxAnalysis::Record E(std::make_pair(BODER, "E"));
	std::size_t top = this->records.size() - 1;
	E.addr = this->newTemp();
	std::string tmpss;
	std::stringstream ss;
	ss << E.addr.second << " = " << this->records[top - 2].addr.second << " + " << this->records[top].addr.second;
	std::getline(ss, tmpss);
	gen(tmpss);
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(E);
}

void SyntaxAnalysis::ES()
{
	SyntaxAnalysis::Record E(std::make_pair(BODER, "E"));
	std::size_t top = this->records.size() - 1;
	E.addr = this->newTemp();
	std::string tmpss;
	std::stringstream ss;
	ss << E.addr.second << " = " << this->records[top - 2].addr.second << " - " << this->records[top].addr.second;
	std::getline(ss, tmpss);
	gen(tmpss);
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(E);
}

void SyntaxAnalysis::ET()
{
	SyntaxAnalysis::Record E(std::make_pair(BODER, "E"));
	std::size_t top = this->records.size() - 1;
	E.addr = this->records[top].addr;
	// pop out
	this->records.erase(this->records.end() - 1, this->records.end());
	this->records.push_back(E);
}

void SyntaxAnalysis::TF()
{
	SyntaxAnalysis::Record T(std::make_pair(BODER, "T"));
	std::size_t top = this->records.size() - 1;
	T.addr = this->records[top].addr;
	// pop out
	this->records.erase(this->records.end() - 1, this->records.end());
	this->records.push_back(T);
}

void SyntaxAnalysis::TM()
{
	SyntaxAnalysis::Record T(std::make_pair(BODER, "T"));
	std::size_t top = this->records.size() - 1;
	T.addr = this->newTemp();
	std::string tmpss;
	std::stringstream ss;
	ss << T.addr.second << " = " << this->records[top - 2].addr.second << " * " << this->records[top].addr.second;
	std::getline(ss, tmpss);
	gen(tmpss);
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(T);
}

void SyntaxAnalysis::TD()
{
	SyntaxAnalysis::Record T(std::make_pair(BODER, "T"));
	std::size_t top = this->records.size() - 1;
	T.addr = this->newTemp();
	std::string tmpss;
	std::stringstream ss;
	ss << T.addr.second << " = " << this->records[top - 2].addr.second << " / " << this->records[top].addr.second;
	std::getline(ss, tmpss);
	gen(tmpss);
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(T);
}

void SyntaxAnalysis::F()
{
	SyntaxAnalysis::Record F(std::make_pair(BODER, "F"));
	std::size_t top = this->records.size() - 1;
	F.addr = this->records[top - 1].addr;
	// pop out
	this->records.erase(this->records.end() - 3, this->records.end());
	this->records.push_back(F);
}

void SyntaxAnalysis::FID()
{
	std::size_t top = this->records.size() - 1;
	SyntaxAnalysis::Record F(std::make_pair(BODER, "F"));
	auto tmp = this->envTable->findEnvItem(this->records[top].lexeme);
	if (tmp.kind == KINDNULL) {
		// TODO 错误处理
		std::cout << "The ID is not defination!" << std::endl;
		return;
	}
	F.addr = this->records[top].lexeme;
	// 记录出栈
	this->records.erase(this->records.end() - 1, this->records.end());
	this->records.push_back(F);
}

void SyntaxAnalysis::FINT()
{
	std::size_t top = this->records.size() - 1;
	SyntaxAnalysis::Record F(std::make_pair(BODER, "F"));
	auto tmp = this->envTable->findEnvItem(this->records[top].lexeme);
	if (tmp.kind == KINDNULL) {
		// TODO 错误处理
		std::cout << "The ID is not defination!" << std::endl;
		return;
	}
	F.addr = this->records[top].lexeme;
	// 记录出栈
	this->records.erase(this->records.end() - 1, this->records.end());
	this->records.push_back(F);
}

void SyntaxAnalysis::D1()
{
	this->records.erase(this->records.end() - 5, this->records.end());
	this->records.push_back(SyntaxAnalysis::Record(std::make_pair(BODER, "D")));
}

void SyntaxAnalysis::D2()
{
	this->records.push_back(SyntaxAnalysis::Record(std::make_pair(BODER, "D")));
}
