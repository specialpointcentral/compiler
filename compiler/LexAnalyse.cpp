#include "LexAnalyse.h"

// ��ʼ���ʷ���������ÿһ��װ��һ��vector��
LexAnalyse::LexAnalyse(std::vector<std::string> inputLex)
{
	this->inputLex = inputLex;
	this->tokenList = nullptr;
}

LexAnalyse::~LexAnalyse()
{

}

// �ʷ���������
bool LexAnalyse::lexAnalysic()
{
	for (int line = 0; line < inputLex.size(); ++line) {
		std::string hintLine = inputLex[line];
		for (int pos = 0, lastPos = 0; pos < hintLine.size(); ++pos, lastPos = pos) {
			if (isLetter(hintLine[pos])) {
				// ��������ĸ��ͷ������ 1-keyword,2-id
				// �����е�letter��numberȫ��Ū��ȥ
				while (pos < hintLine.size() && (isLetter(hintLine[++pos]) || isNumber(hintLine[pos])));
				if (pos == hintLine.size()) --pos; // ���
				else if (!isLetter(hintLine[pos]) && !isNumber(hintLine[pos])) --pos;
				// �ж��ǲ���keyword
				if (isKeyword(hintLine.substr(lastPos, pos - lastPos + 1))) {
					// TODO ����keyword
					// std::cout << "keyword\t" << hintLine.substr(lastPos, pos - lastPos + 1) << std::endl;
					tokenList->Toke(KEYWORDS, hintLine.substr(lastPos, pos - lastPos + 1));
				}
				else {
					// TODO ����id
					// std::cout << "id\t" << hintLine.substr(lastPos, pos - lastPos + 1) << std::endl;
					tokenList->Toke(ID, hintLine.substr(lastPos, pos - lastPos + 1));
				}

			}
			else if (isNumber(hintLine[pos])) {
				// ���������ֿ�ͷ������ 1-int10,2-error
				while (pos < hintLine.size() && isNumber(hintLine[++pos]));
				if (pos == hintLine.size()) --pos; // ���
				if (!isNumber(hintLine[pos])) --pos;
				if (isLetter(hintLine[pos + 1])) {
					// error
					// �ֻŴ�����������letter��number
					while (pos < hintLine.size() && (isLetter(hintLine[++pos]) || isNumber(hintLine[pos])));
					if (pos == hintLine.size()) --pos; // ���
					else if (!isLetter(hintLine[pos]) && !isNumber(hintLine[pos])) --pos;

					error(hintLine, line + 1, lastPos, pos);

				}
				else {
					// int10
					// TODO ����int10
					// std::cout << "int10\t" << hintLine.substr(lastPos, pos - lastPos + 1) << std::endl;
					tokenList->Toke(INT10, hintLine.substr(lastPos, pos - lastPos + 1));
				}
			}
			else if (isOp(hintLine[pos])) {
				// ������op�ģ����� 1-only,2-double
				if (isOp(hintLine.substr(lastPos, 2))) {
					// TODO ���������� hintLine.substr(lastPos, 2)
					// std::cout << "op\t" << hintLine.substr(lastPos, 2) << std::endl;
					tokenList->Toke(OP, hintLine.substr(lastPos, 2));
					++pos;
				}
				else {
					// TODO ����һ����
					// std::cout << "op\t" << hintLine.substr(lastPos, 1) << std::endl;
					tokenList->Toke(OP, hintLine.substr(lastPos, 1));
				}
			}
			else if (hintLine[pos] == ' ') {
				// ���������ո�
				while (pos < hintLine.size() && hintLine[++pos] == ' ');
				if (pos == hintLine.size()) --pos; // ���
				else if (!(hintLine[pos] == ' ')) --pos;
			}
			else {
				// TODO ����
				++pos;

				error(hintLine, line + 1, lastPos, pos);
			}
		}
	}
	return 0;
}


// �Ƿ�����ĸ
bool LexAnalyse::isLetter(char i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')) {
		return true;
	}
	return false;
}


// �Ƿ�������
bool LexAnalyse::isNumber(char i)
{
	if ((i >= '0' && i <= '9')) {
		return true;
	}
	return false;
}


// �ж��Ƿ���OP
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
		// ����ֻ����һ���ĺ�������
		if (in == op[i][0]) {
			return true;
		}
	}
	return false;
}

// �Ƿ��ǹؼ���
bool LexAnalyse::isKeyword(std::string in)
{
	for (int i = 0; i < keywords.size(); ++i) {
		if (in == keywords[i]) {
			return true;
		}
	}
	return false;
}


// �õ�LexToken��
std::vector<std::pair<int, std::string>> LexAnalyse::getTokenTable()
{
	return this->tokenList->tokenList;
}


// �������error
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


// ����TokenList
void LexAnalyse::setTokenList(TokenList *tokenList)
{
	this->tokenList = tokenList;
}


// �ж��Ƿ��д�����Ҫ����
bool LexAnalyse::hasError()
{
	return !errorStack.empty();
}


// ��ȡ��������
std::vector<LexAnalyse::errors> LexAnalyse::getError()
{
	return errorStack;
}
