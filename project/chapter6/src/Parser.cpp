#include "../inc/Parser.hpp"


Parser::Parser(std::string fileName)
    : _ifs(fileName)
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


std::string Parser::_eraseSpace(std::string s)
{
    s.erase(std::remove_if(s.begin(), s.end(),
                [](char c) {
                    return std::isspace(static_cast<unsigned char>(c));
                }), s.end());
    return s;
}


std::string Parser::_eraseComment(std::string s)
{
    std::size_t pos = s.find("//");
    if (pos != std::string::npos) {
        s.erase(s.begin() + pos, s.end());
    }
    return s;
}


CommandType Parser::_checkCommandType(std::string s)
{
    // WIP Exceptional form check
    if (s[0] == '@') {
        _commandType = CommandType::A_COMMAND;
    } else if (s[0] == '(') {
        _commandType = CommandType::L_COMMAND;
    } else {
        _commandType = CommandType::C_COMMAND;
    }
    return _commandType;
}


std::string Parser::_parseSymbol(std::string s)
{
    s.erase(s.begin(), s.begin() + 1);
    if (_commandType == CommandType::L_COMMAND)
        s.erase(s.end() - 1, s.end());
    _symbol = s;
    return _symbol;
}


std::string Parser::_parseDest(std::string s)
{
    std::size_t pos = s.find('=');
    if (pos == std::string::npos) {
        _dest = "";
    } else {
        _dest = s.substr(0, pos);
    }
    return _dest;
}


std::string Parser::_parseComp(std::string s)
{
    std::size_t pos = s.find('=');
    if (pos == std::string::npos) {
        _comp = s;
    } else {
        _comp = s.substr(pos + 1);
    }
    pos = _comp.find(';');
    if (pos != std::string::npos) {
        _comp = _comp.substr(0, pos);
    }
    return _comp;
}


std::string Parser::_parseJump(std::string s)
{
    std::size_t pos = s.find(';');
    if (pos == std::string::npos) {
        _jump = "";
    } else {
        _jump = s.substr(pos + 1);
    }
    return _jump;
}


bool Parser::advance()
{
    std::string s;
    while (!_ifs.eof() && s.empty()) {
        // WIP error check
        std::getline(_ifs, s);
        s = _eraseSpace(s);
        s = _eraseComment(s);
    }
    if (!s.empty()) {
        if (_checkCommandType(s) == CommandType::C_COMMAND) {
            // WIP Duplicate find =, ;
            _parseDest(s);
            _parseComp(s);
            _parseJump(s);
        } else {
            _parseSymbol(s);
        }
    }
    return !s.empty();
}
