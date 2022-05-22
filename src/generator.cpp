/**
 * @file generator.cpp
 * @brief Implement the IR generator's function
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-20
 * @copyright Copyright (c) 2022
 * 
 */
<<<<<<< HEAD
#include "generator.h"

llvm::LLVMContext context;
llvm::IRBuilder<> builder(context);
Generator generator = Generator();
=======
#include"generator.h"

extern llvm::LLVMContext context ;
extern llvm::IRBuilder<> builder(context) ;
>>>>>>> f18219f66fd4ee16ed30b6aeb40faabe064cd852

llvm::Function* Generator::getCurFunction() {
    return this->getStack().top() ;
}
void Generator::pushFunction(llvm::Function* func) {
    this->getStack().push(func) ;
}
void Generator::popFunction() {
    this->getStack().pop() ;
}
llvm::Value* Generator::findValue(const std::string & name) {
    if ( !this->getStack().empty() ){
        llvm::Value* result = this->getStack().top()->getValueSymbolTable()->lookup(name) ;
        if (result != nullptr) 
            return result;
    }
    llvm::Value* result = this->getModule()->getGlobalVariable(name, true) ;
    if (result == nullptr) 
        throw logic_error("Error! Undeclared variable: "+name+".") ;
    else 
        return result;
}
llvm::Function* Generator::createPrintf() {
    std::vector<llvm::Type*> arg_types;
    arg_types.push_back(builder.getInt8PtrTy());
    auto printf_type = llvm::FunctionType::get(builder.getInt32Ty(), llvm::makeArrayRef(arg_types), true);
    auto func = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage, llvm::Twine("printf"), this->module);
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}
llvm::Function* Generator::createScanf() {
    auto scanf_type = llvm::FunctionType::get(builder.getInt32Ty(), true);
    auto func = llvm::Function::Create(scanf_type, llvm::Function::ExternalLinkage, llvm::Twine("scanf"), this->module);
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}
void Generator::generate(Node *root) {
    root->irBuild() ;
}

/**
 * @brief implementation of setter and getter
 * @return llvm::Module*, Function*, stack
 * modification log: 2022/5/14,11:30
 * modificated by: Wang Hui
 */
llvm::Module* Generator::getModule() {
    return this->module ;
}
llvm::Function* Generator::getPrint() {
    return this->printf ;
}
llvm::Function* Generator::getScan() {
    return this->scanf ;
}
stack<llvm::Function*>& Generator::getStack() {
    return this->funcStack ;
}

/**
 * @brief Constructor
 * initialize the module, printf, scanf and funStack
 * modification log: 2022/5/14,11:30
 * modificated by: Wang Hui
 */
Generator::Generator() {
    this->module = new llvm::Module("main", context);
    this->printf = this->createPrintf();
    this->scanf = this->createScanf();
}