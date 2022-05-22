/**
 * @file visualization.cpp
 * @brief define the AST's visulization using json tools
 * @author Wang Hui & Xu Zhengtao 
 * @version 2.0
 * @date 2022-05-12
 * @copyright Copyright (c) 2022
 * 
 */
#include "ast.h"
#include "type.h"

/**
 * @brief 
 * exlclude jsonGen() from ast.cpp
 * @return Json::Value 
 * modification log: 2022/5/12,21:39
 * modificated by: Xu Zhengtao
 */


Json::Value Node::jsonGen(){
    Json::Value root;
    string addstr = "";
    if(this->node_Type == "Typer" || this->node_Type == "Exp"){
        switch (this->getValueType())
        {
        case TYPE_VOID:
            addstr = "void"; break;
        case VAR:
            addstr = "var"; break;
        case ARRAY:
            addstr = "array"; break;
        case FUN:
            addstr = "function"; break;
        case TYPE_INT:
            addstr = "int"; break;
        case TYPE_INT_ARRAY:
            addstr = "int_Array"; break;
        case TYPE_FLOAT:
            addstr = "float"; break;
        case TYPE_FLOAT_ARRAY:
            addstr = "float_Array"; break;
        case TYPE_CHAR:
            addstr = "char"; break;
        case TYPE_CHAR_ARRAY:
            addstr = "char_Array"; break;
        case TYPE_DOUBLE:
            addstr = "double"; break;
        case TYPE_DOUBLE_ARRAY:
            addstr = "double_Array"; break;
        case POINTER:
            addstr = "pointer"; break;
        default:
            break;
        }
    }

    root["name"] = this->node_Type + (addstr == "" ? "" : ": " + addstr);

    for(int i = this->child_Num - 1; i >= 0; i--){
        if(this->child_Node[i]){
            root["children"].append(this->child_Node[i]->jsonGen());
        }
    }
    return root;
}
