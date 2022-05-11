/*
 * @Author: xwxr
 * @Date: 2022-05-09 20:00:51
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-10 21:45:32
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
%token <node> Integer Realnumber Character
%token <node> IF ELSE FOR WHILE CONTINUE BREAK RETURN
%token <node> ID
%token <node> COMMA SEMI
%token <node> PLUS MINUS MUL DIV MOD
%token <node> ASSIGN
%token <node> INCR
%token <node> AND OR NOT
%token <node> EQUAL NOTEQUAL GT GE LT LE
%token <node> OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET OPENCURLY CLOSECURLY

%nonassoc INCR
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
%type <node> FunctionCode Instruction Definition LocalVariableList LocalVariable
%type <node> Statement Expression Arguments

%%
// the root of the AST
Program:
    GlobalDefinitionList {
        $$ = new Node("", "Program", 1, $1);
        ASTroot = $$;
    }
    ;

// list of all the function and global var's definition
GlobalDefinitionList:
    GlobalDefinition GlobalDefinitionList {
        $$ = new Node("", "GlobalDefinitionList", 2, $1, $2);
    }
    | %empty {
        $$ = nullptr;
    }
    ;

// function or global var's definition
GlobalDefinition:
    Typer GlobalVariableList SEMI {
        $$ = new Node("", "GlobalDefinition", 3, $1, $2, $3);
    }
    | Typer Function SEMI {
        $$ = new Node("", "GlobalDefinition", 3, $1, $2, $3);
    }
    ;

// 4 valid data type identifier
Typer:
    CHAR {
        $$ = new Node("", "Typer", 1, $1);
    }
    | INT {
        $$ = new Node("", "Typer", 1, $1);
    }
    | FLOAT {
        $$ = new Node("", "Typer", 1, $1);
    }
    | DOUBLE {
        $$ = new Node("", "Typer", 1, $1);
    }
    | VOID {
        $$ = new Node("", "Typer", 1, $1);
    }
    ;

// list of global var's definition for current data type's definition
GlobalVariableList:
    GlobalVariable COMMA GlobalVariableList {
        $$ = new Node("", "GlobalVariableList", 3, $1, $2, $3);
    }
    | GlobalVariable {
        $$ = new Node("", "GlobalVariableList", 1, $1);
    }
    ;

// global var's definition
GlobalVariable:
    ID {
        $$ = new Node("", "GlobalVariable", 1, $1);
    }
    | ID OPENBRACKET INT CLOSEBRACKET {
        $$ = new Node("", "GlobalVariable", 4, $1, $2, $3, $4);
    }
    ;

// function's definition
Function:
    ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
        $$ = new Node("", "Function", 7, $1, $2, $3, $4, $5, $6, $7);
    }
    ;

// list of function's parameters
ParameterList:
    Parameter COMMA ParameterList {
        $$ = new Node("", "ParameterList", 3, $1, $2, $3);
    }
    | Parameter {
        $$ = new Node("", "ParameterList", 1, $1);
    }
    | VOID {
        $$ = new Node("", "ParameterList", 1, $1);
    }
    | %empty {
        $$ = nullptr;
    }
    ;

// single parameter
Parameter:
    Typer LocalVariable {
        $$ = new Node("", "Parameter", 2, $1, $2);
    }
    ;

// all the instructions in a function
FunctionCode:
    Instruction FunctionCode {
        $$ = new Node("", "FunctionCode", 2, $1, $2);
    }
    | Instruction {
        $$ = new Node("", "FunctionCode", 1, $1);
    }
    | %empty {
        $$ = nullptr;
    }
    ;

// a single instruction
Instruction:
    Definition {
        $$ = new Node("", "Instruction", 1, $1);
    }
    | Statement {
        $$ = new Node("", "Instruction", 1, $1);
    }
    ;

// a single definition instruction
Definition:
    Typer LocalVariableList SEMI{
        $$ = new Node("", "Definition", 3, $1, $2, $3);
    }
    ;

// list of local vars' definition
LocalVariableList:
    LocalVariable COMMA LocalVariableList {
        $$ = new Node("", "LocalVariableList", 3, $1, $2, $3);
    }
    | LocalVariable {
        $$ = new Node("", "LocalVariableList", 1, $1);
    }
    ;

// local var's definition
LocalVariable:
    ID {
        $$ = new Node("", "LocalVariable", 1, $1);
    }
    | ID OPENBRACKET INT CLOSEBRACKET {
        $$ = new Node("", "LocalVariable", 4, $1, $2, $3, $4);
    }
    | ID OPENBRACKET CLOSEBRACKET {
        $$ = new Node("", "LocalVariable", 3, $1, $2, $3);
    }
    ;

// a single instruction but definition
Statement:
    Expression SEMI {
        $$ = new Node("", "Statement", 2, $1, $2);
    }
    | RETURN Expression SEMI {
        $$ = new Node("", "Statement", 3, $1, $2, $3);
    }
    | RETURN SEMI {
        $$ = new Node("", "Statement", 2, $1, $2);
    }
    | BREAK SEMI {
        $$ = new Node("", "Statement", 2, $1, $2);
    }
    | CONTINUE SEMI {
        $$ = new Node("", "Statement", 2, $1, $2);
    }
    | IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
        $$ = new Node("", "Statement", 7, $1, $2, $3, $4, $5, $6, $7);
    }
    | IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY ELSE OPENCURLY FunctionCode CLOSECURLY {
        $$ = new Node("", "Statement", 11, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);
    }
    | WHILE OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
        $$ = new Node("", "Statement", 7, $1, $2, $3, $4, $5, $6, $7);
    }
    | FOR OPENPAREN Expression SEMI Expression SEMI Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
        $$ = new Node("", "Statement", 11, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);
    }
    | Expression {
        $$ = new Node("", "Statement", 1, $1);
    }
    ;

// a single expression
Expression:
    Expression ASSIGN Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($3->getValueType());
    }
    | Expression AND Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression OR Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | NOT Expression {
        $$ = new Node("", "Expression", 2, $1, $2);
        $$->setValueType($2->getValueType());
    }
    | INCR Expression {
        $$ = new Node("", "Expression", 2, $1, $2);
        $$->setValueType($2->getValueType());
    }
    | Expression INCR {
        $$ = new Node("", "Expression", 2, $1, $2);
        $$->setValueType($1->getValueType());
    }
    | Expression PLUS Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression MINUS Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression MUL Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression DIV Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression MOD Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression EQUAL Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression NOTEQUAL Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression GT Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression GE Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression LT Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | Expression LE Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | OPENPAREN Expression CLOSEPAREN {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($2->getValueType());
    }
    | ID OPENPAREN Arguments CLOSEPAREN {
        $$ = new Node("", "Expression", 4, $1, $2, $3, $4);
        $$->setValueType($1->getValueType());
    }
    | ID OPENPAREN CLOSEPAREN {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | ID OPENBRACKET Expression CLOSEPAREN {
        $$ = new Node("", "Expression", 4, $1, $2, $3, $4);
        $$->setValueType($1->getValueType());
    }
    | ID OPENBRACKET CLOSEBRACKET {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($1->getValueType());
    }
    | ID {
        $$ = new Node("", "Expression", 1, $1);
        $$->setValueType($1->getValueType());
    }
    | Integer {
        $$ = new Node("", "Expression", 1, $1);
        $$->setValueType(TYPE_INT);
    }
    | Realnumber {
        $$ = new Node("", "Expression", 1, $1);
        $$->setValueType($1->getValueType());
    }
    | Character {
        $$ = new Node("", "Expression", 1, $1);
        $$->setValueType(TYPE_CHAR);
    }
    | %empty {
        $$ = nullptr;
    }

// arguments
Arguments:
    Expression COMMA Arguments {
        $$ = new Node("", "Arguments", 3, $1, $2, $3);
    }
    | Expression {
        $$ = new Node("", "Arguments", 1, $1);
    }
    ;

%%

void yyerror(const char *) {
    fprintf (stderr, "%s\n", s);
}