/**
 * @file type.h
 * @brief 
 *      define frequently-used date types for C
 *      type informations used for AST's construction
 *      ...
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-09
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _TYPE_H_
#define _TYPE_H_

#define VOID -1
#define VAR 0
#define ARRAY 1

#define FUN 2

#define TYPE_INT 4
#define TYPE_INT_ARRAY 5
#define TYPE_FLOAT 6
#define TYPE_FLOAT_ARRAY 7
#define TYPE_CHAR 8
#define TYPE_CHAR_ARRAY 9

// modified type
#define TYPE_DOUBLE 10
#define TYPE_DOUBLE_ARRAY 11
#define POINTER 12

// no use of bool
// #define TYPE_BOOL 10
// #define TYPE_BOOL_ARRAY 11


#define GLOBAL "global"

#endif