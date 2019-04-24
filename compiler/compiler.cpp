// compiler.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "headerInclude.h"
#include "LexAnalyse.h"
#include "GrammerAnalysis.h"

using namespace std;

ifstream inf;
ofstream outf;
TokenList tokenList = TokenList();

int main()
{
	string filename;

	cout << "Open file:";
	cin >> filename;
	inf.open(filename, ios::in);
	if (!inf.is_open()) {
		cout << "Unable to open the input file. " << endl;
		cout << "Press any key to continue.." << endl;
		return 0;
	}
	outf.open("out.txt", ios::out);
	if (!outf.is_open()) {
		cout << "Unable to open the output file. " << endl;
		cout << "Press any key to continue.." << endl;
		return 0;
	}

	std::string strings;
	vector<string> input;
	while (std::getline(inf, strings)) {
		input.push_back(strings);
	}
	// 词法分析
	LexAnalyse lex = LexAnalyse(input);
	lex.setTokenList(&tokenList);
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
		return 0;
	}
	std::vector<std::pair<int, std::string>> tokenList;
	tokenList = lex.getTokenTable();
	// 进行语法分析

	// 进行语法制导的语义翻译

	return 0;
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
