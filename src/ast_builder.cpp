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
#include "ast.h"
#include "generator.h"

extern Node* ASTroot ;
extern llvm::LLVMContext context ;
extern llvm::IRBuilder<> builder;
extern Generator generator;
extern stack<llvm::BasicBlock *> GlobalAfterBB ;

/**
 * @brief 
 * building process of root node Program
 * @return llvm::Value* 
 * modification log: 2022/5/26,11:06
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuild(){
    /**
     * @brief 
     * build Program
     * modification log: 2022/5/26,11:05
     * modificated by: Wang Hui
     */
    // Program --> GlobalDefinitionList
    Node* list = this->child_Node[0] ;
    while ( true ) {
        // GlobalDefinitionList --> GlobalDefinition GlobalDefinitionList | GlobalDefinition
        Node* def = list->child_Node[0] ;
        if ( def->child_Num == 3 ) 
            def->irBuildVariable() ;
        else
            def->irBuildFunction() ;
        if ( list->child_Num == 2 ) 
            list = list->child_Node[1] ;
        else 
            break ;
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
llvm::Value* Node::irBuildVariable(){
    int type = this->child_Node[0]->getValueType() ;
    vector<pair<Variable,llvm::Value*>> nameList = this->child_Node[1]->getNameList(type) ;
    // for ( auto it : nameList ) 
    //     cout<< it.first.getName() << ": " << it.second->getValueID() << endl ;
    llvm::Type *llvmType ;
    for (auto it : nameList) {
        llvmType = getLlvmType(it.first.getType(),it.first.getSize()) ;
        // global variable
        if (generator.getStack().empty()) {
            llvm::Value *tmp = generator.getModule()->getGlobalVariable(it.first.getName(), true) ;
            if ( tmp != nullptr ) 
                throw logic_error("Error! Redefined global variable: " + it.first.getName()+".") ;
            llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*generator.getModule(), llvmType, false, llvm::GlobalValue::PrivateLinkage, 0, it.first.getName()) ;
            // cout << "Global Variable Success!" << endl ;
        /*
            // Initialize the variable
            // adjust two-dimensional array only
            if ( llvmType->isArrayTy() ) {
                vector<llvm::Constant*> constArrayElem ;
                if ( llvmType->getArrayElementType()->isArrayTy() ) {
                    // constArray is supposed to be array of arrays
                    // Two-dimensional array is not initialized
                } 
                // one-dimension
                else {
                    llvm::Constant* constElem = llvm::ConstantInt::get(llvmType->getArrayElementType(), 0);
                    for (int i = 0; i < llvmType->getArrayNumElements(); i++) 
                        constArrayElem.push_back(constElem) ;
                    llvm::Constant* constArray = llvm::ConstantArray::get(llvm::ArrayType::get(llvmType->getArrayElementType(), llvmType->getArrayNumElements()), constArrayElem) ;
                    globalVar->setInitializer(constArray) ;
                }
            } else {
                globalVar->setInitializer(llvm::ConstantInt::get(llvmType, 0)) ;
            }
        */
            // Initial value is declared
            // Only support variable, do not support array
            if ( it.second != nullptr ) {
                llvm::Value* var = generator.findValue(it.first.getName()) ;
                llvm::Value* initial = it.second ;
                if ( initial->getType() != llvmType ) 
                    initial = typeCast(initial,llvmType) ;
                // cout<< var->isPointerTy() << endl ;
                builder.CreateStore(initial,var) ;
                // cout << "Global Variable Initialized!" << endl ;
            }
        }
        // local variable
        else {            
            llvm::Value *tmp = generator.getStack().top()->getValueSymbolTable()->lookup(it.first.getName());
            if(tmp != nullptr)
                throw logic_error("Error! Redefined local variable: " + it.first.getName()+".") ;
            llvm::Value* alloc = CreateEntryBlockAlloca(generator.getCurFunction(), it.first.getName(), llvmType) ;
            // cout << "Local Variable Success!" << endl ;
            if ( it.second != nullptr ) {
                llvm::Value* var = generator.findValue(it.first.getName()) ;
                llvm::Value* ini = it.second ;
                if ( ini->getType() != llvmType ) 
                    ini = typeCast(ini,llvmType) ;
                builder.CreateStore(ini,var) ;
                // cout << "Local Variable Initialized!" << endl ;
            }
        }
    }
    cout << "Variable success!" << endl ;
    return nullptr ;
}


