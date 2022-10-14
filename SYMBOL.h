/****************************************************************************
 ** NAME: Travis Sharp                                                     **
 ** CLASS: CSC354                                                          **
 ** ASSIGNMENT: 1                                                          **
 ** DUE DATE: 9/14/22                                                      **
 ** INSTRUCTOR: GAMRADT                                                    **
 **************************************************************************** 
 ** DESCRIPTION:  This is a symbol table that is implemented using a binary**
 **               search tree                                              **
 ****************************************************************************/
#pragma once
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

class SymbolTable
{
private:
    struct TNode
    {
        TNode *left;
        TNode *right;
        std::string symbol;
        bool RFlag, IFlag, MFlag;
        int value;
    };

    TNode *root;

    void insert(TNode *&, TNode *&);
    void destroy(TNode *);
    void deleteNode(string, TNode *&);
    void makeDelete(TNode *&);
    void displayInOrder(TNode *) const;
    

public:
/****************************************************************************
 ** FUNCTION: SymbolTable()                                                **
 ****************************************************************************
 ** DESCRIPTION: Constructor for the Symbol Table Creates an               **
 ** instance of the BSTtree with empty root node and default values.       **
 ** INPUT ARGS: None                                                       **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
    SymbolTable()
    {root = nullptr;}

/****************************************************************************
 ** FUNCTION: ~SymbolTable()                                               **
 ****************************************************************************
 ** DESCRIPTION: Destructor for the SymbolTable.                           **
 ** INPUT ARGS: None                                                       **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
    ~SymbolTable()
    {destroy(root);}

/****************************************************************************
 ** FUNCTION: insertNode(string, int, bool, bool, bool)                    **
 ****************************************************************************
 ** DESCRIPTION: Inserts a node with its values into the symbol table      **
 ** INPUT ARGS: String, int, bool, bool, bool                              **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
    void insertNode(string,int,bool,bool,bool);
    
/****************************************************************************
 ** FUNCTION: searchNode(string)                                           **
 ****************************************************************************
 ** DESCRIPTION: Searches the BST for a symbol with the right tag          **
 ** INPUT ARGS: string                                                     **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/ 
    bool searchNode(string);

/****************************************************************************
 ** FUNCTION: Finddup(String)                                              **
 ****************************************************************************
 ** DESCRIPTION: Checks for duplicates                                     **
 ** INPUT ARGS: String                                                     **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
    bool Finddup(string);

/****************************************************************************
 ** FUNCTION: remove(string)                                                  **
 ****************************************************************************
 ** DESCRIPTION: removes an item from the table                            **
 ** INPUT ARGS: string                                                        **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/  
    void remove(string);

/****************************************************************************
 ** FUNCTION: displayInOrder()                                             **
 ****************************************************************************
 ** DESCRIPTION: displays the table in order                               **
 ** INPUT ARGS: NONE                                                       **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/   
    void displayInOrder() const
    {displayInOrder(root);}

bool findrflag(string);

int findval(string);

};
#endif