



<img src=".\image\zju.png" alt="zju" style="zoom: 40%;" />

<h1 align = "center">C-Minus Compiler</h1>



<img src=".\image\logo.png" alt="logo" style="zoom: 33%;" />







<h4 align = "center">课程名称：编译原理</h4>

<h4 align = "center">2021-2022学年春夏学期</h4>

<h4 align = "center">学院：竺可桢学院</h4>

<h4 align = "center">专业：计算机科学与技术</h4>

<h4 align = "center">指导教师：李莹</h4>

<h4 align = "center">小组成员：汪辉 徐正韬 谢文想</h4>











<h3 align = "center">Date:2022-05-xx</h3>

<div style="page-break-after:always"></div>

## 概述

#### 1 项目概述



#### 2 文件说明



#### 3 开发环境

- 操作系统：Linux
- 编译环境：
  - Flex
  - Bison
  - LLVM

#### 4 组员分工



## 第一章 词法分析



## 第二章 语法分析

#### 2.1 Yacc介绍

Yacc(Yet Another Compiler Compiler)是Unix/Linux上一个用来生成编译器的编译器（编译器代码生成器），它使⽤巴克斯范式(BNF)定义语法，能处理上下文无关文法(context-free)。Yacc生成的编译器主要是用C语言写成的语法解析器（Parser），需要与词法解析器Lex一起使用，再把两部份产生出来的C程序一并编译。
与Lex相似，Yacc的输入文件由以%%分割的三部分组成，分别是声明区、规则区和程序区。三部分的功能与Lex相似，不同的是规则区的正则表达式替换为CFG，在声明区要提前声明好使用到的终结符以及非终结符的类型。

```yacas
/* definitions */
//....
%%
/* rules */ 
//....
%% 
/* auxiliary routines */
//.... 
```

定义部分：定义部分包括有关语法定义中使用的标记的信息，还可以包括解析器和变量声明之外的C代码，位于第一列的%{和%}中。

规则部分：规则部分包含修改后的BNF格式的语法定义。动作是{}中的C代码，可以嵌入其中。

辅助例程部分：辅助例程部分仅是C代码，它包括规则部分中所需的每个函数的函数定义。如果解析器要作为程序运行，它也可以包含main()函数定义，main()函数必须调用函数yyparse()。

#### 2.2 抽象语法树

在计算机科学中，抽象语法树（Abstract Syntax Tree，AST），或简称语法树（Syntax tree），是源代码语法结构的⼀一种抽象表示。它以树状的形式表现编程语⾔言的语法结构，树上的每个节点都表示源代码中的⼀一种结构。

之所以说语法是“抽象”的，是因为这⾥里里的语法并不不会表示出真实语法中出现的每个细节。⽐比如，嵌套括号被隐含在树的结构中，并没有以节点的形式呈现；⽽而类似于if-condition-then这样的条件跳转语句句，可以使⽤用带有两个分⽀支的节点来表示。

###### 2.2.1 Node类

我们将抽象语法树的所有节点抽象为一个Node类，Node有结点名、结点类型、儿子数、行数等属性，也实现了了初始化、添加结点、设置类型、获取类型等相关函数。

对于结点类型，我们定义如下：

```c++
/**
* @brief 
* the type of the node, valid values for nodeType 
*  "Program":                  the root node of the AST,
*  "GlobalDefinitionList":     node of list of all the function and global var's definition,
*  "GlobalDefinition":         node of function or global var's definition,
*  "Typer":                    node refers 4 valid data type identifier,
*  "GlobalVariableList":       node of list of global var's definition for current data type's definition
*  "GlobalVariable":           node of global var's definition
*  "Function":                 node of function's definition
*  "ParameterList":            node of list of function's parameters
*  "Parameter":                node of single parameter
*  "FunctionCode":             node of all the instructions in a function
*  "Instruction":              node of single instruction
*  "Definition":               node of a definition instruction
*  "LocalVariableList":        node of list of local vars' definition
*  "LocalVariable":            node of local var's definition
*  "Statement":                node of a instruction but definition
*  "Expression":               node of a expression
*  "Arguments":                node of arguments
*/
string node_Type;
```

