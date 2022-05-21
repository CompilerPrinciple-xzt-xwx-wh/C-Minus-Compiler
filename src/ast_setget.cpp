/**
 * @file ast_setget.cpp
 * @brief separated from ast.cpp, define some public API for building process
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-11
 * @copyright Copyright (c) 2022
 * 
 */
#include"ast.h"
#include<cstdarg>
/**
 * @brief remove global variables from ast_setget.cpp
 * ASTroot, context and builder are defined in file globals.cpp
 * just extern used in local
 * modification log: 2022/5/14,11:10
 * modificated by: Wang Hui
 */
extern Node* ASTroot ;
extern llvm::LLVMContext context ;
extern llvm::IRBuilder<> builder(context) ;

/**
 * @brief Construct a new Node object
 * 
 * @param nodeName <string>
 * @param nodeType 
 * @param lineNo 
 */
Node::Node(string nodeName, string nodeType, int lineNo) {
    this->node_Name = nodeName ;
    this->node_Type = nodeType ;
    this->line_Count = lineNo ;
}

/**
 * @brief Construct a new Node object
 * this constructor is not suggested but still provided
 * constructor using string as nodeName's type is highly recommended
 * @param nodeName <char*>
 * @param nodeType 
 * @param Num 
 * modification log: 2022/5/10,19:46
 * modificated by: Wang Hui
 */
Node::Node(const char* nodeName, string nodeType, int lineNo) {
    this->node_Name = string(nodeName) ;
    this->node_Type = nodeType ;
    this->line_Count = lineNo ;
}

/**
 * @brief Construct a new Node object
 * 
 * @param nodeName 
 * @param nodeType 
 * @param childNum 
 * @param ... 
 */
Node::Node(string nodeName, string nodeType, int childNum, ...){
    this->node_Name = nodeName ;
    this->node_Type = nodeType ;
    this->child_Num = childNum ;
    this->child_Node = new Node*[childNum] ;
    va_list args ;
    va_start(args, childNum) ;
    for ( int i = 0; i < childNum; ++i ) 
        this->child_Node[i] = va_arg(args, Node*);
    this->line_Count = this->child_Node[0]->line_Count ;
    va_end(args);
}

/**
 * @brief Get the value's type of the node
 * if node is a Typer or Expression, return the corresponding type of the value
 * else return VOID (-1), inferring ERROR
 * @return int 
 */
int Node::getValueType(){
    if ( this->node_Type == "Typer" ) {
        if ( this->child_Node[0]->node_Name == "int" ) 
            return TYPE_INT ;
        if ( this->child_Node[0]->node_Name == "float" ) 
            return TYPE_FLOAT ;
        if ( this->child_Node[0]->node_Name == "double" )
            return TYPE_DOUBLE ;
        if ( this->child_Node[0]->node_Name == "char" )
            return TYPE_CHAR ;
    } else if ( this->node_Type == "Expression" ) {
        return this->val_Type ;
    } else 
        return TYPE_VOID ;
    //TODO,yet to be verified
}

/**
 * @brief Set the type of the node's value 
 * @param type 
 */
void Node::setValueType(int type){
    this->val_Type = type ;
}

/**
 * @brief Get operator used for builder to create casting process from src to dst
 * @param src 
 * @param dst 
 * @return llvm::Instruction::CastOps 
 * modification log: 2022/5/17,20:17
 * modificated by: Wang Hui
 */
llvm::Instruction::CastOps Node::getCastOperator(llvm::Type* src, llvm::Type* dst){
    if (src == llvm::Type::getFloatTy(context) && dst == llvm::Type::getInt32Ty(context)) 
        return llvm::Instruction::FPToSI ;
    else if (src == llvm::Type::getInt32Ty(context) && dst == llvm::Type::getFloatTy(context)) 
        return llvm::Instruction::SIToFP ;
    else if (src == llvm::Type::getInt8Ty(context) && dst == llvm::Type::getFloatTy(context)) 
        return llvm::Instruction::UIToFP ;
    else if (src == llvm::Type::getInt8Ty(context) && dst == llvm::Type::getInt32Ty(context)) 
        return llvm::Instruction::ZExt ;
    else if (src == llvm::Type::getInt32Ty(context) && dst == llvm::Type::getInt8Ty(context)) 
        return llvm::Instruction::Trunc ;
    // TODO
    // casting from char,int,float to bool
    else 
        throw logic_error("Error! Inappropriate typecast.");
}

