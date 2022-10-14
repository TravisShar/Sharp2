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
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include "SYMBOL.h"

using namespace std;


/****************************************************************************
 ** FUNCTION: insertNode(string, int, bool, bool, bool)                    **
 ****************************************************************************
 ** DESCRIPTION: Inserts a node with its values into the symbol table      **
 ** INPUT ARGS: String, int, bool, bool, bool                              **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
void SymbolTable::insertNode(string sym, int val, bool rflag, bool iflag, bool mflag)
{
    //cout << "Insert node" << endl;
    TNode *newNode = nullptr;
    newNode = new TNode;
    newNode->symbol = sym;
    newNode->value = val;
    newNode->RFlag = rflag;
    newNode->IFlag = iflag = 1;
    newNode->MFlag = mflag = 0;

    newNode->left = newNode->right = nullptr;

    insert(root, newNode);
}
/****************************************************************************
 ** FUNCTION: insert(TNode *&, TNode *&)                                      **
 ****************************************************************************
 ** DESCRIPTION: adds a symbol to an empty spot in the table               **
 ** INPUT ARGS:  TNode *&, TNode *&                                        **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/ 
void SymbolTable::insert(TNode *&nodePtr, TNode *&newNode)
{
    if(nodePtr == NULL)
        nodePtr = newNode;
    else if(newNode->symbol < nodePtr->symbol)
        insert(nodePtr->left, newNode);
    else
        insert(nodePtr->right, newNode);
}

/****************************************************************************
 ** FUNCTION: destroy(TNode *)                                              **
 ****************************************************************************
 ** DESCRIPTION: removes an item from the tree                             **
 ** INPUT ARGS: TNode *                                                    **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
void SymbolTable::destroy(TNode *nodePTr)
{
    if(nodePTr)
    {
        if(nodePTr->left)
            destroy(nodePTr->left);
        if(nodePTr->right)
            destroy(nodePTr->right);
        delete nodePTr;
    }
}

/****************************************************************************
 ** FUNCTION: displayInOrder(TNode *&)                                     **
 ****************************************************************************
 ** DESCRIPTION: displays the table in order                               **
 ** INPUT ARGS: TNode *&                                                   **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/ 
void SymbolTable::displayInOrder(TNode *nodePtr) const
{
    
    if(nodePtr)
    {
        displayInOrder(nodePtr->left);
        cout << setw(10) << left << nodePtr->symbol << setw(10) << nodePtr-> value  << setw(10) << nodePtr->RFlag << setw(8) << nodePtr->IFlag << setw(10) << nodePtr->MFlag << endl;
        displayInOrder(nodePtr->right);
    }
}


/****************************************************************************
 ** FUNCTION: searchNode(string)                                           **
 ****************************************************************************
 ** DESCRIPTION: Searches the BST for a symbol with the right tag          **
 ** INPUT ARGS: string                                                     **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/ 
bool SymbolTable::searchNode(string se_symbols)
{
    TNode *nodePtr = root;

    while(nodePtr)
    {
        if(nodePtr->symbol == se_symbols)
        {
            //cout << "Found : " << setw(10) << left << nodePtr->symbol << setw(10) << nodePtr-> value  << setw(10) << nodePtr->RFlag << setw(8) << nodePtr->IFlag << setw(10) << nodePtr->MFlag << endl;
            return true;
        }
        else if(se_symbols < nodePtr->symbol)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    
    return false;
}

int SymbolTable::findval(string se_symbols)
{
    cout << "Finding Value" << endl;
    TNode *nodePtr = root;
    //cout << root->symbol << endl;
    cout << se_symbols << endl;
    
    int temp;
    while(nodePtr)
    {
        //cout << nodePtr->symbol << endl;
        if(nodePtr->symbol == se_symbols)
        {
            //cout << "Found : " << setw(10) << left << nodePtr->symbol << setw(10) << nodePtr-> value  << setw(10) << nodePtr->RFlag << setw(8) << nodePtr->IFlag << setw(10) << nodePtr->MFlag << endl;
            temp = nodePtr->value;
            return temp;

        }
        else if(se_symbols < nodePtr->symbol)
            nodePtr = nodePtr->left;
        else if(se_symbols > nodePtr->symbol)
            nodePtr = nodePtr->right;
        else
        cout << "NOT working" << endl;
    }
    
    return 0;
}

bool SymbolTable::findrflag(string se_symbols)
{
    cout << "Finding Rflag" << endl;

    TNode *nodePtr = root;
    int temp;

    while(nodePtr)
    {
        if(nodePtr->symbol == se_symbols)
        {
            //cout << "Found : " << setw(10) << left << nodePtr->symbol << setw(10) << nodePtr-> value  << setw(10) << nodePtr->RFlag << setw(8) << nodePtr->IFlag << setw(10) << nodePtr->MFlag << endl;
            temp = nodePtr->RFlag;
            return temp;

        }
        else if(se_symbols < nodePtr->symbol)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    
    return 0;
}




/****************************************************************************
 ** FUNCTION: Finddup(String)                                              **
 ****************************************************************************
 ** DESCRIPTION: Checks for duplicates                                     **
 ** INPUT ARGS: String                                                     **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
bool SymbolTable::Finddup(string se_symbols)
{
    TNode *nodePtr = root;
    bool dup = false;
    while(nodePtr)
    {
        if(nodePtr->symbol == se_symbols)
        { 
            nodePtr->MFlag = 1;
            dup = true;
            cout << "This one already exisis: " << se_symbols << endl;
            return dup;
        }
        else if(se_symbols < nodePtr->symbol)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    return dup;
}

/****************************************************************************
 ** FUNCTION: remove(TNode *)                                              **
 ****************************************************************************
 ** DESCRIPTION: removes an item from the tree                             **
 ** INPUT ARGS: TNode *                                                    **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
void SymbolTable::remove(string symbol)
{
    deleteNode(symbol, root);
}


/****************************************************************************
 ** FUNCTION: deleteNode(int, TNode *&)                                    **
 ****************************************************************************
 ** DESCRIPTION: removes an node from the tree                             **
 ** INPUT ARGS: int, TNode *&                                              **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
void SymbolTable::deleteNode(string symbol, TNode *&nodePtr)
{
    if(symbol < nodePtr->symbol)
        deleteNode(symbol, nodePtr->left);
    else if( symbol > nodePtr->symbol)
        deleteNode(symbol, nodePtr->right);
    else
        makeDelete(nodePtr);
}


/****************************************************************************
 ** FUNCTION: makeDelete(TNode *&)                                         **
 ****************************************************************************
 ** DESCRIPTION: removes an item from the table near the top                **
 ** INPUT ARGS: TNode *&                                                   **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/  
void SymbolTable::makeDelete(TNode *&nodePtr)
{
    TNode *tempNodePtr;

    if(nodePtr == NULL)
        cout << "Cannot delete empty node.\n";
    else if(nodePtr->right == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempNodePtr;
    }
    else if(nodePtr->left == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
    else
    {
        tempNodePtr = nodePtr->right;
        while(tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
}