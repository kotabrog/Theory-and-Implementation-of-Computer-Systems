#include "../inc/Parser.hpp"

std::map<std::string, CommandType> Parser::_commandMap;

void Parser::makeCommandMap()
 {
    _commandMap["add"] = CommandType::C_ARITHMETIC;
    _commandMap["sub"] = CommandType::C_ARITHMETIC;
    _commandMap["neg"] = CommandType::C_ARITHMETIC;
    _commandMap["eq"] = CommandType::C_ARITHMETIC;
    _commandMap["gt"] = CommandType::C_ARITHMETIC;
    _commandMap["lt"] = CommandType::C_ARITHMETIC;
    _commandMap["and"] = CommandType::C_ARITHMETIC;
    _commandMap["or"] = CommandType::C_ARITHMETIC;
    _commandMap["not"] = CommandType::C_ARITHMETIC;
    _commandMap["push"] = CommandType::C_PUSH;
    _commandMap["pop"] = CommandType::C_POP;
    _commandMap["label"] = CommandType::C_LABEL;
    _commandMap["goto"] = CommandType::C_GOTO;
    _commandMap["if-goto"] = CommandType::C_IF;
    _commandMap["function"] = CommandType::C_FUNCTION;
    _commandMap["return"] = CommandType::C_RETURN;
    _commandMap["call"] = CommandType::C_CALL;
}


Parser::Parser(std::string filePath)
    : _ifs(filePath)
{
    if (!_ifs) {
        std::cerr << "Could not open file" << std::endl;
        std::exit(1);
    }
}


bool Parser::hasMoreCommands()
{
    return !_ifs.eof();
}

std::string Parser::_eraseComment(std::string s)
{
    std::size_t pos = s.find("//");
    if (pos != std::string::npos) {
        s.erase(s.begin() + pos, s.end());
    }
    return s;
}

std::string Parser::_ltrim(std::string s)
{
    const std::string space = " \n\r\t\f\v";
    std::size_t start = s.find_first_not_of(space);
    return (start == std::string::npos) ? "" : s.substr(start);
}


std::string Parser::_rtrim(std::string s)
{
    const std::string space = " \n\r\t\f\v";
    size_t end = s.find_last_not_of(space);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}


std::string Parser::_trim(std::string s)
{
    return _rtrim(_ltrim(s));
}


CommandType Parser::_discriminateCommandType(std::string& command)
{
    if (!_commandMap.count(command)) {
        std::cerr << "The command entered does not exist." << std::endl;
        std::exit(1);
    }
    return _commandMap[command];
}


std::string Parser::_parseCommandType(std::string s)
{
    // WIP nonwhite space delimiter (\r\t\f\v)
    std::size_t pos = s.find(' ');
    std::string command = s.substr(0, pos);
    _commandType = _discriminateCommandType(command);
    if (_commandType == CommandType::C_ARITHMETIC) {
        _arg1 = command;
    }
    s.erase(s.begin(), s.begin() + command.length());
    return _ltrim(s);
}


std::string Parser::_parseArg1(std::string s)
{
    // WIP nonwhite space delimiter (\r\t\f\v)
    std::size_t pos = s.find(' ');
    _arg1 = s.substr(0, pos);
    if (_arg1.empty()) {
        std::cerr << "arg1 does not exist" << std::endl;
        std::exit(1);
    }
    s.erase(s.begin(), s.begin() + _arg1.length());
    return _ltrim(s);
}


void Parser::_parseArg2(std::string s)
{
    try {
        _arg2 = std::stoi(s);
    } catch(const std::exception& e) {
        std::cerr << "arg2 is not a number" << std::endl;
        std::exit(1);
    }
}


bool Parser::advance()
{
    std::string s;
    while (!_ifs.eof() && s.empty()) {
        // WIP error check
        std::getline(_ifs, s);
        s = _eraseComment(s);
        s = _trim(s);
    }
    if (!s.empty()) {
        s = _parseCommandType(s);
        if (_commandType != CommandType::C_ARITHMETIC &&
                _commandType != CommandType::C_RETURN) {
            s = _parseArg1(s);
        }
        if (_commandType == CommandType::C_PUSH ||
                _commandType == CommandType::C_POP ||
                _commandType == CommandType::C_FUNCTION ||
                _commandType == CommandType::C_CALL) {
            _parseArg2(s);
        }
    }
    return !s.empty();
}