/**
 * @brief static function in class Node
 * cast variable src from its raw type to dsts
 * @param src 
 * @param dst 
 * @return llvm::Value* 
 * modification log: 2022/5/17,20:04
 * modificated by: Wang Hui
 */
llvm::Value* Node::typeCast(llvm::Value* src, llvm::Type* dst){
    llvm::Instruction::CastOps op = getCastOperator(src->getType(), dst);
    return builder.CreateCast(op, src, dst, "tmptypecast");
}

/**
 * @brief allocate space for a variable
 * 
 * @param type 
 * @param arraySize 
 * @return llvm::Type* 
 * modification log: 2022/5/15,15:29
 * modificated by: Wang Hui
 */
llvm::Type* Node::getLlvmType(int type, int size){
    switch (type) {
        case TYPE_INT:
            return llvm::Type::getInt32Ty(context) ;
        case TYPE_INT_ARRAY:
            if ( size == 0 )
                return llvm::Type::getInt32PtrTy(context) ;
            else 
                return llvm::ArrayType::get(llvm::Type::getInt32Ty(context), size) ;
        case TYPE_FLOAT:
            return llvm::Type::getFloatTy(context);
        case TYPE_FLOAT_ARRAY:
            if ( size == 0 )
                return llvm::Type::getFloatPtrTy(context) ;
            else
                return llvm::ArrayType::get(llvm::Type::getFloatTy(context), size) ;
        case TYPE_CHAR:
            return llvm::Type::getInt8Ty(context);
        case TYPE_CHAR_ARRAY:
            if ( size == 0 ) 
                return llvm::Type::getInt8PtrTy(context) ;
            else
                return llvm::ArrayType::get(llvm::Type::getInt8Ty(context), size) ;
        case TYPE_DOUBLE:
            return llvm::Type::getDoubleTy(context) ;
        case TYPE_DOUBLE_ARRAY:
            if ( size == 0 )
                return llvm::Type::getDoublePtrTy(context) ;
            else
                return llvm::ArrayType::get(llvm::Type::getDoubleTy(context), size) ;
        default:
            break;
    }
    return llvm::Type::getVoidTy(context);
}

/**
 * @brief Overload function getLlvmType
 * used to create two-dimension array
 * @param type 
 * @param len 
 * @param wid 
 * @return llvm::Type* 
 * modification log: 2022/5/16,14:22
 * modificated by: Wang Hui
 */
llvm::Type* Node::getLlvmType(int type, int len, int wid ) {
    switch ( type ) {
        case TYPE_CHAR_ARRAY_ARRAY :
            /* code */
            if ( len == 0 ) 
                return llvm::PointerType::get(llvm::ArrayType::get(llvm::Type::getInt8Ty(context),wid) , 0 ) ;
            else
                return llvm::ArrayType::get(llvm::ArrayType::get(llvm::Type::getInt8Ty(context),wid), len) ;
        case TYPE_INT_ARRAY_ARRAY:
            if ( len == 0 ) 
                return llvm::PointerType::get(llvm::ArrayType::get(llvm::Type::getInt32Ty(context),wid) , 0) ;
            else 
                return llvm::ArrayType::get( llvm::ArrayType::get(llvm::Type::getInt32Ty(context),wid), len ) ;
        case TYPE_FLOAT_ARRAY_ARRAY:
            if ( len == 0 )
                return llvm::PointerType::get(llvm::ArrayType::get(llvm::Type::getFloatTy(context), wid) ,0 ) ;
            else 
                return llvm::ArrayType::get(llvm::ArrayType::get(llvm::Type::getFloatTy(context),wid), len) ;
        case TYPE_DOUBLE_ARRAY_ARRAY:
            if ( len == 0 ) 
                return llvm::PointerType::get(llvm::ArrayType::get(llvm::Type::getDoubleTy(context),wid),len) ;
        default:
            break;
    }
    return llvm::Type::getVoidTy(context) ;
} 

