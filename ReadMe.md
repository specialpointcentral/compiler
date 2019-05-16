# Compiler

HypoGCC(误)

## 系统设计与架构

完成了：

- [x] 词法分析
- [x] 语法分析
- [x] 语法制导的语义翻译
- [x] 中间代码生成

## 目录文件包含

- 源码目录
  - *.sln 解决方案
  - compiler/ 标准源码目录
- Release版本：compiler.exe
- 包含的数据文件
  - in.txt 目标源码文件
  - gram.txt 语法翻译方案（包含语义动作）
  - out.md 输出的文件（Markdown格式）

## 运行环境设置

Windows 10 开发环境，采用 C++进行开发。
Windows SDK 10.0.18362.0
平台工具集 Visual Studio 2019 (v142)

**如要在低版本VS上编译，请重新选择目标平台的SDK版本和平台工具集**

> 具体方案：
>
> 调试 - 属性 - 配置属性 - 常规
>
> - Windows SDK版本
>
> - 平台工具集

## 使用说明

1. 打开compiler.exe

2. 输入需要翻译的源代码

3. 输入语法规则

4. 输入输出文件地址和文件名

   **注意输出文件名以md结尾，为Markdown格式**