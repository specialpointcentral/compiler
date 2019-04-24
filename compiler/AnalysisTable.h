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

		bool operator == (const GramRule &a) {
			return this->left == a.left && this->right == a.right;
		}
	};
	// 有状态的语法变量
	class statusGram {
	public:
		int status;
		GramRule gramRule;
		statusGram(int status, GramRule gramRule) :status(status), gramRule(gramRule) {}
	};
	// 项集
	class item {
	public:
		int status;
		std::set<AnalysisTable::statusGram> grams;
		// 相等重载
		bool operator == (const AnalysisTable::item &input) {
			return this->grams == input.grams;
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


private:
	std::set<AnalysisTable::statusGram> closure(std::set<AnalysisTable::statusGram>);
	std::set<AnalysisTable::statusGram> GOTO(std::set<AnalysisTable::statusGram>, std::pair<int, std::string>);
	// 填充table
	void insertTable();
};

