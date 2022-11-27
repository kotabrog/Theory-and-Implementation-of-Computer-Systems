#include "../inc/SymbolTable.hpp"


SymbolTable::SymbolTable()
{
    _table["SP"] = 0;
    _table["LCL"] = 1;
    _table["ARG"] = 2;
    _table["THIS"] = 3;
    _table["THAT"] = 4;
    for (int i = 0; i < 16; ++i) {
        _table["R" + std::to_string(i)] = i;
    }
    _table["SCREEN"] = 16384;
    _table["KBD"] = 24576;
}


void SymbolTable::addEntity(std::string symbol, int address)
{
    _table[symbol] = address;
}


bool SymbolTable::contains(std::string symbol)
{
    return _table.count(symbol);
}


int SymbolTable::getAddress(std::string symbol)
{
    return _table.at(symbol);
}
