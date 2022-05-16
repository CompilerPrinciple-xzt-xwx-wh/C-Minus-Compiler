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
    vector<Variable> nameList = this->child_Node[1]->getNameList(type) ;
    llvm::Type *llvmType ;
    for (auto it : nameList) {
        llvmType = getLlvmType(it.getType(),it.getSize()) ;
        // global variable
        if (generator.getStack().empty()) {
            llvm::Value *tmp = generator.getModule()->getGlobalVariable(it.getName(), true) ;
            if ( tmp != nullptr ) 
                throw logic_error("Error! Redefined global variable: " + it.getName()+".") ;
            llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*generator.getModule(), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, it.getName());
            if ( llvmType->isArrayTy() ) {
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
        }
        // local variable
        else {            
            llvm::Value *tmp = generator.getStack().top()->getValueSymbolTable()->lookup(it.getName());
            if(tmp != nullptr)
                throw logic_error("Redefined local variable: " + it.getName()+".") ;
            llvm::Value* alloc = CreateEntryBlockAlloca(generator.getCurFunction(), it.getName(), llvmType);
        }
    }
    return NULL;
}


llvm::Value *Node::irBuildExpression(){
    //TODO
}

/**
 * @brief Build function in global
 * GlobalDefinition --> Typer Function
 * Function --> ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log: 2022/5/15,20:01
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildFunction(){
    // GlobalDefinition --> Typer Function
    Node* funcnode = this->child_Node[1] ;
    // funcnode refers to Function

    // Function --> ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
    vector<pair<string,llvm::Type*>> parameters = funcnode->child_Node[2]->getParameterList() ;
    
    vector<llvm::Type*> argTypes;
    for ( auto it : parameters ) 
        argTypes.push_back(it.second);
    Node* type = this->child_Node[0] ;
    llvm::FunctionType *funcType = llvm::FunctionType::get(getLlvmType(type->getValueType(), 0), argTypes, false) ;
    llvm::Function *function = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, funcnode->child_Node[0]->node_Name, generator.getModule() ) ;
    generator.pushFunction(function) ;

    //Block
    llvm::BasicBlock *newBlock = llvm::BasicBlock::Create(context, "entrypoint", function);
    builder.SetInsertPoint(newBlock);
    
    //Parameters
    if ( !parameters.empty() ) {
        int index = 0;
        for ( auto &Arg : function->args() ) 
            Arg.setName( parameters.at(index++).first ) ;
    }
    
    // Construct on FunctionCode
    funcnode->child_Node[5]->irBuildCode();

    // Pop
    generator.popFunction() ;
    return function;
}

/**
 * @brief Rename irBuildCompSt to irBuildCode
 * FunctionCode --> Instruction FunctionCode
 * FunctionCode --> Instruction
 * @return llvm::Value* 
 * modification log: 2022/5/16,22:26
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildCode(){
    Node* totalCode = this ;
    // totalCode refers to FunctionCode
    while ( true ) {
        // FunctionCode --> Instruction FunctionCode | Instruction
        Node* inst = totalCode->child_Node[0] ;
        inst->irBuildInstruction() ;
        if ( totalCode->child_Num == 1 ) 
            break;
        else 
            totalCode = totalCode->child_Node[1] ;
    } 
    return NULL;
    //TODO
}

/**
 * @brief 
 * Instruction --> Definition | Statement
 * @return llvm::Value* 
 * modification log: 2022/5/16,22:57
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildInstruction(){
    // sonode refers to Definition or Statement
    Node* sonode = this->child_Node[0] ;
    // Instruction --> Definition
    if ( sonode->node_Type == "Definition" ) {
        sonode->irBuildVariable() ;
    }
    // Instruction --> Statement
    else {
        sonode->irBuildStatement() ;
    }
}

/**
 * @brief 
 * Instruction --> Statement
 * 
 * @return llvm::Value* 
 * modification log: 2022/5/14,22:12
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildStatement(){
    //TODO
}

/**
 * @brief Loop while statement
 * WHILE OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log: 2022/5/14,22:15
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildWhile(){
    //TODO
}

/**
 * @brief If statement
 * IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY ELSE OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log: 2022/5/14,22:15
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildIf(){
    //TODO
}

/**
 * @brief Return statement in function
 * RETURN Expression SEMI
 * RETURN SEMI
 * @return llvm::Value* 
 * modification log: 2022/5/14,22:17
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildReturn(){
    //TODO
}

/**
 * @brief 
 * Expression GT Expression
 * Expression GE Expression
 * Expression LT Expression
 * Expression LE Expression
 * @return llvm::Value* 
 * modification log: 2022/5/14,22:22
 * modificated by: Wang Hui
 */
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


// Expression --> ID
// Expression --> ID[Exp]
// Expression --> ID[]
llvm::Value *Node::irBuildAddr(){
    //TODO
}