/**
 * @brief Resolve the names of VariableList to define
 * GlobalVariableList --> GlobalVariable COMMA GlobalVariableList | GlobalVariable
 * LocalVariableList --> LocalVariable COMMA LocalVariableList | LocalVariable
 * @param type 
 * @return vector<Variable> 
 * turn to CustomClass/variable.h to clarify Variable
 * modification log: 2022/5/15,14:02
 * modificated by: Wang Hui
 */
vector<pair<Variable,llvm::Value*>> Node::getNameList(int type) {
    vector<pair<Variable,llvm::Value*>> namelist ;
    Node* temp = this ;
    while ( true ) {
        Node* var = temp->child_Node[0] ;
        // Variable --> ID
        if ( var->child_Num == 1 ) {
            Variable variable(var->child_Node[0]->node_Name,type) ;
            namelist.push_back(make_pair(variable,nullptr)) ;
            var->child_Node[0]->setValueType(type) ;
        }
        // Variable --> ID OPENBRACKET INT CLOSEBRACKET
        else if ( var->child_Num == 4 ) {
            int size = stoi(var->child_Node[2]->node_Name) ;
            Variable variable(var->child_Node[0]->node_Name,type+ARRAY,size) ;
            namelist.push_back(make_pair(variable,nullptr)) ;
            var->child_Node[0]->setValueType(type+ARRAY) ;
        }
        // Variable --> ID OPENBRACKET INT CLOSEBRACKET OPENBRACKET INT CLOSEBRACKET
        else if ( var->child_Num == 7 ) {
            int one_dimension = stoi(var->child_Node[2]->node_Name), two_dimension = stoi(var->child_Node[5]->node_Name) ;
            Variable variable(var->child_Node[0]->node_Name,type+ARRAY+ARRAY,one_dimension*two_dimension,two_dimension) ;
            namelist.push_back(make_pair(variable,nullptr)) ;
            var->child_Node[0]->setValueType(type+ARRAY+ARRAY) ;
        }
        else if ( var->child_Num == 3 ) {
            // Variable --> ID ASSIGN Expression
            if ( var->child_Node[2]->node_Type == "Expression" ) {
                llvm::Value* ret = var->child_Node[2]->irBuildExpression() ;
                Variable variable(var->child_Node[0]->node_Name,type) ;
                namelist.push_back(make_pair(variable,ret)) ;
                var->child_Node[0]->setValueType(type) ;
            } 
            // Variable --> ID OPENBRACKET CLOSEBRACKET
            else {
                // out of use, C grammer do not allow statement like "int arr[];"
                // make sure statements like it not occur
                throw logic_error("Error! Size-unclear array's definition.") ; 
            }
        } 
        else 
            throw logic_error("Error! Wrong definition.") ;
        if ( temp->child_Num == 3 ) 
            temp = temp->child_Node[2] ;
        else 
            break;
    }
    return namelist ;
}

/**
 * @brief Get the arguments of a function's call
 * Arguments --> Expression COMMA Arguments | Expression
 * @return vector<llvm::Value *> 
 * modification log: 2022/5/19,20:18
 * modificated by: Wang Hui
 */
vector<llvm::Value *> Node::getArgumentList() {
    vector<llvm::Value*> args ;
    Node* list = this ;
    while ( true ) {
        Node* temp = list->child_Node[0] ;
        args.push_back( temp->irBuildExpression() ) ;
        if ( list->child_Num == 3 )
            list = list->child_Node[2] ;
        else 
            break ;
    }
    return args ;
}

/**
 * @brief I suppose function print do not need special args like scanf
 * for now, simply call function getArgumentList
 * @return vector<llvm::Value *> 
 * modification log: 2022/5/19,22:22
 * modificated by: Wang Hui
 */
vector<llvm::Value *> Node::getPrintArguments() {
    return this->getArgumentList() ;
    //TODO
}

/**
 * @brief Return the vector of ptrs to variable
 * Arguments --> Expression COMMA Arguments | Expression
 * @return vector<llvm::Value *> 
 * modification log: 
 * modificated by: 
 */
