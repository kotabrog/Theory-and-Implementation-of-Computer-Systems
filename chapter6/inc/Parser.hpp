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

    std::string _eraseEmpty(std::string s);

public:
    Parser(std::string fileName);
    bool hasMoreCommands();
    bool advance();
    CommandType commandType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();
};

#endif
