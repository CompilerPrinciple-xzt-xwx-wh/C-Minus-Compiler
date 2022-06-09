/**
 * @file ast.h
 * @brief Definition of Node's structure and essential declarations of Node's API for Parsing
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-09
 * @copyright Copyright (c) 2022. Xu Zhengtao,Wang Hui and Xie Wenxiang. 
 * 
 */

#ifndef _AST_H_
#define _AST_H_

#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instruction.h>
#include <llvm/ADT/APFloat.h>
#include <json/json.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ostream>

#include "type.h"
#include "variable.h"

#ifndef _STD_H_
#define _STD_H_
using namespace std ;
#endif

class Variable ;

class Node {
public:
    
    /**
     * @brief 
     * Value or name of node, 
     * if type of node is int, the value of nodeName is the value of the integer, float, bool, char are similar
     * if type is var, the value is the name of this variable
     */
    string node_Name;
    
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
     *  "FunctionVariable":         node of name of each parameter
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
    
    /**
     * @brief The type of exp, var or const
     */
    int val_Type;
    
    /**
     * @brief The number of child of the node
     */
    int child_Num;
    
    /**
     * @brief Child nodes of this node
     */
    Node **child_Node;
    
    /**
     * @brief The number of line of which the node located in the file 
     */
    int line_Count;

    /**
     * @brief 
     * alteration of parameter's type ,nodeName: char* --> string
     * modification log: 2022/5/10,19:05
     * modificated by: Wang Hui
     */
    /**
     * @brief Construct a new Node object
     * @param nodeName 
     * @param nodeType 
     * @param lineNo
     */
    //Node(string nodeName, string nodeType, int lineNo);

    /**
     * @brief Construct a new Node object
     * this constructor is not suggested but still provided
     * constructor using string as nodeName's type is highly recommended
     * @param nodeName (const char*)
     * @param nodeType 
     * @param Num refers to the code's line number
     * modification log: 2022/5/10,19:46
     * modificated by: Wang Hui
     */
    Node(int Num, const char* nodeName, string nodeType ) ;
    Node(int Num, string nodeName, string nodeType ) ;

    /**
     * @brief Construct a new Node object
     * add a parameter that refers to code's line number
     * @param nodeName 
     * @param nodeType 
     * @param Num 
     * @param childNum 
     * @param ... 
     * modification log: 2022/5/24,18:53
     * modificated by: Wang Hui
     */
    Node(string nodeName, string nodeType, int childNum, ...) ;
    Node(const char* nodeName, string nodeType, int childNum, ...) ;

    /**
     * @brief delete the customization of destructor
     * modification log: 2022/5/10,19:22
     * modificated by: Wang Hui
     */

    /**
     * @brief Get the value's type of the node
     * if node is a Typer or Expression, return the corresponding type of the value
     * else return -1
     * @return int 
     */
    int getValueType();

    /**
     * @brief Set the type of the node's value 
     * @param type 
     */
    void setValueType(int type);

    /**
     * @brief Change access flag to static
     * for globally access when casting var's type
     * implemented in file ast_setget.cpp
     * modification log: 2022/5/17,20:15
     * modificated by: Wang Hui
     */
    static llvm::Instruction::CastOps getCastOperator(llvm::Type* src, llvm::Type* dst) ;

    /**
     * @brief Change the access flag
     * Designed to be static for globally access
     * @param src 
     * @param dst 
     * @return llvm::Value* 
     * modification log: 2022/5/17,20:02
     * modificated by: Wang Hui
     */
    static llvm::Value *typeCast(llvm::Value* src, llvm::Type* dst) ;

    /**
     * @brief Get the Llvm Type object
     * return variable of type like int, int[] ...
     * @param type 
     * @param arraySize 
     * @return llvm::Type* 
     * modification log: 2022/5/16,13:50
     * modificated by: Wang Hui
     */
    llvm::Type* getLlvmType(int type, int arraySize); 
    /**
     * @brief Get the Llvm Type object
     * Overload the getLlvmType for define two-dimension array
     * return type like int[len][wid] ...
     * @param type 
     * @param len 
     * @param wid 
     * @return llvm::Type* 
     * modification log: 2022/5/16,13:48
     * modificated by: Wang Hui
     */
    llvm::Type* getLlvmType(int type, int len, int wid ) ;

