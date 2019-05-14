#include "LexAnalyse.h"

// 初始化词法分析器，每一行装入一个vector里
LexAnalyse::LexAnalyse(std::vector<std::string> inputLex, std::ofstream *outf)
{
	this->inputLex = inputLex;
	this->tokenList = nullptr;
	this->outf = outf;
	this->envTable = nullptr;
}

LexAnalyse::~LexAnalyse()
{

}

// 词法分析函数
bool LexAnalyse::lexAnalysic()
{
	for (int line = 0; line < inputLex.size(); ++line) {
		std::string hintLine = inputLex[line];
		for (int pos = 0, lastPos = 0; pos < hintLine.size(); ++pos, lastPos = pos) {
			if (isLetter(hintLine[pos])) {
				// 对于是字母开头，考虑 1-keyword,2-id
				// 将所有的letter和number全部弄进去
				while (pos < hintLine.size() && (isLetter(hintLine[++pos]) || isNumber(hintLine[pos])));
				if (pos == hintLine.size()) --pos; // 溢出
				else if (!isLetter(hintLine[pos]) && !isNumber(hintLine[pos])) --pos;
				// 判断是不是keyword
				if (isKeyword(hintLine.substr(lastPos, pos - lastPos + 1))) {
					// 加入keyword
					// std::cout << "keyword\t" << hintLine.substr(lastPos, pos - lastPos + 1) << std::endl;
					tokenList->Toke(KEYWORDS, hintLine.substr(lastPos, pos - lastPos + 1));
				}
				else {
					// 加入id
					// std::cout << "id\t" << hintLine.substr(lastPos, pos - lastPos + 1) << std::endl;
					tokenList->Toke(ID, hintLine.substr(lastPos, pos - lastPos + 1));
					envTable->createItem(std::make_pair(ID, hintLine.substr(lastPos, pos - lastPos + 1)));
				}

			}
			else if (isNumber(hintLine[pos])) {
				// 对于是数字开头，考虑 1-int10,2-error
				while (pos < hintLine.size() && isNumber(hintLine[++pos]));
				if (pos == hintLine.size()) --pos; // 溢出
				if (!isNumber(hintLine[pos])) --pos;
				if (isLetter(hintLine[pos + 1])) {
					// error
					// 恐慌处理，跑完所有letter和number
					while (pos < hintLine.size() && (isLetter(hintLine[++pos]) || isNumber(hintLine[pos])));
					if (pos == hintLine.size()) --pos; // 溢出
					else if (!isLetter(hintLine[pos]) && !isNumber(hintLine[pos])) --pos;

					error(hintLine, line + 1, lastPos, pos);

				}
				else {
					// int10
					// 加入int10
					// std::cout << "int10\t" << hintLine.substr(lastPos, pos - lastPos + 1) << std::endl;
					tokenList->Toke(INT10, hintLine.substr(lastPos, pos - lastPos + 1));
					envTable->createItem(std::make_pair(INT10, hintLine.substr(lastPos, pos - lastPos + 1)));
				}
			}
			else if (isOp(hintLine[pos])) {
				// 对于是op的，考虑 1-only,2-double
				if (isOp(hintLine.substr(lastPos, 2))) {
					// 加入两个的 hintLine.substr(lastPos, 2)
					// std::cout << "op\t" << hintLine.substr(lastPos, 2) << std::endl;
					tokenList->Toke(OP, hintLine.substr(lastPos, 2));
					++pos;
				}
				else {
					// 加入一个的
					// std::cout << "op\t" << hintLine.substr(lastPos, 1) << std::endl;
					tokenList->Toke(OP, hintLine.substr(lastPos, 1));
				}
			}
			else if (hintLine[pos] == ' ') {
				// 丢掉其他空格
				while (pos < hintLine.size() && hintLine[++pos] == ' ');
				if (pos == hintLine.size()) --pos; // 溢出
				else if (!(hintLine[pos] == ' ')) --pos;
			}
			else {
				// TODO 出错
				++pos;
				error(hintLine, line + 1, lastPos, pos);
			}
		}
	}
	std::cout << "Lex Analysis Complete!" << std::endl;
	return true;
}


// 是否是字母
bool LexAnalyse::isLetter(char i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')) {
		return true;
	}
	return false;
}


// 是否是数字
bool LexAnalyse::isNumber(char i)
{
	if ((i >= '0' && i <= '9')) {
		return true;
	}
	return false;
}


// 判断是否是OP
bool LexAnalyse::isOp(std::string in)
{
	for (int i = 0; i < op.size(); ++i) {
		if (in == op[i]) {
			return true;
		}
	}
	return false;
}

bool LexAnalyse::isOp(char in) {
	for (int i = 0; i < op.size(); ++i) {
		// 考虑只含有一个的和两个的
		if (in == op[i][0]) {
			return true;
		}
	}
	return false;
}

// 是否是关键字
bool LexAnalyse::isKeyword(std::string in)
{
	for (int i = 0; i < keywords.size(); ++i) {
		if (in == keywords[i]) {
			return true;
		}
	}
	return false;
}


// 得到LexToken表
std::vector<std::pair<int, std::string>> LexAnalyse::getTokenTable()
{
	return this->tokenList->tokenList;
}


// 处理分析error
void LexAnalyse::error(std::string line, int lines, int begin, int end)
{
	LexAnalyse::errors e;
	e.line = line;
	e.lines = lines;
	e.begin = begin;
	e.end = end;
	errorStack.push_back(e);
	/*std::cout << "Lex Analysis error: " << " Line:" << lines << std::endl;
	std::cout << line << std::endl;
	for (int i = 0; i < end; ++i) {
		if (i < begin) std::cout << " ";
		else std::cout << "^";
	}
	std::cout << std::endl;*/
}


// 设置TokenList
void LexAnalyse::setTokenList(TokenList *tokenList)
{
	this->tokenList = tokenList;
}


// 判断是否有错误需要处理
bool LexAnalyse::hasError()
{
	return !errorStack.empty();
}


// 获取错误数据
std::vector<LexAnalyse::errors> LexAnalyse::getError()
{
	return errorStack;
}

// 设置符号表
void LexAnalyse::setEnvTable(EnvTable*  input)
{
	this->envTable = input;
}
