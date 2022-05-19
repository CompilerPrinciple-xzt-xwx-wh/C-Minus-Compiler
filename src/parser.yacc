/*
 * @Author: xwxr
 * @Date: 2022-05-09 20:00:51
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-19 21:47:13
 * @Description: update the expression grammar
 */

/*
 * @Author: xwxr
 * @Date: 2022-05-09 20:00:51
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-18 16:14:37
 * @Description: update the representation of function parameter variables
 */

/*
 * @Author: xwxr
 * @Date: 2022-05-09 20:00:51
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-15 18:12:37
 * @Description: add 2d array implementation
 */

/*
 * @Author: xwxr
 * @Date: 2022-05-09 20:00:51
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-12 12:42:55
 * @Description: C-Minus Grammar Generator without error detection
 */

/*
 * @Author: xwxr
 * @Date: 2022-05-09 20:00:51
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-10 18:40:23
 * @Description: C-Minus Grammar Generator
 */
%{
    #include <stdio.h>
    #include "ast.h"
    #include "type.h"

    extern Node *ASTroot;
    int yylex(void);
    void yyerror(const char *);
%}

%union
{
    struct Node* node;
}
%token <node> CHAR INT FLOAT DOUBLE VOID
%token <node> Integer Realnumber Character String
%token <node> IF ELSE FOR WHILE CONTINUE BREAK RETURN
%token <node> ID
%token <node> COMMA SEMI
%token <node> PLUS MINUS MUL DIV MOD
%token <node> ASSIGN
%token <node> INCR_P INCR_M
%token <node> ADDRESS
%token <node> AND OR NOT
%token <node> EQUAL NOTEQUAL GT GE LT LE
%token <node> OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET OPENCURLY CLOSECURLY

%nonassoc INCR_P INCR_M
%nonassoc ELSE

// define associativity
%right ASSIGN
%left OR
%left AND
%left EQUAL NOTEQUAL GT GE LT LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%left OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET

%type <node> Program GlobalDefinitionList GlobalDefinition Typer
%type <node> GlobalVariableList GlobalVariable Function ParameterList Parameter
%type <node> FunctionVariable FunctionCode Instruction Definition LocalVariableList
%type <node> LocalVariable Statement Expression Arguments

%%
// the root of the AST
Program
    :           GlobalDefinitionList {
                    $$ = new Node("", "Program", 1, $1);
                    ASTroot = $$;
                }
    ;

// list of all the function and global var's definition
GlobalDefinitionList
    :           GlobalDefinition GlobalDefinitionList {
                    $$ = new Node("", "GlobalDefinitionList", 2, $1, $2);
                }
    |           %empty {
                    $$ = nullptr;
                }
    ;

// function or global var's definition
GlobalDefinition
    :           Typer GlobalVariableList SEMI {
                    $$ = new Node("", "GlobalDefinition", 3, $1, $2, $3);
                }
    |           Typer Function {
                    $$ = new Node("", "GlobalDefinition", 2, $1, $2);
                }
    ;

// 4 valid data type identifier
Typer
    :           CHAR {
                    $$ = new Node("", "Typer", 1, $1);
                }
    |           INT {
                    $$ = new Node("", "Typer", 1, $1);
                }
    |           FLOAT {
                    $$ = new Node("", "Typer", 1, $1);
                }
    |           DOUBLE {
                    $$ = new Node("", "Typer", 1, $1);
                }
    |           VOID {
                    $$ = new Node("", "Typer", 1, $1);
                }
    ;

// list of global var's definition for current data type's definition
GlobalVariableList
    :           GlobalVariable COMMA GlobalVariableList {
                    $$ = new Node("", "GlobalVariableList", 3, $1, $2, $3);
                }
    |           GlobalVariable {
                    $$ = new Node("", "GlobalVariableList", 1, $1);
                }
    ;

// global var's definition
GlobalVariable
    :           ID {
                    $$ = new Node("", "GlobalVariable", 1, $1);
                }
    // global one-dimensional array for definition
    |           ID OPENBRACKET INT CLOSEBRACKET {
                    $$ = new Node("", "GlobalVariable", 4, $1, $2, $3, $4);
                }
    // global two-dimensional array for definition
    |           ID OPENBRACKET INT CLOSEBRACKET OPENBRACKET INT CLOSEBRACKET{
                    $$ = new Node("", "GlobalVariable", 7, $1, $2, $3, $4, $5, $6, $7);
                }
    // initialization assignment
    |           ID ASSIGN Expression {
                    $$ = new Node("", "GlobalVariable", 3, $1, $2, $3);
                }
    ;

