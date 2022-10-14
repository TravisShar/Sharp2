/****************************************************************************
 ** NAME: Travis Sharp                                                     **
 ** CLASS: CSC354                                                          **
 ** ASSIGNMENT: 2                                                          **
 ** DUE DATE:   10/5/2022                                                  **
 ** INSTRUCTOR: GAMRADT                                                    **
 **************************************************************************** 
 ** DESCRIPTION:  Definition File for Expresions                           **
 ****************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include "EXPRESSIONS.h"

using namespace std;


void ExpressionList::appendNode(string exp, int val, string r, bool nbit, bool ibit, bool xbit)
{
    //cout << "working append" << endl;
    ExpressionVal *newNode;
    ExpressionVal *nodePtr;
    newNode = new ExpressionVal;
    newNode->expression = exp;
    newNode->value = val;
    newNode->relocatable = r;
    newNode->Nbit = nbit;
    newNode->Ibit = ibit;
    newNode->Xbit = xbit;
    newNode->next = nullptr;
   
    if(!head)
        head = newNode;
    else
    {
        nodePtr = head;
        while(nodePtr->next)
            nodePtr = nodePtr->next;
        nodePtr->next = newNode;   
    }
}


ExpressionList::~ExpressionList()
{
    ExpressionVal *nodePtr;
    ExpressionVal *nextNode;

    nodePtr = head;

    while(nodePtr != nullptr)
    {
        nextNode = nodePtr->next;

        delete nodePtr;

        nodePtr = nextNode;
    }
}


void ExpressionList::displayList() const
{
    ExpressionVal *nodePtr;
    nodePtr = head;
    while(nodePtr)
    {
        cout << setw(15) << nodePtr->expression << setw(10) << nodePtr->value << setw(12) << nodePtr->relocatable << setw(10) << nodePtr->Nbit << setw(10) << nodePtr->Ibit << setw(10) << nodePtr->Xbit << endl;

        nodePtr = nodePtr->next;
    }
}