    /**
     * @brief getters for building
     * retype the return value, remove the pointer to vector
     * modification log: 2022/5/14,10:05
     * modificated by: Wang Hui
     */
    /**
     * @brief Get then name list of variables when definition
     * @param type 
     * @return vector<pair<Variable,llvm::Value*>> 
     * modification log: 2022/5/19,20:14
     * modificated by: Wang Hui
     */
    vector<pair<Variable,llvm::Value*>> getNameList(int type) ;
    /**
     * @brief Get arguments when call function print()
     * Expression --> print ( Arguments )
     * @return vector<llvm::Value *> 
     * modification log: 2022/5/19,22:20
     * modificated by: Wang Hui
     */
    vector<llvm::Value *> getPrintArguments() ;
    /**
     * @brief Get arguments when call function input()
     * Return the vector of ptrs to variable
     * @return vector<llvm::Value *> 
     * modification log: 2022/5/19,21:23
     * modificated by: Wang Hui
     */
    vector<llvm::Value *> getInputArguments() ;
    /**
     * @brief Get arguments when call function scanf()
     * Return the vector of ptrs to variable
     * @return vector<llvm::Value*> 
     * modification log: 2022/5/19,21:49
     * modificated by: Wang Hui
     */
    vector<llvm::Value*> getScanfArguments() ;
    /**
     * @brief Get the arguments for function's call
     * @return vector<llvm::Value *> 
     * modification log: 2022/5/19,20:15
     * modificated by: Wang Hui
     */
    vector<llvm::Value *> getArgumentList() ;
    /**
     * @brief Get the parameter list of a function for definition
     * @return vector<pair<string, llvm::Type*>> 
     * modification log: 2022/5/19,20:14
     * modificated by: Wang Hui
     */
    vector<pair<string, llvm::Type*>> getParameterList();

    /**
     * @brief for all builder functions below
     * implemented in file set_builder.cpp
     * irBuild() is the root function for program's building
     * @return llvm::Value* 
     * modification log: 2022/5/11,20:10
     * modificated by: Wang Hui
     */
    llvm::Value *irBuild();
    /**
     * @brief rename function irBuildVar()
     * irBuildVariable() build the variable for global and local
     * @return llvm::Value* 
     * modification log: 2022/5/14,10:00
     * modificated by: Wang Hui
     */
    llvm::Value *irBuildVariable();
    /**
     * @brief rename function irBuildFun()
     * irBuildFunction() build the function in the global
     * modify the return type
     * @return llvm::Function* 
     * modification log: 2022/5/26,11:09
     * modificated by: Wang Hui
     */
    llvm::Function *irBuildFunction();
    /**
     * @brief Rename functions
     * irBuildExp ~ irBuildExpression, irBuildStmt ~ irBuildStatement, irBuildCompSt ~ irBuildCode, irBuildRELOP ~ irBuildComparer
     * @return llvm::Value* 
     * modification log: 2022/5/14,22:27
     * modificated by: Wang Hui
     */
    llvm::Value *irBuildExpression();
    llvm::Value *irBuildStatement();
    llvm::Value *irBuildWhile();
    llvm::Value *irBuildIf();
    llvm::Value *irBuildReturn();
    /**
     * @brief 
     * Statement --> Continue SEMI
     * Statement --> Break SEMI
     * @return llvm::Value* 
     * modification log: 2022/6/9,22:05
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildBreak() ;
    llvm::Value* irBuildContinue() ;

    llvm::Value *irBuildCode();
    llvm::Value *irBuildComparer();

    /**
     * @brief print() and input() are like the way in python
     * 
     * @return llvm::Value* 
     * modification log: 2022/5/19,21:39
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildPrint();
    llvm::Value* irBuildInput();
    /**
     * @brief printf() and scanf() are supported
     * 
     * @return llvm::Value* 
     * modification log: 2022/5/19,21:38
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildPrintf() ;
    llvm::Value* irBuildScanf() ;
    
    /**
     * @brief Expression --> ID ...
     * LeftValue get the pointer when assign expression to a left_value
     * RightValue get the value of ID,ID[n],ID[n][m]
     * @return llvm::Value* 
     * modification log: 2022/5/19,16:56
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildLeftValue() ;
    llvm::Value* irBuildRightValue() ;

    /**
     * @brief Build each instruction in Function
     * Instruction --> Definition | Statement
     * @return llvm::Value* 
     * modification log: 2022/5/16,22:55
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildInstruction() ;

    /**
     * @brief for(;;){}
     * @return llvm::Value* 
     * modification log:2022/5/17,11:09 
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildFor() ;

    /**
     * @brief Build literal in code
     * @return llvm::Value* 
     * modification log: 2022/5/18,21:13
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildConst() ;

    /**
     * @brief Unary Operator includes !,++,-,&
     *        Binary Operators are +,-,*,&&,||,=,%
     * @return llvm::Value* 
     * modification log: 2022/5/18,20:57
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildUnaryOperator() ;
    llvm::Value* irBuildBinaryOperator() ;
    
    /**
     * @brief Build function's call
     * @return llvm::Value* 
     * modification log: 2022/5/19,19:26
     * modificated by: Wang Hui
     */
    llvm::Value* irBuildCallFunction() ;

    /**
     * @brief function jsonGen(), to visiualize AST
     * implemented in file visulization.cpp
     * @return Json::Value 
     * modification log: 2022/5/11,20:09
     * modificated by: Wang Hui
     */
    Json::Value jsonGen();

};

llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type);

#endif
