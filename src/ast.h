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
    Node(string nodeName, string nodeType, int lineNo);

    /**
     * @brief Construct a new Node object
     * this constructor is not suggested but still provided
     * constructor using string as nodeName's type is highly recommended
     * @param nodeName (const char*)
     * @param nodeType 
     * @param Num 
     * modification log: 2022/5/10,19:46
     * modificated by: Wang Hui
     */
    Node(const char* nodeName, string nodeType, int Num) ;

    /**
     * @brief Construct a new Node object
     * @param nodeName 
     * @param nodeType 
     * @param childNum 
     * @param ... 
     */
    Node(string nodeName, string nodeType, int childNum, ...);

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
     * @brief functions above and these 
     * implemented in file ast_setget.cpp
     * modification log: 2022/5/11,20:11
     * modificated by: Wang Hui
     */
    llvm::Instruction::CastOps getCastInst(llvm::Type* src, llvm::Type* dst);
    llvm::Value *typeCast(llvm::Value* src, llvm::Type* dst);

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
     * @param type 
     * @return vector<variable> 
     * modification log: 2022/5/14,10:05
     * modificated by: Wang Hui
     */
    vector<Variable> getNameList(int type);
    vector<llvm::Value *> getArgs();
    vector<llvm::Value *> getPrintArgs();
    vector<llvm::Value *> getArgsAddr();
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
     * @return llvm::Value* 
     * modification log: 2022/5/14,10:01
     * modificated by: Wang Hui
     */
    llvm::Value *irBuildFunction();
    /**
     * @brief Rename functions
     * irBuildExp --> irBuildExpression, irBuildStmt --> irBuildStatement, irBuildCompSt --> irBuildCode
     * @return llvm::Value* 
     * modification log: 2022/5/14,22:27
     * modificated by: Wang Hui
     */
    llvm::Value *irBuildExpression();
    llvm::Value *irBuildStatement();
    llvm::Value *irBuildWhile();
    llvm::Value *irBuildIf();
    llvm::Value *irBuildReturn();
    llvm::Value *irBuildCode();
    llvm::Value *irBuildRELOP();
    llvm::Value *irBuildPrint();
    llvm::Value *irBuildPrintf();
    llvm::Value *irBuildScan();
    llvm::Value *irBuildAddr();

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