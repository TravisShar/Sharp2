/****************************************************************************
 ** NAME: Travis Sharp                                                     **
 ** CLASS: CSC354                                                          **
 ** ASSIGNMENT: 2                                                          **
 ** DUE DATE:   10/5/2022                                                  **
 ** INSTRUCTOR: GAMRADT                                                    **
 **************************************************************************** 
 ** DESCRIPTION:  Driver Program                                           **
 ****************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include "SYMBOL.h"
#include "EXPRESSIONS.h"
#include "LITERAL.h"

using namespace std;


bool CheckSymbol(string symbol);
bool CheckRFlag(string rflag);
bool CheckVal(string value);
int main()
{ 
    bool rflag_table;  
    SymbolTable table;
    fstream inTable;
    string searchfile;
    string symboltable = "SYMBOLS.DAT";
    inTable.open(symboltable, std::ios::in);
    if(!inTable)
    {
        std::cout << "Error opening SYMBOLS.DAT\n";
        exit(103);
    }
      std::string line , line2;
      string sym, rflag, value, sym2;

    do{
        std::getline(inTable,line);
     
        istringstream symbol_dat(line);
        
      
        symbol_dat >> sym >> rflag >> value;
        sym.resize(sym.length()-1);
  
        if(CheckSymbol(sym) == false)
        {
            if(CheckRFlag(rflag) == false)
            {
                if (CheckVal(value) == false)
                {
                        if (rflag == "1" || rflag == "true")
                        {
                            rflag_table = true;
                        }else if (rflag == "0" || rflag == "false")
                        {
                            rflag_table = false;
                        }
                    stringstream sint;
                    int val_table;
                    sint << value;
                    sint >> val_table;
                    if(sym.length() > 6)
                        sym.resize(6); 
                    if (!table.Finddup(sym))
                        table.insertNode(sym, val_table, rflag_table, true ,false);  
                }   
            } 
        }

    }while(!inTable.eof());
    inTable.close();
    std::cout << setw(10) << left << "Symbol" << setw(10) << "Value" << setw(10) << "RFlag" << setw(8) << "IFlag" << setw(10) << "MFlage" << endl;
    table.displayInOrder();
    ExpressionList e;
    LiteralList l;
    string expressionfile;
    string expression, exp;
    fstream inExpression;
    std::cout << "Enter a expressionfile to be search" << endl;
    cin >> expressionfile;
    inExpression.open(expressionfile, std::ios::in);
    if(!inExpression)
    {
        std::cout << "Error opening file\n";
        exit(103);
    }
     do{
        std::getline(inExpression,expression);
        istringstream expression_file(expression);
        expression_file >> exp;
        string index, indirect, immediate, literal, other, rVal;
        bool rval, rval2, x, i, n;
        int val;
        if(exp.find(",X") == exp.length()-2 || exp.find(",x") == exp.length()-2)
        {
            if(exp.length() != 1)
            {
                index = exp;
                index.erase(remove(index.begin(), index.end(), ','), index.end());
                index.erase(remove(index.begin(), index.end(), 'X'), index.end());
                if(table.searchNode(index) == false)
                {
                    std::cout << "Symbol not found: " << index << endl;
                }
                else
                {
                    val = table.findval(index);
                    rval = table.findrflag(index);
                        if(rval == 1)
                        {
                            rVal = "RELATIVE";

                        }
                        else if(rval == 0)
                        {
                            rVal = "ABSOLUTE";
                        }
                        n = 1;
                        i = 1;
                        x = 1;
                        
                    e.appendNode(exp, val, rVal,n, i, x);
                    
            }    }
               
        }
        else if(exp[0] == '@')
        {  
            string inadd, insub;
            int splitpoint;
            indirect = exp;
            std::cout << indirect << endl;
            indirect.erase(remove(indirect.begin(), indirect.end(), '@'), indirect.end());
            std::cout << indirect << endl;
            
                if(exp.find('+')!= string::npos)
                {
                    splitpoint = exp.find('+');
                    inadd = indirect;
                    string tempin, tempin2;
                    int tempin3, val2;
                    inadd.erase(remove(inadd.begin(), inadd.end(), '+'), inadd.end());
                    std::cout << inadd << setw(5) << "ADDITION" << endl;
                    for(int i=0; i < splitpoint-1; i++)
                    {
                        tempin = tempin + inadd[i];
                    }
                    for(int j = splitpoint-1; j < inadd.length(); j++)
                    {
                        tempin2 = tempin2 + inadd[j];
                    }
                    
                    std::cout << tempin << endl;
                    std::cout << tempin2 << endl;

                    if(table.searchNode(tempin) == false)
                    {
                         std::cout << "Symbol not found and convert to integer " << endl;
                         val2 = std::stoi(tempin);
                         rval2 = 0;
                    }
                    else if(table.searchNode(tempin2) == false)
                    {
                        std::cout << "Symbol not found and convert to integer " << endl;
                        val2 = std::stoi(tempin2);
                        rval2 = 0;
                    }
                        if(table.searchNode(tempin) == true)
                        {
                                val = table.findval(tempin);
                                rval = table.findrflag(tempin);
                                std::cout << val << rval << endl;

                        }
                        else if (table.searchNode(tempin2) == true)
                        {
                                val = table.findval(tempin2);
                                rval = table.findrflag(tempin2);
                                std::cout << val << rval << endl;

                        }
                    
                        std::cout << val2 << val << endl;
                        tempin3 = val + val2;

                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 1;
                        i = 0;
                        x = 0;

                        e.appendNode(exp, tempin3, rVal, n, i, x);
                
                      
                }
                else if(exp.find('-')!= string::npos)
                {
                    insub = indirect;
                    string tempin, tempin2;
                    int tempin3, val2;
                    insub.erase(remove(insub.begin(), insub.end(), '-'), insub.end());
                    std::cout << insub << "-" << endl;
                    for(int i=0; i < splitpoint-1; i++)
                    {
                        tempin = tempin + insub[i];
                    }
                    for(int j = splitpoint-1; j < insub.length(); j++)
                    {
                        tempin2 = tempin2 + insub[j];
                    }
                    
                    std::cout << tempin << endl;
                    std::cout << tempin2 << endl;

                    if(table.searchNode(tempin) == false)
                    {
                         std::cout << "Symbol not found and convert to integer " << endl;
                         val2 = std::stoi(tempin);
                         rval2 = 0;
                    }
                    else if(table.searchNode(tempin2) == false)
                    {
                        std::cout << "Symbol not found and convert to integer " << endl;
                        val2 = std::stoi(tempin2);
                        rval2 = 0;
                    }
                        if(table.searchNode(tempin) == true)
                        {
                                val = table.findval(tempin);
                                rval = table.findrflag(tempin);
                                //cout << val << rval << endl;

                        }
                        else if (table.searchNode(tempin2) == true)
                        {
                                val = table.findval(tempin2);
                                rval = table.findrflag(tempin2);
                                //cout << val << rval << endl;

                        }
                        std::cout << val << endl;
                        std::cout << val2 << endl;
                        tempin3 = val2 - val;
                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                          n = 1;
                        i = 0;
                        x = 0;
                        e.appendNode(exp, tempin3, rVal,n,i,x);
                        
                    
                }
                else
                {
                    std::cout << indirect  << "ELSE" << endl;
                    if(table.searchNode(indirect) == false)
                    {
                         std::cout << "Symbol not found " << endl;
                    }
                    val = table.findval(indirect);
                    rval = table.findrflag(indirect);
                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 1;
                        i = 0;
                        x = 0;
                        e.appendNode(exp, val, rVal,n,i,x);
                       
                     
                }
        }
        else if(exp[0] == '#' || isdigit(exp[0]) == true )
        {  
            string inadd, insub,innumber;
            int splitpoint;
            immediate = exp;
            std::cout << immediate << endl;
            immediate.erase(remove(immediate.begin(), immediate.end(), '#'), immediate.end());
            std::cout << immediate << endl;
            
                if(exp.find('+')!= string::npos)
                {
                    splitpoint = exp.find('+');
                    inadd = immediate;
                    string tempin, tempin2;
                    int tempin3, val2;
                    inadd.erase(remove(inadd.begin(), inadd.end(), '+'), inadd.end());
                    std::cout << inadd << setw(5) << "ADDITION" << endl;
                    for(int i=0; i < splitpoint-1; i++)
                    {
                        tempin = tempin + inadd[i];
                    }
                    for(int j = splitpoint-1; j < inadd.length(); j++)
                    {
                        tempin2 = tempin2 + inadd[j];
                    }
                    
                    std::cout << tempin << endl;
                    std::cout << tempin2 << endl;

                    if(table.searchNode(tempin) == false)
                    {
                         std::cout << "Symbol not found and convert to integer " << endl;
                         val2 = std::stoi(tempin);
                         rval2 = 0;
                    }
                    else if(table.searchNode(tempin2) == false)
                    {
                        std::cout << "Symbol not found and convert to integer " << endl;
                        val2 = std::stoi(tempin2);
                        rval2 = 0;
                    }
                        if(table.searchNode(tempin) == true)
                        {
                                val = table.findval(tempin);
                                rval = table.findrflag(tempin);
                                std::cout << val << rval << endl;

                        }
                        else if (table.searchNode(tempin2) == true)
                        {
                                val = table.findval(tempin2);
                                rval = table.findrflag(tempin2);
                                std::cout << val << rval << endl;

                        }
                    
                        std::cout << val2 << val << endl;
                        tempin3 = val + val2;

                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 0;
                        i = 1;
                        x = 0;

                        e.appendNode(exp, tempin3, rVal, n, i, x);
                
                      
                }
                else if(exp.find('-')!= string::npos)
                {
                    insub = immediate;
                    string tempin, tempin2;
                    int tempin3, val2;
                    insub.erase(remove(insub.begin(), insub.end(), '-'), insub.end());
                    std::cout << insub << "-" << endl;
                    for(int i=0; i < splitpoint-1; i++)
                    {
                        tempin = tempin + insub[i];
                    }
                    for(int j = splitpoint-1; j < insub.length(); j++)
                    {
                        tempin2 = tempin2 + insub[j];
                    }
                    
                    std::cout << tempin << endl;
                    std::cout << tempin2 << endl;

                    if(table.searchNode(tempin) == false)
                    {
                         std::cout << "Symbol not found and convert to integer " << endl;
                         val2 = std::stoi(tempin);
                         rval2 = 0;
                    }
                    else if(table.searchNode(tempin2) == false)
                    {
                        std::cout << "Symbol not found and convert to integer " << endl;
                        val2 = std::stoi(tempin2);
                        rval2 = 0;
                    }
                        if(table.searchNode(tempin) == true)
                        {
                                val = table.findval(tempin);
                                rval = table.findrflag(tempin);
                                //cout << val << rval << endl;

                        }
                        else if (table.searchNode(tempin2) == true)
                        {
                                val = table.findval(tempin2);
                                rval = table.findrflag(tempin2);
                                //cout << val << rval << endl;

                        }
                        std::cout << val << endl;
                        std::cout << val2 << endl;
                        tempin3 = val2 - val;
                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 0;
                        i = 1;
                        x = 0;
                        e.appendNode(exp, tempin3, rVal,n,i,x);
                        
                    
                }
                else if(isdigit(immediate[0]) == true)
                {
                    innumber = immediate;
                    std::cout << innumber << "Number" << endl;
                    val = std::stoi(innumber);
                    rVal = "ABSOLUTE"; 
                    n = 0;
                    i = 1;
                    x = 0;
                    e.appendNode(exp, val, rVal,n,i,x);

                }
                else
                {
                    std::cout << immediate << "ELSE" << endl;
                    if(table.searchNode(immediate) == false)
                    {
                         std::cout << "Symbol not found " << endl;
                    }
                    else
                    {
                    val = table.findval(immediate);
                    rval = table.findrflag(immediate);
                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 1;
                        i = 0;
                        x = 0;
                        e.appendNode(exp, val, rVal,n,i,x);
                       
                    } 
                }
        }
        else if(exp[0] == '=')
        {
            literal = exp; 
            string value;
            int bytes, address;
            if (literal[1] == 'c' || literal[1] == 'C')
            {
                
              

            }
            else if (literal[1] == 'x' || literal[1] == 'X')
            {

            }
            else
                cout << "Literal not defined correctly: " << literal << endl;
        
        
        }
        else
        {
            string inadd, insub;
            int splitpoint;
            other = exp;
            std::cout << other << endl;            
                if(exp.find('+')!= string::npos)
                {
                    splitpoint = exp.find('+');
                    inadd = other;
                    string tempin, tempin2;
                    int tempin3, val2;
                    inadd.erase(remove(inadd.begin(), inadd.end(), '+'), inadd.end());
                    std::cout << inadd << setw(5) << "ADDITION" << endl;
                    for(int i=0; i < splitpoint; i++)
                    {
                        tempin = tempin + inadd[i];
                    }
                    for(int j = splitpoint; j < inadd.length(); j++)
                    {
                        tempin2 = tempin2 + inadd[j];
                    }
                    
                    std::cout << tempin << endl;
                    std::cout << tempin2 << endl;

                    if(table.searchNode(tempin) == false)
                    {
                         std::cout << "Symbol not found and convert to integer " << endl;
                         val2 = std::stoi(tempin);
                         rval2 = 0;
                    }
                    else if(table.searchNode(tempin2) == false)
                    {
                        std::cout << "Symbol not found and convert to integer " << endl;
                        val2 = std::stoi(tempin2);
                        rval2 = 0;
                    }
                        if(table.searchNode(tempin) == true)
                        {
                                val = table.findval(tempin);
                                rval = table.findrflag(tempin);
                                std::cout << val << rval << endl;

                        }
                        else if (table.searchNode(tempin2) == true)
                        {
                                val = table.findval(tempin2);
                                rval = table.findrflag(tempin2);
                                std::cout << val << rval << endl;

                        }
                    
                        std::cout << val2 << val << endl;
                        tempin3 = val + val2;

                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 0;
                        i = 1;
                        x = 0;

                        e.appendNode(exp, tempin3, rVal, n, i, x);
                
                      
                }
                else if(exp.find('-')!= string::npos)
                {
                    insub = other;
                    string tempin, tempin2;
                    int tempin3, val2;
                    insub.erase(remove(insub.begin(), insub.end(), '-'), insub.end());
                    std::cout << insub << "-" << endl;
                    for(int i=0; i < splitpoint; i++)
                    {
                        tempin = tempin + insub[i];
                    }
                    for(int j = splitpoint; j < insub.length(); j++)
                    {
                        tempin2 = tempin2 + insub[j];
                    }
                    
                    std::cout << tempin << endl;
                    std::cout << tempin2 << endl;

                    if(table.searchNode(tempin) == false)
                    {
                         std::cout << "Symbol not found and convert to integer " << endl;
                         val2 = std::stoi(tempin);
                         rval2 = 0;
                    }
                    else if(table.searchNode(tempin2) == false)
                    {
                        std::cout << "Symbol not found and convert to integer " << endl;
                        val2 = std::stoi(tempin2);
                        rval2 = 0;
                    }
                        if(table.searchNode(tempin) == true)
                        {
                                val = table.findval(tempin);
                                rval = table.findrflag(tempin);
                                //cout << val << rval << endl;

                        }
                        else if (table.searchNode(tempin2) == true)
                        {
                                val = table.findval(tempin2);
                                rval = table.findrflag(tempin2);
                                //cout << val << rval << endl;

                        }
                        std::cout << val << endl;
                        std::cout << val2 << endl;
                        tempin3 = val - val2;
                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 0;
                        i = 1;
                        x = 0;
                        e.appendNode(exp, tempin3, rVal,n,i,x);
                        
                    
                }
                else
                {
                    std::cout << other << "ELSE" << endl;
                    if(table.searchNode(other) == false)
                    {
                         std::cout << "Symbol not found " << endl;
                    }
                    else
                    {
                    val = table.findval(other);
                    rval = table.findrflag(other);
                        if(rval == 1)
                        {
                            rVal = "RELATIVE";
                        }
                        else
                        {
                            rVal = "ABSOLUTE";
                            
                        }
                        n = 1;
                        i = 0;
                        x = 0;
                        e.appendNode(exp, val, rVal,n,i,x);
                       
                    } 
                } 
        }
    }while(!inExpression.eof());
    std::cout << setw(15) << left << "Expression" << setw(10) << "Value" << setw(12) << "Relocatable" << setw(10) << "N-Bit" << setw(10) << "I-Bit" << setw(10) << "X-Bit"<< endl;
    e.displayList();

    return 0;
}


/****************************************************************************
 ** FUNCTION: CheckSymbol(String)                                          **
 ****************************************************************************
 ** DESCRIPTION: Checks Symbol from File                                   **
 ** INPUT ARGS: String                                                     **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
bool CheckSymbol(string symbol)
{
    bool fault = false;
    if(symbol.size() > 12)
    {
        fault = true;
        std::cout << "Error in the size of you symbol : " << symbol << endl;    
    }
    else if(isalpha(symbol[0]) == false)
    {
        fault = true;
        std::cout << "Error your symbol doesn't start with a letter : " << symbol << endl;
    }else
    {
        for(int i = 1; i < symbol.length(); i++)
            if(!isalpha(symbol[i]) && fault == false)
                if(!isdigit(symbol[i]))
                {
                fault = true;
                std::cout << "It doesn't follow by letters (A..Z, a..z) and digits (0..9): " << symbol << endl; 
                }
    }
    return fault;

}


/****************************************************************************
 ** FUNCTION: CheckRFlag(String)                                           **
 ****************************************************************************
 ** DESCRIPTION: Checks RFlag from File                                    **
 ** INPUT ARGS: String                                                     **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
bool CheckRFlag(string rflag)
{
    bool fault = false;
    if(rflag == "1" || rflag == "0" || rflag == "true" || rflag == "false")
    {
        return fault;
       // cout << "Invalid rflag : " << rflag << endl;
    }
        std::cout << "Invalid rflag : " << rflag << endl;
        

        fault = true;
        return fault;

}


/****************************************************************************
 ** FUNCTION: CheckVal(String)                                             **
 ****************************************************************************
 ** DESCRIPTION: checks Value from file                                    **
 ** INPUT ARGS: String                                                     **
 ** OUTPUT ARGS: None                                                      **
 ** IN/OUT ARGS: None                                                      ** 
 ****************************************************************************/
bool CheckVal(string value)
{
    bool fault = false;
    size_t found = value.find(".");
    if(found != std::string::npos)
    {
        fault = true;
        std::cout << "Invalid value :" << value << endl;
        

    }else
    {
        for(int i = 1; i < value.length(); i++)
            if(isalpha(value[i]) && fault == false)
            {
              fault = true;
              std::cout << "Invalid value :" << value << endl;
              
  
            }
    }
        return fault;
}
