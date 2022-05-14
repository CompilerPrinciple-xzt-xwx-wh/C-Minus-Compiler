#include"generator.h"

extern llvm::LLVMContext context ;

llvm::Function* Generator::getCurFunction() {
    //TODO
}
void Generator::pushFunction(llvm::Function* func) {
    //TODO
}
void Generator::popFunction() {
    //TODO
}
llvm::Value* Generator::findValue(const std::string & name) {
    //TODO
}
llvm::Function* Generator::createPrintf() {
    //TODO
}
llvm::Function* Generator::createScanf() {
    //TODO
}
void Generator::generate(Node *root) {
    //TODO
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