/****************************************************************************
 ** NAME: Travis Sharp                                                     **
 ** CLASS: CSC354                                                          **
 ** ASSIGNMENT: 2                                                          **
 ** DUE DATE:   10/5/2022                                                  **
 ** INSTRUCTOR: GAMRADT                                                    **
 **************************************************************************** 
 ** DESCRIPTION:  Header File for the Literal Table                        **
 ****************************************************************************/

#pragma once
#ifndef LITERAL_H
#define LITERAL_H
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

class LiteralList
{
    private:
    struct LiteralVal
    {
        string literal_name;
        string operand_value;
        int bytes;
        int address;
        struct LiteralVal *next;
    };
    
    LiteralVal *head;

    public:
    LiteralList()
    { head = nullptr; }
    ~LiteralList();
    void appendNode(string, string, int, int);
    void insertNode(string, string, int, int);
    void literal_handler(string, string, int, int);
    bool searchdupp(string);
    //void deleteNode(string, string, int, int);
    void displayList() const;

    
};
#endif