// function's definition
Function
    :           ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
                    $$ = new Node("", "Function", 7, $1, $2, $3, $4, $5, $6, $7);
                }
    ;

// list of function's parameters
ParameterList
    :           Parameter COMMA ParameterList {
                    $$ = new Node("", "ParameterList", 3, $1, $2, $3);
                }
    |           Parameter {
                    $$ = new Node("", "ParameterList", 1, $1);
                }
    |           VOID {
                    $$ = new Node("", "ParameterList", 1, $1);
                }
    |           %empty {
                    $$ = nullptr;
                }
    ;

// single parameter
Parameter
    :           Typer FunctionVariable {
                    $$ = new Node("", "Parameter", 2, $1, $2);
                }
    ;

// function parameter variables
FunctionVariable
    :           ID {
                    $$ = new Node("", "FunctionVariable", 1, $1);
                }
    // one-dimensional array for function parameter
    |           ID OPENBRACKET CLOSEBRACKET {
                    $$ = new Node("", "FunctionVariable", 3, $1, $2, $3);
                }
    // two-dimensional array for function parameter
    |           ID OPENBRACKET CLOSEBRACKET OPENBRACKET INT CLOSEBRACKET{
                    $$ = new Node("", "FunctionVariable", 6, $1, $2, $3, $4, $5, $6);
                }
    ;          

// all the instructions in a function
FunctionCode
    :           Instruction FunctionCode {
                    $$ = new Node("", "FunctionCode", 2, $1, $2);
                }
    |           Instruction {
                    $$ = new Node("", "FunctionCode", 1, $1);
                }
    |           %empty {
                    $$ = nullptr;
                }
    ;

// a single instruction
Instruction
    :           Definition {
                    $$ = new Node("", "Instruction", 1, $1);
                }
    |           Statement {
                    $$ = new Node("", "Instruction", 1, $1);
                }
    ;

// a single definition instruction
Definition
    :           Typer LocalVariableList SEMI{
                    $$ = new Node("", "Definition", 3, $1, $2, $3);
                }
    ;

// list of local vars' definition
LocalVariableList
    :           LocalVariable COMMA LocalVariableList {
                    $$ = new Node("", "LocalVariableList", 3, $1, $2, $3);
                }
    |           LocalVariable {
                    $$ = new Node("", "LocalVariableList", 1, $1);
                }
    ;

// local var's definition
LocalVariable
    :           ID {
                    $$ = new Node("", "LocalVariable", 1, $1);
                }
    //local one-dimensional array for definition
    |           ID OPENBRACKET INT CLOSEBRACKET {
                    $$ = new Node("", "LocalVariable", 4, $1, $2, $3, $4);
                }
    // local two-dimensional array for definition
    |           ID OPENBRACKET INT CLOSEBRACKET OPENBRACKET INT CLOSEBRACKET{
                    $$ = new Node("", "LocalVariable", 7, $1, $2, $3, $4, $5, $6, $7);
                }
    // initialization assignment
    |           ID ASSIGN Expression {
                    $$ = new Node("", "LocalVariable", 3, $1, $2, $3);
                }
    ;

// a single instruction but definition
Statement
    :           Expression SEMI {
                    $$ = new Node("", "Statement", 2, $1, $2);
                }
    |           RETURN Expression SEMI {
                    $$ = new Node("", "Statement", 3, $1, $2, $3);
                }
    |           RETURN SEMI {
                    $$ = new Node("", "Statement", 2, $1, $2);
                }
    |           BREAK SEMI {
                    $$ = new Node("", "Statement", 2, $1, $2);
                }
    |           CONTINUE SEMI {
                    $$ = new Node("", "Statement", 2, $1, $2);
                }
    |           IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
                    $$ = new Node("", "Statement", 7, $1, $2, $3, $4, $5, $6, $7);
                }
    |           IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY ELSE OPENCURLY FunctionCode CLOSECURLY {
                    $$ = new Node("", "Statement", 11, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);
                }
    |           WHILE OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
                    $$ = new Node("", "Statement", 7, $1, $2, $3, $4, $5, $6, $7);
                }
    |           FOR OPENPAREN Expression SEMI Expression SEMI Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
                    $$ = new Node("", "Statement", 11, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);
                }
    ;

