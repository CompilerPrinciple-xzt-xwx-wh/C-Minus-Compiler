/**
 * @file type.h
 * @brief 
 *      define frequently-used date types for C
 *      type informations used for AST's construction
 *      ...
 * @author Wang Hui (3190105609@zju.edu.cn)
 * @version 1.0
 * @date 2022-05-09
 * @copyright Copyright (c) 2022. Xu Zhengtao,Wang Hui and Xie Wenxiang. 
 * 
 */

#ifndef _TYPE_H_
#define _TYPE_H_

#define TYPE_VOID (-1)
#define VAR 0
#define ARRAY 1

#define FUN 2

/**
 * @brief add two-dimension array
 * 
 * modification log: 2022/5/15,15:13
 * modificated by: Wang Hui
 */
#define TYPE_INT 10
#define TYPE_INT_ARRAY 11
#define TYPE_INT_ARRAY_ARRAY 12
#define TYPE_FLOAT 20
#define TYPE_FLOAT_ARRAY 21
#define TYPE_FLOAT_ARRAY_ARRAY 22
#define TYPE_CHAR 30
#define TYPE_CHAR_ARRAY 31
#define TYPE_CHAR_ARRAY_ARRAY 32

// modified type
#define TYPE_DOUBLE 40
#define TYPE_DOUBLE_ARRAY 41
#define TYPE_DOUBLE_ARRAY_ARRAY 42

// TODO
#define POINTER 3

// no use of bool
// #define TYPE_BOOL 10
// #define TYPE_BOOL_ARRAY 11

/**
 * @brief return 0 if type is not an array, return 1 if type is one-dimension array and return 2 if type is two-dimension.
 * @param type 
 * @return int 
 * modification log: 2022/5/15,17:44
 * modificated by: Wang Hui
 */
inline int isArray(int type) {
    return type%10 ;
}

#define GLOBAL "global"

#endif