其中对于每个结点类型都有相应的描述，在此不再阐述。

#### 2.3 语法分析的具体实现

###### 2.3.1 定义部分

定义AST根节点指针：

```c++
extern Node *ASTroot;
```

定义token：

```c++
%token <node> CHAR INT FLOAT DOUBLE VOID
%token <node> Integer Realnumber Character
%token <node> IF ELSE FOR WHILE CONTINUE BREAK RETURN
%token <node> ID
%token <node> COMMA SEMI
%token <node> PLUS MINUS MUL DIV MOD
%token <node> ASSIGN
%token <node> INCR
%token <node> ADDRESS
%token <node> AND OR NOT
%token <node> EQUAL NOTEQUAL GT GE LT LE
%token <node> OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET OPENCURLY CLOSECURLY
```

定义非终结符：

```c++
%type <node> Program GlobalDefinitionList GlobalDefinition Typer
%type <node> GlobalVariableList GlobalVariable Function ParameterList Parameter
%type <node> FunctionVariable FunctionCode Instruction Definition LocalVariableList
%type <node> LocalVariable Statement Expression Arguments
```

定义优先级和结合性：

```c++
%right ASSIGN
%left OR
%left AND
%left EQUAL NOTEQUAL GT GE LT LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%left OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET
```

###### 2.3.2 规则部分

按自顶向下的顺序构造语法树，部分文法如下：

```c++
Program
    :           GlobalDefinitionList {
                    $$ = new Node("", "Program", 1, $1);
                    ASTroot = $$;
                }
    ;

GlobalDefinitionList
    :           GlobalDefinition GlobalDefinitionList {
                    $$ = new Node("", "GlobalDefinitionList", 2, $1, $2);
                }
    |           %empty {
                    $$ = nullptr;
                }
    ;

GlobalDefinition
    :           Typer GlobalVariableList SEMI {
                    $$ = new Node("", "GlobalDefinition", 3, $1, $2, $3);
                }
    |           Typer Function {
                    $$ = new Node("", "GlobalDefinition", 2, $1, $2);
                }
    ;

Typer
    : //...
    ;

GlobalVariableList
    :           GlobalVariable COMMA GlobalVariableList {
                    $$ = new Node("", "GlobalVariableList", 3, $1, $2, $3);
                }
    |           GlobalVariable {
                    $$ = new Node("", "GlobalVariableList", 1, $1);
                }
    ;

GlobalVariable
    : //...
    ;

Function
    :           ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
                    $$ = new Node("", "Function", 7, $1, $2, $3, $4, $5, $6, $7);
                }
    ;

ParameterList
    : //...
    ;

Parameter
    :           Typer FunctionVariable {
                    $$ = new Node("", "Parameter", 2, $1, $2);
                }
    ;

FunctionVariable
    : //...
    ;          

FunctionCode
    : //...
    ;

Instruction
    :           Definition {
                    $$ = new Node("", "Instruction", 1, $1);
                }
    |           Statement {
                    $$ = new Node("", "Instruction", 1, $1);
                }
    ;

Definition
    :           Typer LocalVariableList SEMI{
                    $$ = new Node("", "Definition", 3, $1, $2, $3);
                }
    ;

LocalVariableList
    :           LocalVariable COMMA LocalVariableList {
                    $$ = new Node("", "LocalVariableList", 3, $1, $2, $3);
                }
    |           LocalVariable {
                    $$ = new Node("", "LocalVariableList", 1, $1);
                }
    ;

LocalVariable
    : //...
    ;

Statement
    : //...
    ;

Expression
    : //...
    ;

Arguments
    :           Expression COMMA Arguments {
                    $$ = new Node("", "Arguments", 3, $1, $2, $3);
                }
    |           Expression {
                    $$ = new Node("", "Arguments", 1, $1);
                }
    ;

%%
```

#### 2.4 抽象语法树可视化

<h5 align = "center">这里没写</h5>



## 第三章 语义分析



## 第四章 代码生成



## 第五章 测试样例



## 第六章 总结