// a single expression
Expression
    :           Expression ASSIGN Expression {
                    $$ = $1 = $3;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($3->getValueType());
                }
    |           Expression AND Expression {
                    $$ = $1 && $3;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression OR Expression {
                    $$ = $1 || $3;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           NOT Expression {
                    $$ = ~$2;
                    $$ = new Node("", "Expression", 2, $1, $2);
                    $$->setValueType(TYPE_INT);
                }
    |           MINUS Expression {
                    $$ = -$2;
                    $$ = new Node("", "Expression", 2, $1, $2);
                    $$->setValueType($2->getValueType());
                }
    |           INCR_P Expression {
                    $$ = $2 + 1;
                    $$ = new Node("", "Expression", 2, $1, $2);
                    $$->setValueType($2->getValueType());
                }
    |           Expression INCR_P {
                    $$ = $1 + 1;
                    $$ = new Node("", "Expression", 2, $1, $2);
                    $$->setValueType($1->getValueType());
                }
    |           INCR_M Expression {
                    $$ = $2 - 1;
                    $$ = new Node("", "Expression", 2, $1, $2);
                    $$->setValueType($2->getValueType());
                }
    |           Expression INCR_M {
                    $$ = $1 - 1;
                    $$ = new Node("", "Expression", 2, $1, $2);
                    $$->setValueType($1->getValueType());
                }
    // get the address
    |           ADDRESS Expression {
                    $$ = &$2;
                    $$ = new Node("", "Expression", 2, $1, $2);
                    $$->setValueType(TYPE_INT);
                }
    |           Expression PLUS Expression {
                    $$ = $1 + $2;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression MINUS Expression {
                    $$ = $1 - $2;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression MUL Expression {
                    $$ = $1 * $2;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression DIV Expression {
                    $$ = $1 / $2;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression MOD Expression {
                    $$ = $1 % $2;
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression EQUAL Expression {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression NOTEQUAL Expression {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression GT Expression {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression GE Expression {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression LT Expression {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           Expression LE Expression {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           OPENPAREN Expression CLOSEPAREN {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($2->getValueType());
                }
    // call function with arguments
    |           ID OPENPAREN Arguments CLOSEPAREN {
                    $$ = new Node("", "Expression", 4, $1, $2, $3, $4);
                    $$->setValueType($1->getValueType());
                }
    // call void function
    |           ID OPENPAREN CLOSEPAREN {
                    $$ = new Node("", "Expression", 3, $1, $2, $3);
                    $$->setValueType($1->getValueType());
                }
    |           ID OPENBRACKET Expression CLOSEPAREN {
                    $$ = new Node("", "Expression", 4, $1, $2, $3, $4);
                    $$->setValueType($1->getValueType() - ARRAY);
                }
    |           ID OPENBRACKET Expression CLOSEBRACKET OPENBRACKET Expression CLOSEBRACKET {
                    $$ = new Node("", "Expression", 7, $1, $2, $3, $4, $5, $6, $7);
                    $$->setValueType($1->getValueType() - ARRAY);
                }
    |           ID {
                    $$ = new Node("", "Expression", 1, $1);
                    $$->setValueType($1->getValueType());
                }
    |           Integer {
                    $$ = new Node("", "Expression", 1, $1);
                    $$->setValueType(TYPE_INT);
                }
    |           Realnumber {
                    $$ = new Node("", "Expression", 1, $1);
                    $$->setValueType($1->getValueType());
                }
    |           Character {
                    $$ = new Node("", "Expression", 1, $1);
                    $$->setValueType(TYPE_CHAR);
                }
    |           String {
                    $$ = new Node("", "Expression", 1, $1);
                    $$->setValueType(TYPE_CHAR_ARRAY);
                }
    |           %empty {
                    $$ = nullptr;
                }
    ;

// arguments
Arguments
    :           Expression COMMA Arguments {
                    $$ = new Node("", "Arguments", 3, $1, $2, $3);
                }
    |           Expression {
                    $$ = new Node("", "Arguments", 1, $1);
                }
    ;

%%

void yyerror(const char * s) {
    fprintf (stderr, "%s\n", s);
}