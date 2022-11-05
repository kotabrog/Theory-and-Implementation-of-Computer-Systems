#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

#include "CommandType.hpp"

class Parser
{
private:
    std::ifstream _ifs;
    CommandType _commandType;
    std::string _symbol;
    std::string _dest;
    std::string _comp;
    std::string _jump;

    std::string _eraseSpace(std::string s);
    std::string _eraseComment(std::string s);
    CommandType _checkCommandType(std::string s);
    std::string _parseSymbol(std::string s);
    std::string _parseDest(std::string s);
    std::string _parseComp(std::string s);
    std::string _parseJump(std::string s);

public:
    Parser(std::string fileName);
    bool hasMoreCommands();
    bool advance();
    CommandType commandType() {return _commandType;}
    std::string symbol() {return _symbol;}
    std::string dest() {return _dest;}
    std::string comp() {return _comp;}
    std::string jump() {return _jump;}
};

#endif
