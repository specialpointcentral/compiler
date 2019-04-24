#pragma once
#include "headerInclude.h"
class AnalysisTable
{
public:
	AnalysisTable();
	~AnalysisTable();
	// ACTION����
	class Action {
	public:
		std::map<std::pair<int, std::string>, std::string> actionMap;
	};
	// GOTO����
	class GOTO {
	public:
		std::map<std::pair<int, std::string>, int> gotoMap;
	};
	// ������һ�б���
	class SingleLine {
	public:
		AnalysisTable::Action t_action;
		AnalysisTable::GOTO t_goto;
	};
	// �﷨����
	class GramRule {
	public:
		std::pair<int, std::string> left;				// ��
		std::vector<std::pair<int, std::string>> right;	// �Ҳ�

		bool operator == (const GramRule &a) {
			return this->left == a.left && this->right == a.right;
		}
	};
	// ��״̬���﷨����
	class statusGram {
	public:
		int status;
		GramRule gramRule;
		statusGram(int status, GramRule gramRule) :status(status), gramRule(gramRule) {}
	};
	// �
	class item {
	public:
		int status;
		std::set<AnalysisTable::statusGram> grams;
		// �������
		bool operator == (const AnalysisTable::item &input) {
			return this->grams == input.grams;
		}
	};
	// ���
	std::set<AnalysisTable::item> itemSet;
	// Դ�﷨����
	std::map<int, GramRule> realGram;
	// <summary>
	// AnalysisTable
	// map
	//  - int: ״̬��
	//  - SingleLine: һ�еĽṹ
	//		- t_action��ACTION
	//			- map 
	//				- std::pair<int, std::string>:����Ĵʷ��������ݣ����ۺ�����
	//				- string:����			
	//		- t_goto�� GOTO
	//			- map
	//				- std::pair<int,std::string>:�����ۺ�����
	//				- int:GOTO״̬
	// </summary>
	std::map<int, AnalysisTable::SingleLine> Table;


private:
	std::set<AnalysisTable::statusGram> closure(std::set<AnalysisTable::statusGram>);
	std::set<AnalysisTable::statusGram> GOTO(std::set<AnalysisTable::statusGram>, std::pair<int, std::string>);
	// ���table
	void insertTable();
};

