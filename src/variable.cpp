#include"variable.h"

Variable::Variable(/* args */string n, int t, int s ) {
    this->Name = n ;
    this->Size = s ;
    this->Type = t ;
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