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
	// ��״̬���﷨����
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
	// �
	class item {
	public:
		int status;
		std::set<AnalysisTable::statusGram> grams;
		// �������
		friend bool operator == (const AnalysisTable::item &input, const AnalysisTable::item &a) {
			return a.grams == input.grams;
		}
		friend bool operator < (const AnalysisTable::item &input, const AnalysisTable::item &a) {
			return a.grams < input.grams;
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
	// ����GOTO��������
	void setGOTO(const int &, const int &, const std::pair<int, std::string> &);
	// ����Action��Ŀ
	void setAction(const std::string &, const int &, const std::pair<int, std::string> &);
	// Ѱ��item��Ŀ
	int findItem(const std::set<AnalysisTable::statusGram> &);
};
