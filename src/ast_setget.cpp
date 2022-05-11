/**
 * @file ast_setget.cpp
 * @brief separated from ast.cpp, define some public API for building process
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-11
 * @copyright Copyright (c) 2022
 * 
 */
#include"ast.h"
#include<cstdarg>

/**
 * @brief 
 * var root is the root of program AST
 * extern used in parser.yacc, main.cpp, ast_builder.cpp
 * modification log: 2022/5/11,19:42
 * modificated by: Wang Hui
 */
Node* root;

/**
 * @brief Construct a new Node object
 * 
 * @param nodeName <string>
 * @param nodeType 
 * @param lineNo 
 */
Node::Node(string nodeName, string nodeType, int lineNo) {
    this->node_Name = nodeName ;
    this->node_Type = nodeType ;
    this->line_Count = lineNo ;
}

/**
 * @brief Construct a new Node object
 * this constructor is not suggested but still provided
 * constructor using string as nodeName's type is highly recommended
 * @param nodeName <char*>
 * @param nodeType 
 * @param Num 
 * modification log: 2022/5/10,19:46
 * modificated by: Wang Hui
 */
Node::Node(char* nodeName, string nodeType, int lineNo) {
    this->node_Name = string(nodeName) ;
    this->node_Type = nodeType ;
    this->line_Count = lineNo ;
}

/**
 * @brief Construct a new Node object
 * 
 * @param nodeName 
 * @param nodeType 
 * @param childNum 
 * @param ... 
 */
Node::Node(string nodeName, string nodeType, int childNum, ...){
    this->node_Name = nodeName ;
    this->node_Type = nodeType ;
    this->child_Num = childNum ;
    this->child_Node = new Node*[childNum] ;
    va_list args ;
    va_start(args, childNum) ;
    for ( int i = 0; i < childNum; ++i ) 
        this->child_Node[i] = va_arg(args, Node*);
    this->line_Count = this->child_Node[0]->line_Count ;
    va_end(args);
}

/**
 * @brief Get the value's type of the node
 * if node is a Typer or Expression, return the corresponding type of the value
 * else return VOID (-1), inferring ERROR
 * @return int 
 */
int Node::getValueType(){
    if ( this->node_Type == "Typer" ) {
        if ( this->child_Node[0]->node_Name == "int" ) 
            return TYPE_INT ;
        if ( this->child_Node[0]->node_Name == "floar" ) 
            return TYPE_FLOAT ;
        if ( this->child_Node[0]->node_Name == "double" )
            return TYPE_DOUBLE ;
        if ( this->child_Node[0]->node_Name == "char" )
            return TYPE_CHAR ;
    } else if ( this->node_Type == "Expression" ) {
        return this->val_Type ;
    } else 
        return VOID ;
    //TODO,yet to be verified
}

/**
 * @brief Set the type of the node's value 
 * @param type 
 */
void Node::setValueType(int type){
    this->val_Type = type ;
}

llvm::Instruction::CastOps Node::getCastInst(llvm::Type* src, llvm::Type* dst){
    //TODO
}
llvm::Value *Node::typeCast(llvm::Value* src, llvm::Type* dst){
    //TODO
}
llvm::Type* Node::getLlvmType(int type, int arraySize){
    //TODO
}

vector<pair<string, int>> *Node::getNameList(int type){
    //TODO
}
vector<llvm::Value *> *Node::getArgs(){
    //TODO
}
vector<llvm::Value *> *Node::getPrintArgs(){
    //TODO
}
vector<llvm::Value *> *Node::getArgsAddr(){
    //TODO
}
vector<pair<string, llvm::Type*>> *Node::getParam(){
    //TODO
}

/**
 * @brief 
 * jsonGen() is implemented in file visualization.cpp
 * @return Json::Value 
 * modification log: delete this function 2022/5/11,19:52
 * modificated by: Wang Hui
 */
// Json::Value Node::jsonGen(){
//     //TODO
// }