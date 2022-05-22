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

int main()
{
    printf("0\n");
    // parse the file
    yyparse();

    printf("1\n");
    // TODO
    auto root = ASTroot->jsonGen();
    string jsonFile = "./ast_tree.json";
    std::ofstream astJson(jsonFile);
    if (astJson.is_open())
    {
        astJson << root;
        astJson.close();
        //cout << "json write to " << jsonFile << endl;
    }
    printf("2\n");
    // TODO
    // generate the LLVM IR
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    printf("3\n");
    generator = Generator();
    printf("4\n");
    generator.generate(ASTroot);
    printf("5\n");
    return 0;
}