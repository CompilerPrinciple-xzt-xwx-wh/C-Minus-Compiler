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

using namespace std;

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
     *  "Paramater":                node of single parameter
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
     * @brief The number of line of the node in the file 
     */
    int line_Count;

    /**
     * @brief Construct a new Node object
     * 
     * @param nodeName 
     * @param nodeType 
     * @param lineNo 
     */
    Node(char * nodeName, string nodeType, int lineNo);

    /**
     * @brief Construct a new Node object
     * 
     * @param nodeName 
     * @param nodeType 
     * @param childNum 
     * @param ... 
     */
    Node(string nodeName, string nodeType, int childNum, ...);

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

    llvm::Value *irBuild();
    llvm::Value *irBuildExp();
    llvm::Value *irBuildFun();
    llvm::Value *irBuildVar();
    llvm::Value *irBuildStmt();
    llvm::Value *irBuildWhile();
    llvm::Value *irBuildIf();
    llvm::Value *irBuildReturn();
    llvm::Value *irBuildCompSt();
    llvm::Value *irBuildRELOP();
    llvm::Value *irBuildPrint();
    llvm::Value *irBuildPrintf();
    llvm::Value *irBuildScan();
    llvm::Value *irBuildAddr();
    llvm::Instruction::CastOps getCastInst(llvm::Type* src, llvm::Type* dst);
    llvm::Value *typeCast(llvm::Value* src, llvm::Type* dst);
    llvm::Type* getLlvmType(int type, int arraySize); 

    vector<pair<string, int>> *getNameList(int type);
    vector<llvm::Value *> *getArgs();
    vector<llvm::Value *> *getPrintArgs();
    vector<llvm::Value *> *getArgsAddr();
    vector<pair<string, llvm::Type*>> *getParam();
    Json::Value jsonGen();

    ~Node();
};

llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type);

#endif