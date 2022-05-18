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
 * @brief Statement --> ...
 * @return llvm::Value* 
 * modification log: 2022/5/17,9:30
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildStatement(){
    Node* flag = this->child_Node[0] ;
    // Statement --> Expression SEMI
    if ( flag->node_Type == "Expression" ) 
        flag->irBuildExpression() ;

    // Statement --> RETURN Expression SEMI
    // Statement --> RETURN SEMI
    if ( flag->node_Name == "return" ) 
        this->irBuildReturn() ;

    // Statement --> IF ( Expression ) { FunctionCode }
    // Statement --> IF ( Expression ) { FunctionCode } ELSE { FunctionCode }
    if ( flag->node_Name == "if" ) 
        this->irBuildIf() ;

    // Statement --> WHILE ( Expression ) { FunctionCode }
    if ( flag->node_Name == "while" ) 
        this->irBuildWhile() ;

    // Statement --> FOR ( Expression SEMI Expression SEMI Expression ) { FunctionCode }
    if ( flag->node_Name == "for" ) 
        this->irBuildFor() ;
}

/**
 * @brief Expression --> ...
 * @return llvm::Value* 
 * modification log: 2022/5/18,14:52
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildExpression(){

    // Expression --> %empty
    if ( this == nullptr ) 
        return NULL ;

    // Expression --> Integer | Realnumber | Character
    if ( this->child_Num == 1 )
        return this->irBuildConst() ;

    /**
     * @brief Unary operator like: ! , - , ++ , &
     * Expression --> NOT Expression 
     * Expression --> MINUS Expression 
     * Expression --> INCR Expression
     * Expression --> ADDRESS Expression 
     * Expression --> Expression INCR 
     * modification log: 2022/5/18,20:25
     * modificated by: Wang Hui
     */
    if ( this->child_Num == 2 ) 
       return this->irBuildUnaryOperator() ;

    /**
     * @brief comparer of two expressions
     *  Expression --> Expression EQUAL Expression
     *  Expression --> Expression NOTEQUAL Expression
     *  Expression --> Expression GT Expression 
     *  Expression --> Expression GE Expression
     *  Expression --> Expression LT Expression
     *  Expression --> Expression LE Expression
     * modification log: 2022/5/18,17:05
     * modificated by: Wang Hui
     */
    if ( this->child_Num == 3 && 
            ( this->child_Node[1]->node_Type == "EQUAL" || 
              this->child_Node[1]->node_Type == "NOTEQUAL" || 
              this->child_Node[1]->node_Type == "GT" || 
              this->child_Node[1]->node_Type == "GE" || 
              this->child_Node[1]->node_Type == "LT" ||
              this->child_Node[1]->node_Type == "LE" ) )
        return this->irBuildComparer() ;

    /**
     * @brief binary operator
     * Expression --> Expression ASSIGN Expression
     * Expression --> Expression AND Expression
     * Expression --> Expression OR Expression 
     * Expression --> Expression PLUS Expression 
     * Expression --> Expression MINUS Expression 
     * Expression --> Expression MUL Expression 
     * Expression --> Expression DIV Expression 
     * Expression --> Expression MOD Expression 
     * modification log: 2022/5/18,20:51
     * modificated by: Wang Hui
     */
    if ( this->child_Num == 3 && this->child_Node[2]->node_Type == "Expression" && this->child_Node[0]->node_Type == "Expression" ) 
        return this->irBuildBinaryOperator() ;

    // Expression --> OPENPAREN Expression CLOSEPAREN 
    if ( this->child_Num == 3 && this->child_Node[1]->node_Type == "Expression" ) 
        return child_Node[1]->irBuildExpression() ;

    /**
     * @brief call array and variable
     * Expression --> ID OPENBRACKET Expression CLOSEPAREN OPENBRACKET Expression CLOSEPAREN
     * Expression --> ID OPENBRACKET Expression CLOSEPAREN 
     * Expression --> ID 
     * modification log: 2022/5/18,16:06
     * modificated by: Wang Hui
     */
    if ( this->child_Node[0]->node_Type == "ID" && ( this->child_Num == 1 || this->child_Node[1]->node_Type == "OPENBRACKET" ) ) {
        //TODO
    }

    /**
     * @brief call function
     * Expression --> ID OPENPAREN Arguments CLOSEPAREN 
     * Expression --> ID OPENPAREN CLOSEPAREN 
     * modification log: 2022/5/18,16:06
     * modificated by: Wang Hui
     */
    if ( this->child_Node[0]->node_Type == "ID" && this->child_Node[1]->node_Type == "OPENPAREN" ) {
        //TODO
    }

}

