#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <iostream>
#include <string>
#include <map>

class SymbolTable
{
private:
    std::map<std::string, int> _table;

public:
    SymbolTable();
    void addEntity(std::string symbol, int address);
    bool contains(std::string symbol);
    int getAddress(std::string symbol);
};

#endif