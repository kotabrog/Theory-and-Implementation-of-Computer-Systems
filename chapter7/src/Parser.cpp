#include "../inc/Parser.hpp"

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


bool Parser::advance()
{
    std::string s;
    while (!_ifs.eof() && s.empty()) {
        // WIP error check
        std::getline(_ifs, s);
        s = _eraseComment(s);
        s = _trim(s);
    }
    std::cout << s << std::endl;
    return !s.empty();
}
