#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <iostream>
#include <string>
#include <map>

#include "Type.hpp"

class SymbolTable
{
private:
    struct Var
    {
        Var() {}
        Var(int index, std::string type, Kind kind)
            : index(index), type(type), kind(kind) {}
        int index;
        std::string type;
        Kind kind;
    };

    std::map<std::string, Var> _classTable;
    std::map<std::string, Var> _subroutineTable;
    int _staticCount;
    int _fieldCount;
    int _argCount;
    int _varCount;
    std::string _subroutineName;

public:
    SymbolTable() : _staticCount(0), _fieldCount(0), _argCount(0), _varCount(0) {}
    void startSubroutine();
    void define(std::string name, std::string type, Kind kind);
    int varCount(Kind kind);
    Kind kindOf(std::string name);
    std::string typeOf(std::string name);
    int indexOf(std::string name);
    void setSubroutineName(std::string className, std::string name);
    std::string getSubroutineName() {return _subroutineName;}
};

#endif
