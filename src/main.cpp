/**
 * @file main.cpp
 * @brief define three processes of main
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-11
 * @copyright Copyright (c) 2022. Wang Hui, Xie Wenxiang and Xu Zhengtao.
 * 
 */

#include <iostream>
#include <fstream>
#include "ast.h"
#include "type.h"
#include "generator.h"

// #include"parser.y.h"

extern Node *ASTroot;
extern Generator generator;
extern int yyparse();

int main() {
    // parse the file
    yyparse();
    // TODO
    auto root = ASTroot->jsonGen();
    string jsonFile = "./ast_tree.json";
    std::ofstream astJson(jsonFile);
    if (astJson.is_open()) {
        astJson << root;
        astJson.close();
        //cout << "json write to " << jsonFile << endl;
    }
    // TODO
    // generate the LLVM IR
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    generator = Generator();
    generator.generate(ASTroot);
    // printf("Main finished!\n");
    return 0;
}