/**
 * @brief Build function in global
 * GlobalDefinition --> Typer Function
 * Function --> ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log: 2022/5/15,20:01
 * modificated by: Wang Hui
 */
llvm::Function *Node::irBuildFunction(){

    cout << "Into function!" << endl ;
    // GlobalDefinition --> Typer Function
    Node* type = this->child_Node[0] ;
    Node* funcnode = this->child_Node[1] ;
    // funcnode refers to Function, type refers to typer

    // Function --> ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
    vector<pair<string,llvm::Type*>> parameters ;
    if ( child_Node[2] != nullptr ) 
        parameters = funcnode->child_Node[2]->getParameterList() ;

    cout << "Parameters get!" << endl ;
    
    vector<llvm::Type*> argTypes;
    for ( auto it : parameters ) 
        argTypes.push_back(it.second);
    llvm::FunctionType *functionType = llvm::FunctionType::get(getLlvmType(type->getValueType(), 0), argTypes, false) ;
    llvm::Function *function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, funcnode->child_Node[0]->node_Name, generator.getModule() ) ;
    // Check if Redifine function of the same name
    if ( function->getName() != funcnode->child_Node[0]->node_Name ) {
        function->eraseFromParent() ;
        function = generator.getModule()->getFunction(funcnode->child_Node[0]->node_Name) ;
    }
    
    cout << "Function declared!" << endl ;
    generator.pushFunction(function) ;

    llvm::BasicBlock *newBlock = llvm::BasicBlock::Create(context, "entrypoint", function) ;
    builder.SetInsertPoint(newBlock) ;
    
    // Set parameters's name
    if ( !parameters.empty() ) {
        int index = 0 ;
        for ( auto &Arg : function->args() ) 
            Arg.setName( parameters.at(index++).first ) ;
    }
    
    // Construct on FunctionCode
    if ( funcnode->child_Node[5] != nullptr ) 
        funcnode->child_Node[5]->irBuildCode() ;
    cout << "Function code built!" << endl ;

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
        cout << "Running at " << inst->line_Count << endl ;
        inst->irBuildInstruction() ;
        cout << "Running at " << inst->line_Count << "End!" << endl ;
        if ( totalCode->child_Num == 1 ) 
            break;
        else if ( totalCode->child_Num == 2 )
            totalCode = totalCode->child_Node[1] ;
    } 
    return nullptr ;
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
    return nullptr ;
}

