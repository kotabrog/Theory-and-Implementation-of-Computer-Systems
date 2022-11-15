#include "../inc/SymbolTable.hpp"


void SymbolTable::startSubroutine()
{
    _subroutineTable.clear();
    _argCount = 0;
    _varCount = 0;
}


void SymbolTable::define(std::string name, std::string type, Kind kind)
{
    if (((kind == Kind::STATIC || kind == Kind::FIELD) && _classTable.count(name)) ||
            ((kind == Kind::ARG || kind == Kind::VAR) && _classTable.count(name))) {
        std::cerr << "compile error: Variables are doubly defined" << std::endl;
        std::exit(1);
    }
    if (kind == Kind::STATIC) {
        _classTable[name] = Var(_staticCount, type, kind);
        _staticCount += 1;
    } else if (kind == Kind::FIELD) {
        _classTable[name] = Var(_fieldCount, type, kind);
        _fieldCount += 1;
    } else if (kind == Kind::ARG) {
        _subroutineTable[name] = Var(_argCount, type, kind);
        _argCount += 1;
    } else if (kind == Kind::VAR) {
        _subroutineTable[name] = Var(_varCount, type, kind);
        _varCount += 1;
    }
}


int SymbolTable::varCount(Kind kind)
{
    if (kind == Kind::STATIC) {
        return _staticCount;
    } else if (kind == Kind::FIELD) {
        return _fieldCount;
    } else if (kind == Kind::ARG) {
        return _argCount;
    } else if (kind == Kind::VAR) {
        return _varCount;
    }
    return 0;
}


Kind SymbolTable::kindOf(std::string name)
{
    if (_classTable.count(name))
        return _classTable[name].kind;
    if (_subroutineTable.count(name))
        return _subroutineTable[name].kind;
    return Kind::NONE;
}


std::string SymbolTable::typeOf(std::string name)
{
    if (_classTable.count(name))
        return _classTable[name].type;
    if (_subroutineTable.count(name))
        return _subroutineTable[name].type;
    std::cerr << "compile error: typeOf: The variable is not defined" << std::endl;
    std::exit(1);
}


int SymbolTable::indexOf(std::string name)
{
    if (_classTable.count(name))
        return _classTable[name].index;
    if (_subroutineTable.count(name))
        return _subroutineTable[name].index;
    std::cerr << "compile error: indexOf: The variable is not defined" << std::endl;
    std::exit(1);
}
