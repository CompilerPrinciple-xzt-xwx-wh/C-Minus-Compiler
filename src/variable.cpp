#include "variable.h"

Variable::Variable(/* args */string n, int t, int s ) {
    this->Name = n ;
    this->Type = t ;
    this->Size = s ;
    this->BottomSize = s ;
}
Variable::Variable(string n, int t, int s, int bs ) {
    this->Name = n ;
    this->Type = t ;
    this->Size = s ;
    this->BottomSize = bs ;
}

string Variable::getName(){
    return Name ;
}
int Variable::getType(){
    return Type ;
}
int Variable::getSize(){
    return Size ;
}
int Variable::getBottomSize(){
    return BottomSize ;
}