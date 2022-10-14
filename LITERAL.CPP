/****************************************************************************
 ** NAME: Travis Sharp                                                     **
 ** CLASS: CSC354                                                          **
 ** ASSIGNMENT: 2                                                          **
 ** DUE DATE:   10/5/2022                                                  **
 ** INSTRUCTOR: GAMRADT                                                    **
 **************************************************************************** 
 ** DESCRIPTION:  Definition function for Literal table                    **
 ****************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include "LITERAL.h"
using namespace std;

void LiteralList::appendNode(string literal, string operand, int byte, int address)
{
    LiteralVal *newNode;
    LiteralVal *nodePtr;

    newNode = new  LiteralVal;
    newNode->literal_name = literal;
    newNode->operand_value = operand;
    newNode->bytes = byte;
    newNode->address = address; 
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

bool LiteralList::searchdupp(string literal)
{
    LiteralVal * current = head;
    while (current != NULL)
    {
        if((current->literal_name == literal))
            return true;
        current = current->next;

    }
    return false;
}

 LiteralList::~LiteralList()
{
    LiteralVal *nodePtr;
    LiteralVal *nextNode;

    nodePtr = head;

    while(nodePtr != nullptr)
    {
        nextNode = nodePtr->next;

        delete nodePtr;

        nodePtr = nextNode;
    }
}


void LiteralList::displayList() const
{
    LiteralVal *nodePtr;
    nodePtr = head;
    while(nodePtr)
    {
        cout << nodePtr->literal_name << nodePtr->operand_value << nodePtr->bytes << nodePtr->address << endl;

        nodePtr = nodePtr->next;
    }
}