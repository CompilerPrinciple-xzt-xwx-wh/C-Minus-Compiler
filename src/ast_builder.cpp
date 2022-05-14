/**
 * @file ast_builder.cpp
 * @brief separated from ast.cpp, 
 *        implement the function of building IR for LLVM's coding
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-11,20:00
 * @copyright Copyright (c) 2022
 * 
 */
#include"ast.h"
#include"generator.h"

extern Node* ASTroot ;
extern llvm::LLVMContext context ;
extern llvm::IRBuilder<> builder(context) ;
extern Generator generator ;

/**
 * @brief 
 * building process of all nodes in the global
 * @return llvm::Value* 
 * modification log: 2022/5/12,9:06
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuild(){
    /**
     * @brief 
     * first code implementation for IR builder
     * modification log: 2022/5/14,9:45
     * modificated by: Wang Hui
     */
    if (this->node_Type == "GlobalDefinition" ) {
        if (this->child_Node[1]->node_Type == "GlobalVariableList" ) {
            return this->irBuildVariable() ;
        } else {
            return this->irBuildFunction() ;
        }
    } else if (this->node_Type == "Definition" ) {
        return this->irBuildVariable() ;
    }
    for ( int i = 0; i < this->child_Num; i++) {
        if (this->child_Node[i] != nullptr)
            this->child_Node[i]->irBuild() ;
    }
    return NULL ;
}

/**
 * @brief Build variable for both global and local
 * GlobalDefinition --> Typer GlobalVariableList SEMI 
 * Definition --> Typer LocalVariableList SEMI
 * @return llvm::Value* 
 * modification log: 2022/5/14,9:50
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildVariable(){
    int type = this->child_Node[0]->getValueType() ;
    vector<pair<string, int>> nameList = this->child_Node[1]->getNameList(type) ;
    llvm::Type *llvmType ;
    for (auto it : nameList) {
        if (it.second == VAR) {
            llvmType = getLlvmType(type, 0) ;
        } else {
            llvmType = getLlvmType(type + ARRAY, it.second - ARRAY) ;
        }
        if (generator.getStack().empty()) {
            llvm::Value *tmp = generator.getModule()->getGlobalVariable(it.first, true) ;
            //Undefined rule, definition of var that share the same name with outer or global code's variable
            if(tmp != nullptr){
                throw logic_error("Redefined Variable: " + it.first) ;
            }
            llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*generator.getModule(), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, it.first);
            if (llvmType->isArrayTy()) {
                std::vector<llvm::Constant*> constArrayElem ;
                llvm::Constant* constElem = llvm::ConstantInt::get(llvmType->getArrayElementType(), 0);
                for (int i = 0; i < llvmType->getArrayNumElements(); i++) {
                    constArrayElem.push_back(constElem);
                }
                llvm::Constant* constArray = llvm::ConstantArray::get(llvm::ArrayType::get(llvmType->getArrayElementType(), llvmType->getArrayNumElements()), constArrayElem);
                globalVar->setInitializer(constArray);
            } else {
                globalVar->setInitializer(llvm::ConstantInt::get(llvmType, 0));
            }
            //if (generator->module->getGlobalVariable(it.first, true) == nullptr) {
            //    cout<<"ERROR"<<endl;
            //}
        }
        else {            
            llvm::Value *tmp = generator.getStack().top()->getValueSymbolTable()->lookup(it.first);
            if(tmp != nullptr){
                throw logic_error("Redefined Variable: " + it.first);
            }            
            llvm::Value* alloc = CreateEntryBlockAlloca(generator.getCurFunction(), it.first, llvmType);
        }
    }
    return NULL;
}


llvm::Value *Node::irBuildExp(){
    //TODO
}

// GlobalDefinition --> Typer Function
llvm::Value *Node::irBuildFunction(){
    //TODO
}

// Stmt
llvm::Value *Node::irBuildStmt(){
    //TODO
}

// WHILE LP Exp RP Stmt
llvm::Value *Node::irBuildWhile(){
    //TODO
}

// IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
// IF LP Exp RP Stmt ELSE Stmt
llvm::Value *Node::irBuildIf(){
    //TODO
}

// RETURN Exp SEMI
// RETURN SEMI
llvm::Value *Node::irBuildReturn(){
    //TODO
}


// CompSt --> LC DefList StmtList RC
// DefList --> Def DefList
// Def --> Specifier DecList SEMI
// StmtList --> Stmt StmtList
llvm::Value *Node::irBuildCompSt(){
    //TODO
}

// Exp RELOP Exp
llvm::Value *Node::irBuildRELOP(){
    //TODO
}

// Exp --> ID LP Args RP
llvm::Value *Node::irBuildPrint(){
    //TODO
}

llvm::Value *Node::irBuildPrintf(){
    //TODO
}

// Args --> Exp COMMA Args
// Args --> Exp
llvm::Value *Node::irBuildScan(){
    //TODO
}


// Exp --> ID
// Exp --> ID[Exp]
// Exp --> ID[]
llvm::Value *Node::irBuildAddr(){
    //TODO
}