/**
 * @brief Statement --> ...
 * @return llvm::Value* 
 * modification log: 2022/5/17,9:30
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildStatement(){
    Node* flag = this->child_Node[0] ;
    if ( flag == nullptr ) 
        return nullptr ;
    // Statement --> Expression SEMI
    if ( flag->node_Type == "Expression" ) 
        return flag->irBuildExpression() ;

    // Statement --> RETURN Expression SEMI
    // Statement --> RETURN SEMI
    if ( flag->node_Name == "return" ) 
        return this->irBuildReturn() ;

    // Statement --> IF ( Expression ) { FunctionCode }
    // Statement --> IF ( Expression ) { FunctionCode } ELSE { FunctionCode }
    if ( flag->node_Name == "if" ) 
        return this->irBuildIf() ;

    // Statement --> WHILE ( Expression ) { FunctionCode }
    if ( flag->node_Name == "while" ) 
        return this->irBuildWhile() ;

    // Statement --> FOR ( Expression SEMI Expression SEMI Expression ) { FunctionCode }
    if ( flag->node_Name == "for" ) 
        return this->irBuildFor() ;
    
    return nullptr ;
}

/**
 * @brief Expression --> ...
 * @return llvm::Value* 
 * modification log: 2022/5/18,14:52
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildExpression(){

    // // Expression --> %empty
    // if ( this == nullptr ) 
    //     return NULL ;

    // Expression --> Integer | Realnumber | Character
    if ( this->child_Num == 1 && this->child_Node[0]->node_Type != "ID" )
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
    if ( this->child_Node[0]->node_Type == "ID" && ( this->child_Num == 1 || this->child_Node[1]->node_Type == "OPENBRACKET" ) ) 
        return this->irBuildRightValue() ;

    /**
     * @brief call function
     * Expression --> ID OPENPAREN Arguments CLOSEPAREN 
     * Expression --> ID OPENPAREN CLOSEPAREN 
     * modification log: 2022/5/18,16:06
     * modificated by: Wang Hui
     */
    if ( this->child_Node[0]->node_Type == "ID" && this->child_Node[1]->node_Type == "OPENPAREN" ) 
        return this->irBuildCallFunction() ;
    
    return nullptr ;
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
    if ( this->child_Node[0]->node_Type == "Integer" )
        return builder.getInt32(stoi(this->child_Node[0]->node_Name)) ;
    // Expression --> Realnumber
    if ( this->child_Node[0]->node_Type == "Realnumber" ) 
        return llvm::ConstantFP::get(builder.getFloatTy(), llvm::APFloat(stof(this->child_Node[0]->node_Name))) ;
    // Expression --> String
    if ( this->child_Node[0]->node_Type == "String" ) 
        return builder.CreateGlobalStringPtr(this->child_Node[0]->node_Name) ;
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
    return nullptr ;
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
    return nullptr ;
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
    // Expression --> Expression ASSIGN Expression 
    if ( this->child_Node[1]->node_Type == "ASSIGN" ) {
        llvm::Value *lvalue = this->child_Node[0]->irBuildLeftValue() ;
        llvm::Value *rvalue = this->child_Node[2]->irBuildExpression() ;
        if (rvalue->getType() != lvalue->getType()->getPointerElementType()) 
            rvalue = typeCast(rvalue, lvalue->getType()->getPointerElementType()) ;
        return builder.CreateStore(rvalue, lvalue ) ;
    }
    
    llvm::Value *left = this->child_Node[0]->irBuildExpression() ;
    llvm::Value *right = this->child_Node[2]->irBuildExpression() ;
    // Expression --> Expression AND Expression
    if ( this->child_Node[1]->node_Type == "AND" ) 
        return typeCast( builder.CreateAnd(typeCast(left,llvm::Type::getInt1Ty(context)), typeCast(right,llvm::Type::getInt1Ty(context)), "tmpAnd"), llvm::Type::getInt32Ty(context) ) ;
    // Expression --> Expression OR Expression
    if ( this->child_Node[1]->node_Type == "OR" ) 
        return typeCast( builder.CreateOr(typeCast(left,llvm::Type::getInt1Ty(context)), typeCast(right,llvm::Type::getInt1Ty(context)), "tmpAnd"), llvm::Type::getInt32Ty(context) ) ;
    
    // Expression --> Expression MOD Expression
    if ( this->child_Node[1]->node_Type == "MOD" ){
        //TODO
    }
    // Cast type if left and right are different types
    if (left->getType() != right->getType()) {
        if (left->getType() == llvm::Type::getFloatTy(context)) 
            right = this->typeCast(right, llvm::Type::getFloatTy(context)) ;
        else if (right->getType() == llvm::Type::getFloatTy(context)) 
            left = this->typeCast(left, llvm::Type::getFloatTy(context));
        else if (left->getType() == llvm::Type::getInt32Ty(context)) 
            right = this->typeCast(right, llvm::Type::getInt32Ty(context));
        else if(right->getType() == llvm::Type::getInt32Ty(context)) 
            left = this->typeCast(left, llvm::Type::getInt32Ty(context));
        else 
            throw logic_error("Error! Unsupported operand type.");
    }
    // Expression --> Expression PLUS Expression
    if ( this->child_Node[1]->node_Type == "PLUS" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFAdd(left, right, "addtmpf") : builder.CreateAdd(left, right, "addtmpi") ;   
    // Expression --> Expression MINUS Expression
    if ( this->child_Node[1]->node_Type == "MINUS" ) 
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFSub(left, right, "addtmpf") : builder.CreateSub(left, right, "addtmpi") ;
    // Expression --> Expression MUL Expression
    if ( this->child_Node[1]->node_Type == "MUL" )
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFMul(left, right, "addtmpf") : builder.CreateMul(left, right, "addtmpi") ;
    // Expression --> Expression DIV Expression
    if ( this->child_Node[1]->node_Type == "DIV" )
        return (left->getType() == llvm::Type::getFloatTy(context)) ? builder.CreateFDiv(left, right, "addtmpf") : builder.CreateSDiv(left, right, "addtmpi") ;
    
    return nullptr ;
}

