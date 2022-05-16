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
Node::Node(char* nodeName, string nodeType, int lineNo) {
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

llvm::Instruction::CastOps Node::getCastInst(llvm::Type* src, llvm::Type* dst){
    //TODO
}
llvm::Value *Node::typeCast(llvm::Value* src, llvm::Type* dst){
    //TODO
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
            return llvm::ArrayType::get(llvm::Type::getInt32Ty(context), size) ;
        case TYPE_INT_ARRAY_ARRAY:
            //TODO
            break;
        
        case TYPE_FLOAT:
            return llvm::Type::getFloatTy(context);
        case TYPE_FLOAT_ARRAY:
            return llvm::ArrayType::get(llvm::Type::getFloatTy(context), size) ;
        case TYPE_FLOAT_ARRAY_ARRAY:
            //TODO
            break; 

        case TYPE_CHAR:
            return llvm::Type::getInt8Ty(context);
        case TYPE_CHAR_ARRAY:
            return llvm::ArrayType::get(llvm::Type::getInt8Ty(context), size) ;
        case TYPE_CHAR_ARRAY_ARRAY:
            //TODO
            break;
        
        case TYPE_DOUBLE:
            return llvm::Type::getDoubleTy(context) ;
        case TYPE_DOUBLE_ARRAY:
            return llvm::ArrayType::get(llvm::Type::getDoubleTy(context), size) ;
        case TYPE_DOUBLE_ARRAY_ARRAY:
            //TODO
            break;

        default:
            break;
    }
    return llvm::Type::getVoidTy(context);
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
vector<Variable> Node::getNameList(int type){
    vector<Variable> namelist ;
    Node* temp = this ;
    while ( true ) {
        Node* var = temp->child_Node[0] ;
        // Variable --> ID
        if ( var->child_Num == 1 ) {
            Variable variable(var->child_Node[0]->node_Name,type) ;
            namelist.push_back(variable);
            var->child_Node[0]->setValueType(type) ;
        }
        // Variable --> ID OPENBRACKET INT CLOSEBRACKET
        else if ( var->child_Num == 4 ) {
            int size = stoi(var->child_Node[2]->node_Name) ;
            Variable variable(var->child_Node[0]->node_Name,type+ARRAY,size) ;
            namelist.push_back(variable) ;
            var->child_Node[0]->setValueType(type+ARRAY) ;
        }
        // Variable --> ID OPENBRACKET INT CLOSEBRACKET OPENBRACKET INT CLOSEBRACKET
        else if ( var->child_Num == 7 ) {
            int one_dimension = stoi(var->child_Node[2]->node_Name), two_dimension = stoi(var->child_Node[5]->node_Name) ;
            Variable variable(var->child_Node[0]->node_Name,type+ARRAY+ARRAY,one_dimension*two_dimension,two_dimension) ;
            namelist.push_back(variable) ;
            var->child_Node[0]->setValueType(type+ARRAY+ARRAY) ;
        }
        else if ( var->child_Num == 3 ) {
            // Variable --> ID ASSIGN Expression
            if ( var->child_Node[2]->node_Type == "Expression" ) {
                //TODO
            } 
            // Variable --> ID OPENBRACKET CLOSEBRACKET
            else {
                // out of use, C grammer do not allow statement like "int arr[];"
                // make sure statements like it not occur
                throw logic_error("Error! Size-unclear array's definition.") ; 
            }
        } 
        else {
            throw logic_error("Error! Wrong definition.") ;
        }
        if ( temp->child_Num == 1 ) 
            break;
        else // iterative construction
            temp = temp->child_Node[2] ;
    }
    return namelist ;
}
vector<llvm::Value *> Node::getArgs(){
    //TODO
}
vector<llvm::Value *> Node::getPrintArgs(){
    //TODO
}
vector<llvm::Value *> Node::getArgsAddr(){
    //TODO
}

/**
 * @brief get function's parameters in definition of global function
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
        
        // FunctionVariable --> ID[] 
        if (fv->child_Num == 3) {
            llvm::Type* type = getLlvmType(ARRAY + para->child_Node[0]->getValueType(), 0) ;
            parameters.push_back(make_pair(fv->child_Node[0]->node_Name, type ));
        }
        // FunctionVariable --> ID
        else if (fv->child_Num == 1) {
            llvm::Type* type = getLlvmType(VAR + para->child_Node[0]->getValueType(), 0) ;
            parameters.push_back(make_pair(para->child_Node[1]->child_Node[0]->node_Name, type));
        }
        // FunctionVariable --> ID[][n]
        else if (fv->child_Num == 6 ) {
            //TODO
        } else 
            throw logic_error("[ERROR]Wrong var def.");
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
//     //TODO
// }