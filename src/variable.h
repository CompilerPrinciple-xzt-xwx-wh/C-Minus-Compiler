/**
 * @file variable.h
 * @brief Class Variable is used to construct variable while definition, 
 *        which is essential since we need to construct two-dimension arrays.
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-15
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _VARIABLE_H
#define _VARIABLE_H

#include"ast.h"

#ifndef _STD_H_
#define _STD_H_
using namespace std ;
#endif

class Variable {
private:
    /* data */
    string Name ;
    /**
     * @brief Type 
     * refer to predefined int values in _TYPE_H_
     * modification log: 2022/5/15,17:39
     * modificated by: Wang Hui
     */
    int Type ;
    /**
     * @brief Total size of variable or array
     * size is 0 if variable or a positive number equals to the size of array
     * modification log: 2022/5/15,17:55
     * modificated by: Wang Hui
     */
    int Size ;
    /**
     * @brief BottomSize
     * Used in two-dimension arrays, for operator [][] to compute the location
     * modification log: 2022/5/15,17:40
     * modificated by: Wang Hui
     */
    int BottomSize ;
public:
    Variable(/* args */string n , int t, int s = 0 ) ;
    Variable(string n, int t, int s, int bs ) ;
    // ~variable();
    string getName() ;
    int getType() ;
    int getSize() ;
    int getBottomSize() ;
};

#endif