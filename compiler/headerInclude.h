#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <sstream>
#include <set>

// 声明Lex种类
constexpr auto KEYWORDS = 1;
constexpr auto INT10 = 2;
constexpr auto ID = 3;
constexpr auto OP = 4;
constexpr auto END = 5;
constexpr auto BODER = 6;	// 非终结符
constexpr auto EMPTY = 7;	// 空串


constexpr auto BEGINITEM = "E";	// 开始符号