vector<llvm::Value *> Node::getInputArguments() {
    vector<llvm::Value *> args ;
    Node *list = this;
    while ( true ) {
        Node* temp = list->child_Node[0] ;
        // temp refers to Expression
        // Expression --> ID
        args.push_back( temp->irBuildLeftValue() ) ;
        if ( list->child_Num == 3 )
            list = list->child_Node[2] ;
        else 
            break ;
    }
    return args;
}

/**
 * @brief Get arguments when call function scanf()
 * Return the vector of ptrs to variable
 * Arguments --> Expression COMMA Arguments | Expression
 * @return vector<llvm::Value*> 
 * modification log: 2022/5/19,21:49
 * modificated by: Wang Hui
 */
vector<llvm::Value*> Node::getScanfArguments() {
    vector<llvm::Value*> args ;
    // scanf() always has a first argument of type const string like "..."
    args.push_back(this->child_Node[0]->irBuildExpression() ) ;
    Node* list = this->child_Node[2] ;
    while ( true ) {
        Node* temp = list->child_Node[0] ;
        args.push_back(temp->irBuildLeftValue() ) ;
        if ( list->child_Num == 3 ) 
            list = list->child_Node[2] ;
        else 
            break ;
    }
    return args ;
}

/**
 * @brief Get function's parameters in definition of global function
 * ParameterList --> Parameter COMMA ParameterList
 * ParameterList --> Parameter
 * ParameterList --> %empty
 * @return vector<pair<string, llvm::Type*>> 
 * modification log: 2022/5/15,20:04
 * modificated by: Wang Hui
 */
vector<pair<string, llvm::Type*>> Node::getParameterList(){
    vector<pair<string,llvm::Type*>> parameters ;
    // ParameterList --> %empty
    if ( this == nullptr ) 
        return parameters ;
    Node *list = this;
    while (true) {
        // list refers to ParameterList
        // ParameterList --> Parameter COMMA ParameterList | Parameter
        Node* para = list->child_Node[0];
        // para refers to Parameter
        // Parameter --> Typer FunctionVariable
        Node* fv = para->child_Node[1] ;
        // fv refers to FunctionVariable
        Node* ty = para->child_Node[0] ;
        // ty refers to Typer

        // FunctionVariable --> ID[] 
        if (fv->child_Num == 3) {
            llvm::Type* type = getLlvmType(ARRAY + ty->getValueType(), 0) ;
            parameters.push_back(make_pair(fv->child_Node[0]->node_Name, type ));
        }
        // FunctionVariable --> ID
        else if (fv->child_Num == 1) {
            llvm::Type* type = getLlvmType(VAR + ty->getValueType(), 0) ;
            parameters.push_back(make_pair(fv->child_Node[0]->node_Name, type));
        }
        // FunctionVariable --> ID[][n]
        else if (fv->child_Num == 6 ) {
            int bottomSize = stoi(fv->child_Node[4]->node_Name) ;
            llvm::Type* type = getLlvmType(ARRAY+ARRAY+ty->getValueType(), 0, bottomSize) ;
            parameters.push_back(make_pair(fv->child_Node[0]->node_Name, type)) ;
        } else 
            throw logic_error("Error! Wrong parameter definition.");
        // ParameterList --> Parameter COMMA ParameterList
        if (list->child_Num == 3)
            list = list->child_Node[2];
        // ParameterList --> Parameter
        else
            break;        
    }
    return parameters ;
}

/**
 * @brief 
 * jsonGen() is implemented in file visualization.cpp
 * @return Json::Value 
 * modification log: delete this function 2022/5/11,19:52
 * modificated by: Wang Hui
 */
// Json::Value Node::jsonGen(){
//     //
// }

/**
 * @brief Create a Entry Block Alloca object
 * Copied from project of last year
 * @param TheFunction 
 * @param VarName 
 * @param type 
 * @return llvm::AllocaInst* 
 * modification log: 2022/5/21,19:25
 * modificated by: Wang Hui
 */
llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type, nullptr, VarName);
}
