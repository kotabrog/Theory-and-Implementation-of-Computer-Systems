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


bool Parser::advance()
{
    std::string s;
    while (!_ifs.eof() && s.empty()) {
        std::getline(_ifs, s);
        s = _eraseSpace(s);
    }
    std::cout << s << std::endl;
    return !s.empty();
}
