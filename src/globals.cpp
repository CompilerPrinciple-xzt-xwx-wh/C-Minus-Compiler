/**
 * @file globals.cpp
 * @brief define globally-used variables: ASTroot, context, builder and generator
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-14
 * @copyright Copyright (c) 2022
 * 
 */
#include "ast.h"
#include "generator.h"

/**
 * @brief rename root as ASTroot
 * since parser.yacc has already declared to use extern ASTroot
 * modification log: 2022/5/12,11:11
 * modificated by: Wang Hui
 */
/**
 * @brief var root is the root of program AST
 * extern used in parser.yacc, main.cpp, ast_builder.cpp
 * modification log: 2022/5/11,19:42
 * modificated by: Wang Hui
 */
Node* ASTroot ;

/**
 * @brief context and builder are global variables
 * extern used in ast_builder.cpp, ast_setget.cpp, generator.cpp
 * modification log: 2022/5/14,10:30
 * modificated by: Wang Hui
 */
// llvm::LLVMContext context ;
// llvm::IRBuilder<> builder(context) ;

/**
 * @brief generator to code IR
 * extern used in ast_setget.cpp, main.cpp, ast_builder.cpp and generator.cpp
 * @return Generator
 * modification log: 2022/5/14,11:37
 * modificated by: Wang Hui
 */
extern Generator generator;

/**
 * @brief Environment of current code block
 * modification log: 2022/5/19,20:31
 * modificated by: Wang Hui
 */
stack<llvm::BasicBlock *> GlobalAfterBB ;