/**
 * @brief Get the pointer to assgin value
 *  Expression --> ID
 *  Expression --> ID [ Expression ]
 *  Expression --> ID [ Expression ] [ Expression ]
 * @return llvm::Value* 
 * modification log: 2022/5/19,16:58
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildLeftValue(){
    llvm::Value* id = generator.findValue( this->child_Node[0]->node_Name ) ;
    if ( this->child_Num == 1 ) {
        return id ;
    } else if ( this->child_Num == 4 ) {
        llvm::Value* idx = this->child_Node[2]->irBuildExpression() ;
        if ( idx->getType() != llvm::Type::getInt32Ty(context) ) 
            idx = this->typeCast( idx, llvm::Type::getInt32Ty(context) ) ;
        vector<llvm::Value*> indexList = { builder.getInt32(0),idx } ;
        return builder.CreateInBoundsGEP( id, llvm::ArrayRef<llvm::Value*>(indexList), "tmpvar" ) ;
    } else if( this->child_Num == 7 ) {
        llvm::Value* idx1 = this->child_Node[2]->irBuildExpression() ;
        llvm::Value* idx2 = this->child_Node[5]->irBuildExpression() ;

        if ( idx1->getType() != llvm::Type::getInt32Ty(context) ) 
            idx1 = this->typeCast( idx1, llvm::Type::getInt32Ty(context) ) ;
        if ( idx2->getType() != llvm::Type::getInt32Ty(context)) 
            idx2 = this->typeCast( idx2, llvm::Type::getInt32Ty(context) ) ;

        vector<llvm::Value*> indexList1 = { builder.getInt32(0), idx1 } ;
        llvm::Value* ptr_arr = builder.CreateInBoundsGEP(id, llvm::ArrayRef<llvm::Value*>(indexList1), "tmparr" ) ;
        llvm::Value* arr = builder.CreateLoad(ptr_arr->getType()->getPointerElementType(), ptr_arr, "tmparr") ;
        
        vector<llvm::Value*> indexList2 = { builder.getInt32(0), idx2 } ;
        return builder.CreateInBoundsGEP(arr, llvm::ArrayRef<llvm::Value*>(indexList2), "tmpvar" ) ;
    } else {
        //ERROR
        throw logic_error("Error! Invalid left value.") ;
    }
    return nullptr ;
}

/**
 * @brief Get the value of variable
 *  Expression --> ID
 *  Expression --> ID [ Expression ]
 *  Expression --> ID [ Expression ] [ Expression ]
 * @return llvm::Value* 
 * modification log: 2022/5/19,19:35
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildRightValue() {
    llvm::Value * id = generator.findValue(this->child_Node[0]->node_Name) ;
    // Expression --> ID
    if (this->child_Num == 1) {
        if (id->getType()->isPointerTy() && !(id->getType()->getPointerElementType()->isArrayTy()) ) 
            return builder.CreateLoad(id->getType()->getPointerElementType(), id, "tmpvar");
        else
            return id;
    }
    // Expression --> ID [ Expression ]
    if ( this->child_Num == 4 ) {
        llvm::Value* index = this->child_Node[2]->irBuildExpression() ;
        if ( index->getType() != llvm::Type::getInt32Ty(context)) 
            index = this->typeCast( index, llvm::Type::getInt32Ty(context) ) ;
        vector<llvm::Value*> indexList = { builder.getInt32(0), index};
        llvm::Value * varPtr = builder.CreateInBoundsGEP(id, llvm::ArrayRef<llvm::Value*>(indexList), "tmpvar") ;
        return builder.CreateLoad(varPtr->getType()->getPointerElementType(), varPtr, "tmpvar") ;
    }
    // Expression --> ID [ Expression ] [ Expression ]
    if ( this->child_Num == 7 ) {
        llvm::Value* idx1 = this->child_Node[2]->irBuildExpression() ;
        llvm::Value* idx2 = this->child_Node[5]->irBuildExpression() ;
        if ( idx1->getType() != llvm::Type::getInt32Ty(context) ) 
            idx1 = this->typeCast( idx1, llvm::Type::getInt32Ty(context) ) ;
        if ( idx2->getType() != llvm::Type::getInt32Ty(context)) 
            idx2 = this->typeCast( idx2, llvm::Type::getInt32Ty(context) ) ;
        vector<llvm::Value*> indexList1 = { builder.getInt32(0), idx1 } ;
        llvm::Value* ptr_arr = builder.CreateInBoundsGEP(id, llvm::ArrayRef<llvm::Value*>(indexList1), "tmparr" ) ;
        llvm::Value* arr = builder.CreateLoad(ptr_arr->getType()->getPointerElementType(), ptr_arr, "tmparr") ;
        
        vector<llvm::Value*> indexList2 = { builder.getInt32(0), idx2 } ;
        llvm::Value* ptr_var = builder.CreateInBoundsGEP(arr, llvm::ArrayRef<llvm::Value*>(indexList2), "tmpvar" ) ;
        return builder.CreateLoad(ptr_var->getType()->getPointerElementType(), ptr_var, "tmpvar" ) ;
    }

    return nullptr ;
}

/**
 * @brief Call of function
 * Expression --> ID OPENPAREN Arguments CLOSEPAREN 
 * Expression --> ID OPENPAREN CLOSEPAREN 
 * @return llvm::Value* 
 * modification log: 2022/5/19,19:28
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildCallFunction() {
    if (this->child_Node[0]->node_Name == "printf" ) 
        return this->irBuildPrintf() ;
    if (this->child_Node[0]->node_Name == "scanf" ) 
        return this->irBuildScanf() ;
    if (this->child_Node[0]->node_Name == "print" ) 
        return this->irBuildPrint() ;
    if (this->child_Node[0]->node_Name == "input" ) 
        return this->irBuildInput() ;
    llvm::Function *fun = generator.getModule()->getFunction( this->child_Node[0]->node_Name ) ;
    if (fun == nullptr) 
        throw logic_error("Error! Funtion not defined: " + this->child_Node[0]->node_Name+".") ;
    // Expression --> ID OPENPAREN CLOSEPAREN 
    if ( this->child_Num == 3 ) 
        return builder.CreateCall(fun, nullptr, "calltmp") ;
    // Expression --> ID OPENPAREN Arguments CLOSEPAREN
    vector<llvm::Value*> args = this->child_Node[2]->getArgumentList() ;
    return builder.CreateCall(fun, args, "calltmp");
}

/**
 * @brief Loop while statement
 * Statement --> WHILE OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log: 2022/5/19,20:35
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildWhile(){
    llvm::Function *TheFunction = generator.getCurFunction() ;
    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(context, "cond", TheFunction) ;
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(context, "loop", TheFunction) ;
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(context, "afterLoop", TheFunction) ;

    GlobalAfterBB.push(afterBB);
    
    //Cond
    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    // WHILE LP Exp RP Stmt
    llvm::Value *condValue = this->child_Node[2]->irBuildExpression() ;
    cout<< "while 1" << endl ;
    condValue = builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true), "whileCond");
    
    builder.CreateCondBr(condValue, loopBB, afterBB);
    // builder.SetInsertPoint(condBB) ;
    condBB = builder.GetInsertBlock();
    cout << "Into BodyCode" << endl ;
    //Loop
    builder.SetInsertPoint(loopBB);
    this->child_Node[5]->irBuildCode() ;
    builder.CreateBr(condBB);
    cout<< "loop after" << endl ;
    //After
    builder.SetInsertPoint(afterBB);
    //this->backward(generator);
    GlobalAfterBB.pop();
    return nullptr ;
}


/**
 * @brief For ( Expression ; Expression ; Expression ) { FunctionCode }
 * FOR OPENPAREN Expression SEMI Expression SEMI Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log:2022/5/17,11:09 
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildFor() {
    // Emit the start code first, without 'variable' in scope.
    llvm::Value* StartExp = this->child_Node[2]->irBuildExpression() ;
    Node* CodeBody = this->child_Node[9] ;

    // Make the new basic block for the loop header, inserting after current block.
    llvm::Function *TheFunction = builder.GetInsertBlock()->getParent() ;
    llvm::BasicBlock *PreheaderBB = builder.GetInsertBlock();
    llvm::BasicBlock *CondBB = llvm::BasicBlock::Create(context, "cond", TheFunction) ;
    llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(context, "loop", TheFunction) ;
    llvm::BasicBlock* AfterBB = llvm::BasicBlock::Create( context, "afterloop", TheFunction);
    
    GlobalAfterBB.push(AfterBB) ;

    // Insert an explicit fall through from the current block to the LoopBB.
    builder.CreateBr(CondBB) ;
    // Start insertion in LoopBB.
    builder.SetInsertPoint(CondBB) ;

    llvm::Value* EndExp = this->child_Node[4]->irBuildExpression() ;
    // Convert condition to a bool by comparing non-equal to 0.0.
    llvm::Value* EndCond = builder.CreateICmpNE(
        EndExp, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true), "forCond") ;

    // Insert the conditional branch into the end of LoopEndBB.
    builder.CreateCondBr(EndCond, LoopBB, AfterBB);

    CondBB = builder.GetInsertBlock();

    //Loop
    builder.SetInsertPoint(LoopBB);
    // Emit the body of the loop.  This, like any other expr, can change the
    // current BB.  Note that we ignore the value computed by the body, but don't
    // allow an error.
    CodeBody->irBuildCode() ;
    // Emit the step value.
    llvm::Value* StepExp = this->child_Node[6]->irBuildExpression() ;
    builder.CreateBr(CondBB);

    // Any new code will be inserted in AfterBB.
    builder.SetInsertPoint(AfterBB);
    GlobalAfterBB.pop() ;
    // for expr always returns 0.0.
    return nullptr ;
}

/**
 * @brief If statement
 * Statement --> IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY
 * Statement --> IF OPENPAREN Expression CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY ELSE OPENCURLY FunctionCode CLOSECURLY
 * @return llvm::Value* 
 * modification log: 2022/5/14,22:15
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildIf(){
    // llvm::Value *condValue = this->child_Node[2]->irBuildExpression() ;
    // condValue = builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true), "ifCond");

    // llvm::Function *TheFunction = generator.getCurFunction();
    // llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(context, "then", TheFunction);
    // llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(context, "else") ;
    // llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(context, "merge") ;

    // auto branch = builder.CreateCondBr(condValue, thenBB, elseBB);

    // llvm::PHINode* PN =
    //     builder.CreatePHI(llvm::Type::getDoubleTy(context), 2, "iftmp") ;

    // // Then

    // builder.SetInsertPoint(thenBB);
    // llvm::Value* thenValue = this->child_Node[5]->irBuildCode();
    // builder.CreateBr(mergeBB);
    // thenBB = builder.GetInsertBlock();
    // PN->addIncoming(thenValue, thenBB) ;

    // // else
    
    // if ( this->child_Num == 11 ) {
    //     TheFunction->getBasicBlockList().push_back(elseBB) ;
    //     builder.SetInsertPoint(elseBB) ;
    //     llvm::Value* elseValue = this->child_Node[9]->irBuildCode() ;
    //     builder.CreateBr(mergeBB) ;
    //     elseBB = builder.GetInsertBlock() ;
    //     PN->addIncoming(elseValue, elseBB) ;
    // }

    // TheFunction->getBasicBlockList().push_back(mergeBB) ;
    // builder.SetInsertPoint(mergeBB);    
    
    // return PN;
    llvm::Value *condValue = this->child_Node[2]->irBuildExpression(), *thenValue = nullptr, *elseValue = nullptr;
    condValue = builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true), "ifCond");

    cout << "Branch Notation!" << endl ;

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
    cout << "Branch Then!" << endl ;

    // else
    builder.SetInsertPoint(elseBB);
    if ( this->child_Num == 11 ) 
        elseValue = this->child_Node[9]->irBuildCode();
    elseBB = builder.GetInsertBlock();
    builder.CreateBr(mergeBB);
    cout << "Branch Else!" << endl ;

    builder.SetInsertPoint(mergeBB);    
    return branch;
}

/**
 * @brief Return statement in function
 * Expression --> RETURN Expression SEMI
 * Expression --> RETURN SEMI
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
        return nullptr ;
}

/**
 * @brief Build function print()
 * Expression --> print ( Arguments )
 * @return llvm::Value* 
 * modification log: 2022/5/19,21:43
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildPrint(){
    // cout << "Into print function!" << endl ;
    string formatStr = "";
    vector<llvm::Value *> args = this->child_Node[2]->getPrintArguments() ;
    cout << "Print arguments get!" << endl ;
    for (auto & arg : args) {
        if (arg->getType() == llvm::Type::getInt32Ty(context) ) 
            formatStr += "%d";
        else if (arg->getType() == llvm::Type::getInt8Ty(context) ) 
            formatStr += "%c";
        else if (arg->getType() == llvm::Type::getFloatTy(context) ) 
            formatStr += "%f";
        else if (arg->getType() == llvm::Type::getInt8PtrTy(context) ) 
            formatStr += "%s";
        else if (arg->getType()->getPointerElementType()->isArrayTy() && arg->getType()->getPointerElementType()->getArrayElementType() == builder.getInt8Ty()) {
            formatStr += "%s";
            vector<llvm::Value*> indexList;
            indexList.push_back(builder.getInt32(0));
            indexList.push_back(builder.getInt32(0));
            arg = builder.CreateGEP(arg, indexList);
        }
        else {
            throw logic_error("Error! Invalid type to write.");
        }
    }
    formatStr += "\n";
    auto formatConst = llvm::ConstantDataArray::getString(context, formatStr.c_str());
    auto formatStrVar = new llvm::GlobalVariable(*generator.getModule(), llvm::ArrayType::get(builder.getInt8Ty(), formatStr.size() + 1), true, llvm::GlobalValue::ExternalLinkage, formatConst, ".str");
    auto zero = llvm::Constant::getNullValue(builder.getInt32Ty());
    llvm::Constant* indices[] = {zero, zero};
    auto varRef = llvm::ConstantExpr::getGetElementPtr(formatStrVar->getType()->getElementType(), formatStrVar, indices);
    args.insert(args.begin(), varRef);
    cout << "Before CreateCall!" << endl ;
    return builder.CreateCall(generator.getPrint(), args, "print");
}

/**
 * @brief Build function input()
 * Expression --> input ( Arguments )
 * @return llvm::Value* 
 * modification log: 2022/5/19,20:38
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildInput() {
    string formatStr = "";
    vector<llvm::Value*> args = this->child_Node[2]->getInputArguments() ;
    for (auto arg : args) {
        if (arg->getType()->getPointerElementType() == builder.getInt32Ty()) 
            formatStr += "%d";
        else if (arg->getType()->getPointerElementType() == builder.getInt8Ty()) 
            formatStr += "%c";
        else if (arg->getType()->getPointerElementType() == builder.getInt1Ty()) 
            formatStr += "%d";
        else if (arg->getType()->getPointerElementType() == builder.getFloatTy())
            formatStr += "%f";
        else if (arg->getType()->getPointerElementType()->isArrayTy() && arg->getType()->getPointerElementType()->getArrayElementType() == builder.getInt8Ty())
            formatStr += "%s";
        else 
            throw logic_error("Error! Invalid type to read.") ;
    }
    args.insert(args.begin(), builder.CreateGlobalStringPtr(formatStr)) ;
    return builder.CreateCall(generator.getScan(), args, "input") ;
}

/**
 * @brief Build function printf()
 * Expression --> printf ( Arguments )
 * @return llvm::Value* 
 * modification log: 2022/5/19,20:37
 * modificated by: Wang Hui
 */
llvm::Value *Node::irBuildPrintf() {
    vector<llvm::Value *> args = this->child_Node[2]->getPrintArguments() ;
    return builder.CreateCall(generator.getPrint(), args, "printf") ;
}

/**
 * @brief Build function scanf()
 * Expression --> scanf ( Arguments )
 * @return llvm::Value* 
 * modification log: 2022/5/19,21:41
 * modificated by: Wang Hui
 */
llvm::Value* Node::irBuildScanf() {
    vector<llvm::Value*> args = this->child_Node[2]->getScanfArguments() ;
    return builder.CreateCall(generator.getScan(), args, "scanf" ) ;
}