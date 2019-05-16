// compiler.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "headerInclude.h"
#include "LexAnalyse.h"
#include "SyntaxAnalysis.h"
#include "EnvTable.h"

using namespace std;

ifstream inf;
ofstream outf;
TokenList tokenList;
AnalysisTable analysisTable = AnalysisTable();
std::vector<std::pair<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>>> gramRule;
std::map<int, std::string> actionList;
EnvTable envTable(&outf);

void spiltArray(const string&, vector<string>&, const string&);
std::pair<int, std::string> getPair(const std::string&);
bool readGram(const std::string&, std::vector<std::pair<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>>>&);

int main()
{
	string filename;

	cout << "Open file:";
	cin >> filename;
	inf.open(filename, ios::in);
	if (!inf.is_open()) {
		cout << "Unable to open the input file. " << endl;
		cout << "Press any key to continue.." << endl;
		std::system("pause");
		return 0;
	}
	cout << "Open gram file:";
	cin >> filename;
	if (!readGram(filename, gramRule)) {
		std::system("pause");
		return 0;
	}
	cout << "Output file（use Markdown, *.md）:";
	cin >> filename;
	outf.open(filename, ios::out);
	if (!outf.is_open()) {
		cout << "Unable to open the output file. " << endl;
		cout << "Press any key to continue.." << endl;
		std::system("pause");
		return 0;
	}

	std::string strings;
	vector<string> input;
	while (std::getline(inf, strings)) {
		input.push_back(strings);
	}
	// 词法分析
	LexAnalyse lex = LexAnalyse(input, &outf);
	lex.setTokenList(&tokenList);
	lex.setEnvTable(&envTable);
	lex.lexAnalysic();
	// 词法分析-错误处理
	if (lex.hasError()) {
		std::vector<LexAnalyse::errors> errorList = lex.getError();
		std::cout << "Lex Analysis error: " << std::endl;
		outf << "Lex Analysis error: " << std::endl;
		for (auto it = errorList.begin(); it != errorList.end(); ++it) {
			std::cout << " Line:" << it->lines << std::endl;
			std::cout << it->line << std::endl;
			outf << " Line:" << it->lines << std::endl;
			outf << it->line << std::endl;
			for (int i = 0; i < it->end; ++i) {
				if (i < it->begin) {
					std::cout << " ";
					outf << " ";
				}
				else {
					std::cout << "^";
					outf << "^";
				}
			}
			std::cout << std::endl;
		}
		std::cout << "Analysis Stoped! Please check the code again!";
		std::system("pause");
		return 0;
	}
	std::vector<std::pair<int, std::string>> tokenLists;
	tokenLists = lex.getTokenTable();
	// 输出分析结果
	outf << "### Lex result" << std::endl << std::endl << "```" << std::endl;
	for (auto it = tokenLists.begin(); it != tokenLists.end(); ++it) {
		outf << "< " << it->first << " , " << it->second << " >" << std::endl;
	}
	outf << "```" << std::endl << std::endl;
	// 生成状态转换表
	analysisTable.setRealGram(gramRule, &outf);
	analysisTable.insertTable();
	// 进行语法分析
	SyntaxAnalysis gram = SyntaxAnalysis(&tokenList, &analysisTable, &envTable);
	// 添加语义动作
	gram.setActionList(actionList);
	gram.setOutput(&outf);
	// 进行语法制导的语义翻译
	gram.beginAnalysis();

	std::system("pause");
	return 0;
}

bool readGram(const std::string& inputFile, std::vector<std::pair<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>>>& input) {
	ifstream inf;
	inf.open(inputFile, ios::in);
	if (!inf.is_open()) {
		cout << "Unable to open the input file. " << endl;
		cout << "Press any key to continue.." << endl;
		return false;
	}
	std::string line;
	while (getline(inf, line)) {
		std::pair<int, std::string> left;
		std::vector<std::pair<int, std::string>> right;
		// 先将左边加入
		std::string::size_type pos = line.find("→");
		left = getPair(line.substr(0, pos));
		pos += std::string("→").size();
		// 加入右边的
		std::vector<std::string> s;
		spiltArray(line.substr(pos), s, "|");
		for (auto it = s.begin(); it != s.end(); ++it) {
			std::vector<std::string> p;
			spiltArray(*it, p, " ");
			for (auto pt = p.begin(); pt != p.end(); ++pt) {
				auto tmp = getPair(*pt);
				if (tmp.first == ACTION) {
					// 语义动作
					actionList[gramRule.size()] = tmp.second;
				}
				else
				{
					right.push_back(tmp);
				}
			}
			input.push_back(std::make_pair(left, right));
			right.clear();
		}

	}
	return true;
}

void spiltArray(const string& s, vector<string>& v, const string& c) {
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
std::pair<int, std::string> getPair(const std::string & input) {
	std::string tmp = input.substr(1, input.size() - 2);
	std::vector<std::string> split;
	spiltArray(tmp, split, ",");
	int left;
	if (split[0] == "KEYWORDS") {
		left = KEYWORDS;
	}
	else if (split[0] == "INT10") {
		left = INT10;
	}
	else if (split[0] == "ID") {
		left = ID;
	}
	else if (split[0] == "OP") {
		left = OP;
	}
	else if (split[0] == "BODER") {
		left = BODER;
	}
	else if (split[0] == "EMPTY") {
		left = EMPTY;
	}
	else if (split[0] == "ACTION") {
		left = ACTION;
	}
	return std::make_pair(left, split.size() == 1 ? "" : split[1]);
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
