#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <iostream>
#include <stack>
#include <map>
#include <string>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>
#include "ast.h"
#include "type.h"

#ifndef _STD_H_
#define _STD_H_
using namespace std ;
#endif

class Generator{

    llvm::Module *module ;
    llvm::Function *printf, *scanf ;
    stack<llvm::Function*> funcStack ;

public:
    /**
     * @brief Construct a new Generator object
     * initialize the module, printf, scanf and funStack
     * modification log: 2022/5/14,11:23
     * modificated by: Wang Hui
     */
    Generator();

    llvm::Function* getCurFunction() ;
    void pushFunction(llvm::Function* func) ;
    void popFunction() ;
    llvm::Value* findValue(const std::string & name) ;
    llvm::Function* createPrintf() ;
    llvm::Function* createScanf() ;
    void generate(Node *root) ;

    /**
     * @brief setter and getter
     * @return llvm::Module*, Function*, stack
     * modification log: 2022/5/14,11:21
     * modificated by: Wang Hui
     */
    llvm::Module* getModule() ;
    llvm::Function* getPrint() ;
    llvm::Function* getScan() ;
    stack<llvm::Function*>& getStack() ;
} ;

#endif