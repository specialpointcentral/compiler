#pragma once
#include "headerInclude.h"
class AnalysisTable
{
public:
	AnalysisTable();
	~AnalysisTable();
	// ACTION表项
	class Action {
	public:
		std::map<std::pair<int, std::string>, std::string> actionMap;
	};
	// GOTO表项
	class GOTO {
	public:
		std::map<std::pair<int, std::string>, int> gotoMap;
	};
	// 分析表一行表项
	class SingleLine {
	public:
		AnalysisTable::Action t_action;
		AnalysisTable::GOTO t_goto;
	};
	// 语法变量
	class GramRule {
	public:
		std::pair<int, std::string> left;				// 左部
		std::vector<std::pair<int, std::string>> right;	// 右部
		GramRule(std::pair<int, std::string> a, std::vector<std::pair<int, std::string>>b) :left(a), right(b) {}
		GramRule() {
			left = std::pair<int, std::string>();
			right = std::vector<std::pair<int, std::string>>();
		}
		friend bool operator == (const AnalysisTable::GramRule &a, const AnalysisTable::GramRule &input) {
			return a.left == input.left && a.right == input.right;
		}
		friend bool operator < (const AnalysisTable::GramRule &a, const AnalysisTable::GramRule &input) {
			if (a.left == input.left) {
				return  a.right < input.right;
			}
			else
				return a.left < input.left;
		}
	};
	// 有状态的语法变量
	class statusGram {
	public:
		int status;
		GramRule gramRule;
		statusGram(int status, GramRule gramRule) :status(status), gramRule(gramRule) {}
		friend bool operator == (const AnalysisTable::statusGram &a, const AnalysisTable::statusGram &input) {
			if (a.status == input.status && a.gramRule == input.gramRule)
				return true;
			else return false;
		}
		friend bool operator < (const AnalysisTable::statusGram &a, const AnalysisTable::statusGram &input) {
			if (a.status == input.status) {
				return a.gramRule < input.gramRule;
			}
			else return a.status < input.status;
		}
	};
	// 项集
	class item {
	public:
		int status;
		std::set<AnalysisTable::statusGram> grams;
		// 相等重载
		friend bool operator == (const AnalysisTable::item &input, const AnalysisTable::item &a) {
			return a.grams == input.grams;
		}
		friend bool operator < (const AnalysisTable::item &input, const AnalysisTable::item &a) {
			if (a.status == input.status)
				return a.grams < input.grams;
			else
				return a.status < input.status;
		}
	};
	// 项集族
	std::set<AnalysisTable::item> itemSet;
	// 源语法规则
	std::map<int, GramRule> realGram;
	// <summary>
	// AnalysisTable
	// map
	//  - int: 状态号
	//  - SingleLine: 一行的结构
	//		- t_action：ACTION
	//			- map 
	//				- std::pair<int, std::string>:输入的词法分析内容，非综合属性
	//				- string:动作			
	//		- t_goto： GOTO
	//			- map
	//				- std::pair<int,std::string>:输入综合属性
	//				- int:GOTO状态
	// </summary>
	std::map<int, AnalysisTable::SingleLine> Table;
	// 填充table
	void insertTable();

private:
	std::set<AnalysisTable::statusGram> closure(std::set<AnalysisTable::statusGram>);
	std::set<AnalysisTable::statusGram> GOTO(std::set<AnalysisTable::statusGram>, std::pair<int, std::string>);
	// 设置GOTO表格内容
	void setGOTO(const int &, const int &, const std::pair<int, std::string> &);
	// 设置Action项目
	void setAction(const std::string &, const int &, const std::pair<int, std::string> &);
	// 寻找item项目
	int findItem(const std::set<AnalysisTable::statusGram> &);
	// 返回first集合
	std::set<std::pair<int, std::string>> FIRST(const std::pair<int, std::string>&);
	std::set<std::pair<int, std::string>> FIRST(const std::vector<std::pair<int, std::string>>&);
	// 返回follow集合
	std::set<std::pair<int, std::string>> FOLLOW(const std::pair<int, std::string>&);
	// first集合
	std::map<std::pair<int, std::string>, std::set<std::pair<int, std::string>>> FIRSTSet;
	// follow集合
	std::map<std::pair<int, std::string>, std::set<std::pair<int, std::string>>> FOLLOWSet;
	std::ofstream *outf;
public:
	// 设置语法分析表
	void setRealGram(const std::vector<std::pair<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>>>&, std::ofstream *);
private:
	// 文件输出
	void printToFile();
};

