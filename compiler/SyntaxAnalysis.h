#pragma once
#include "headerInclude.h"
#include "TokenList.h"
#include "AnalysisTable.h"
#include "EnvTable.h"
class SyntaxAnalysis
{
public:
	SyntaxAnalysis(TokenList*, AnalysisTable*, EnvTable*);
	~SyntaxAnalysis();
	// 记录栈结构
	class Record
	{
	public:
		// use as defination
		std::pair<int, std::string> lexeme;
		std::string type;
		int width;
		// 
		std::vector<int> nextlist;
		std::vector<int> truelist;
		std::vector<int> falselist;
		std::pair<int,std::string> addr = std::pair<int, std::string>();
		int quad;
		Record(const std::pair<int, std::string>& input) :lexeme(input) { Record(); }
		Record() :type(""), width(0), quad(0) {
			nextlist.clear(); 
			truelist.clear(); 
			falselist.clear();
		}
	};
	// 代码存储
	class Code {
	public:
		std::string code;

		Code() {}
		Code(const std::string& input) :code(input) {}
	};
	// 开始语法分析
	void beginAnalysis();
	// 设置语义动作
	void setActionList(const std::map<int, std::string>& input);
	// 设置文件输出
	void setOutput(std::ofstream*);
private:
	// stack
	std::stack<int> stauts;							// 状态栈
	std::stack<std::pair<int, std::string>> sym;		// 符号栈
	std::vector<SyntaxAnalysis::Record> records;	// 记录栈
	// 语义动作
	typedef void(SyntaxAnalysis::* _CALLBACK)();
	std::map<int, SyntaxAnalysis::_CALLBACK> actionList;

	TokenList* tokenList;
	AnalysisTable* analysisTable;
	EnvTable* envTable;
	std::ofstream* outf;

	// 中间代码存储区
	std::vector<SyntaxAnalysis::Code> codes;

	void gen(const std::string&);
	int nextquad();
	void backpatch(std::vector<int>, int);
	std::vector<int> merge(const std::vector<int>&, const std::vector<int>&);
	std::vector<int> makelist(int);
	std::pair<int,std::string> newTemp();
	// 输出操作
	void printOut();
	// 动作语义回调函数定义
	// 空操作
	void ept();
	// Q1 → ε{ offset = 0; }
	void Q1();
	// Q2 → ε{ enter( id.lexeme, L.type, offset ); offset = offset + L.width; }
	void Q2();
	// L → int { L.type = int; L.width = 4; }
	void L1();
	// L → float { L.type = float; L.width = 8; }
	void L2();
	// S → id = E; 
	// { 
	// p = lookup(id.lexeme);
	// if p == nil then error;
	// S.nextlist = null;
	// gen(p ‘ = ’E.addr);
	// }
	void S();
	// M →ε{ M.quad = nextquad ; }
	void M();
	// S → if  (C) M1 S1  N  else  M2  S2
	// {
	// backpatch(C.truelist, M1.quad);
	// backpatch(C.falselist, M2.quad);
	// S.nextlist = merge(merge(S1.nextlist, N.nextlist), S2.nextlist);
	// }
	void SF();
	// N→ε
	// { 
	// N.nextlist = makelist(nextquad);
	// gen(‘goto _’); 
	// }
	void N();
	// S → while M1(C) M2 S1
	// {
	// backpatch(S1.nextlist, M1.quad);
	// backpatch(C.truelist, M2.quad);
	// S.nextlist = C.falselist;
	// gen(‘goto’ M1.quad);
	// }
	void SW();
	// S → S1M S2
	// {
	// backpatch(S1.nextlist, M.quad);
	// S.nextlist = S2.nextlist;
	// }
	void SS();
	// C → E1 relop E2
	// {
	// C.truelist = makelist(nextquad);
	// C.falselist = makelist(nextquad + 1);
	// gen(‘if ’E1.addr relop E2.addr ‘goto _’);
	// gen(‘goto _’);
	// }
	// C → E1 > E2
	void CA();
	// C → E1 < E2
	void CB();
	// C → E1 == E2
	void CE();
	// E → E1 + T 
	// { 
	// E.addr = newtemp( );
	// gen(E.addr ‘ = ’E1.addr ‘ + ’T.addr);
	// }
	void EA();
	// E → E1 – T
	// { 
	// E.addr = newtemp( );
	// gen(E.addr ‘ = ’E1.addr ‘ - ’T.addr); 
	// }
	void ES();
	// E → T{ E.addr =T.addr}
	void ET();
	// T → F{ T.addr =F.addr}
	void TF();
	// T → T1 * F
	// { 
	// T.addr = newtemp( );
	// gen(T.addr ‘ = ’T1.addr ‘ * ’F.addr); 
	// }
	void TM();
	// T → T1 / F
	// { 
	// T.addr = newtemp( );
	// gen(T.addr ‘ = ’T1.addr ‘ / ’F.addr); 
	// }
	void TD();
	// F → ( E ) { F.addr = E .addr ; }
	void F();
	// F → id 
	// { 
	// F.addr = lookup(id.lexeme);
	// if F.addr == nil then error; 
	// }
	void FID();
	// F → int10
	// {
	// F.addr = lookup(int10.val);
	// if F.addr == nil then error; 
	// }
	void FINT();

	void D1();

	void D2();
};