/**
 * @brief Build literal in code
 * Expression --> Integer
 * Expression --> Realnumber
 * Expression --> Character
 * @return llvm::Value* 
 * modification log: 2022/5/18,21:13
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildConst() {
    // Expression --> Integer
    if ( this->child_Node[0]->node_Type == " Integer" )
        return builder.getInt32(stoi(this->child_Node[0]->node_Name)) ;
    // Expression --> Realnumber
    if ( this->child_Node[0]->node_Type == "Realnumber" ) 
        return llvm::ConstantFP::get(builder.getFloatTy(), llvm::APFloat(stof(this->child_Node[0]->node_Name))) ;
    // Expression --> Character
    if ( this->child_Node[0]->node_Type == "Character" ) {
        if (this->child_Node[0]->node_Name.length() == 3)
            return builder.getInt8(this->child_Node[0]->node_Name[1]);
        else {
            if ( this->child_Node[0]->node_Name == "'\\n'" ) 
                return builder.getInt8('\n');
            else if (this->child_Node[0]->node_Name == "'\\\\'" ) 
                return builder.getInt8('\\');
            else if (this->child_Node[0]->node_Name == "'\\a'" ) 
                return builder.getInt8('\a');
            else if (this->child_Node[0]->node_Name == "'\\b'" ) 
                return builder.getInt8('\b');
            else if (this->child_Node[0]->node_Name == "'\\f'" ) 
                return builder.getInt8('\f');
            else if (this->child_Node[0]->node_Name == "'\\t'" ) 
                return builder.getInt8('\t');
            else if (this->child_Node[0]->node_Name == "'\\v'" ) 
                return builder.getInt8('\v');
            else if (this->child_Node[0]->node_Name == "'\\''" ) 
                return builder.getInt8('\'');
            else if (this->child_Node[0]->node_Name == "'\\\"'" ) 
                return builder.getInt8('\"');
            else if (this->child_Node[0]->node_Name == "'\\0'" ) 
                return builder.getInt8('\0');
             else 
                throw logic_error("Error! Invalid char: " + this->child_Node[0]->node_Name+"." ) ;
        }
    }
}

/**
 * @brief Build unary operator expression
 * Expression --> NOT Expression 
 * Expression --> MINUS Expression 
 * Expression --> INCR Expression
 * Expression --> Expression INCR 
 * Expression --> ADDRESS Expression 
 * @return llvm::Value* 
 * modification log: 2022/5/18,21:04
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildUnaryOperator() {
    if ( this->child_Node[0]->node_Type == "NOT" ) {
        llvm::Value* operand = this->child_Node[1]->irBuildExpression() ;
        // if ( tmp->getType() != llvm::Type::getInt1Ty(context) ) 
        //     throw logic_error("Error! Cannot use types other than bool in ! Exp") ;
        operand = typeCast(operand, llvm::Type::getInt32Ty(context)) ;
        return builder.CreateNot(operand, "tmpNot") ;
    } 
    if ( this->child_Node[0]->node_Type == "MINUS" ) {
        return builder.CreateNeg(this->child_Node[1]->irBuildExpression(), "tmpNeg") ;
    }
    if ( this->child_Node[0]->node_Type == "INCR" ) {
        //TODO
    }
    if ( this->child_Node[0]->node_Type == "ADDRESS" ) {
        //TODO
    }
    if ( this->child_Node[1]->node_Type == "INCR" ) {
        //TODO
    }
}

/**
 * @brief Build binary operator expression
 * Expression --> Expression ASSIGN Expression
 * Expression --> Expression AND Expression
 * Expression --> Expression OR Expression 
 * Expression --> Expression PLUS Expression 
 * Expression --> Expression MINUS Expression 
 * Expression --> Expression MUL Expression 
 * Expression --> Expression DIV Expression 
 * Expression --> Expression MOD Expression 
 * @return llvm::Value* 
 * modification log: 2022/5/18,21:06
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildBinaryOperator() {

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
 * @brief for(;;){}
 * FOR OPENPAREN Expression SEMI Expression SEMI Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log:2022/5/17,11:09 
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildFor() {
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
    llvm::Value *condValue = this->child_Node[2]->irBuildExpression(), *thenValue = nullptr, *elseValue = nullptr;
    condValue = builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true), "ifCond");

    llvm::Function *TheFunction = generator.getCurFunction();
    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(context, "then", TheFunction);
    llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(context, "else", TheFunction);
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(context, "merge", TheFunction);

    // Then
    auto branch = builder.CreateCondBr(condValue, thenBB, elseBB);
    
    builder.SetInsertPoint(thenBB);
    thenValue = this->child_Node[5]->irBuildCode();
    builder.CreateBr(mergeBB);
    thenBB = builder.GetInsertBlock();

    // else
    builder.SetInsertPoint(elseBB);
    if ( this->child_Num == 11 ) 
        elseValue = this->child_Node[9]->irBuildCode();
    builder.CreateBr(mergeBB);
    elseBB = builder.GetInsertBlock();

    builder.SetInsertPoint(mergeBB);    
    return branch;
}

/**
 * @brief Return statement in function
 * RETURN Expression SEMI
 * RETURN SEMI
 * @return llvm::Value* 
 * modification log: 2022/5/17,16:04
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildReturn(){
    // Statement --> RETURN Expression SEMI
    if (this->child_Num == 3) {
        auto returnInst = this->child_Node[1]->irBuildExpression();
        return builder.CreateRet(returnInst);
    } 
    // Statement --> RETURN SEMI
    else 
        return builder.CreateRetVoid();
}

/**
 * @brief 
 * Expression --> Expression EQUAL Expression
 * Expression --> Expression NOTEQUAL Expression
 * Expression --> Expression GT Expression
 * Expression --> Expression GE Expression
 * Expression --> Expression LT Expression
 * Expression --> Expression LE Expression
 * @return llvm::Value* 
 * modification log: 2022/5/17,19:58
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildComparer() {
    llvm::Value * left = this->child_Node[0]->irBuildExpression() ;
    llvm::Value * right = this->child_Node[2]->irBuildExpression() ;
    if ( left->getType() != right->getType() ) {
        if ( left->getType() == llvm::Type::getFloatTy(context) ) 
            right = typeCast(right, llvm::Type::getFloatTy(context));
        else if ( right->getType() == llvm::Type::getFloatTy(context) ) 
            left = typeCast(left, llvm::Type::getFloatTy(context));
        else {
            if (left->getType() == llvm::Type::getInt32Ty(context)) {
                right = typeCast(right, llvm::Type::getInt32Ty(context));
            } else if(right->getType() == llvm::Type::getInt32Ty(context)) {
                left = typeCast(left, llvm::Type::getInt32Ty(context));
            } else {
                throw logic_error("Error! Inappropriate values' type to compare.");
            }
        }
    }
    if ( this->child_Node[1]->node_Name == "==" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFCmpOEQ(left, right, "fcmptmp") : builder.CreateICmpEQ(left, right, "icmptmp");
    else if (this->child_Node[1]->node_Name == "!=" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFCmpONE(left, right, "fcmptmp") : builder.CreateICmpNE(left, right, "icmptmp");
    else if ( this->child_Node[1]->node_Name == ">=" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFCmpOGE(left, right, "fcmptmp") : builder.CreateICmpSGE(left, right, "icmptmp");
    else if (this->child_Node[1]->node_Name == "<=" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFCmpOLE(left, right, "fcmptmp") : builder.CreateICmpSLE(left, right, "icmptmp");
    else if (this->child_Node[1]->node_Name == ">" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFCmpOGT(left, right, "fcmptmp") : builder.CreateICmpSGT(left, right, "icmptmp");
    else if (this->child_Node[1]->node_Name == "<" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFCmpOLT(left, right, "fcmptmp") : builder.CreateICmpSLT(left, right, "icmptmp");
    else
        return NULL;
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
// Expression --> ID [ Expression ]
// Expression --> ID [ Expression ] [ Expression ]
llvm::Value *Node::irBuildAddr(){
    //TODO
}