#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "CommandType.hpp"

class Parser
{
private:
    static std::map<std::string, CommandType> _commandMap;

    std::ifstream _ifs;
    CommandType _commandType;
    std::string _arg1;
    int _arg2;

    std::string _eraseComment(std::string s);
    std::string _ltrim(std::string s);
    std::string _rtrim(std::string s);
    std::string _trim(std::string s);
    std::string _parseCommandType(std::string s);
    CommandType _discriminateCommandType(std::string& command);
    std::string _parseArg1(std::string s);

public:
    static void makeCommandMap();

    Parser(std::string filePath);
    bool hasMoreCommands();
    bool advance();
    CommandType commandType() {return _commandType;}
    std::string arg1() {return _arg1;}
    int arg2() {return _arg2;}
};

#endif
