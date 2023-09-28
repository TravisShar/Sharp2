/****************************************************************************
 ** NAME: Travis Sharp                                                     **
 ** CLASS: CSC354                                                          **
 ** ASSIGNMENT: 2                                                          **
 ** DUE DATE:   10/5/2022                                                  **
 ** INSTRUCTOR: GAMRADT                                                    **
 **************************************************************************** 
 ** DESCRIPTION:  Header File for Expressions                              **
 ****************************************************************************/

#pragma once
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include <iomanip>
#include <string>
#include <iostream>
#include "SYMBOL.h"
using namespace std;

class ExpressionList
{
    private:
    struct ExpressionVal
    {
        string expression;
        int value;
        string relocatable;
        bool Nbit;
        bool Ibit;
        bool Xbit;
        struct ExpressionVal *next;
    };
    
    ExpressionVal *head;

    public:
    ExpressionList()
    { head = nullptr; }
    ~ExpressionList();
    void appendNode(string, int, string, bool, bool, bool);
    void displayList() const;
  
   


    
};
#endif
