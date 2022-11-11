#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "Type.hpp"

class JackTokenizer
{
private:
    std::ifstream _ifs;
    std::string _restStr;
    TokenType _tokenType;
    KeyWord _keyWord;
    char _symbol;
    std::string _identifier;
    int _intVal;
    std::string _stringVal;

    std::string _ltrim(std::string s);
    std::string _rtrim(std::string s);
    std::string _trim(std::string s);
    std::string _eraseCommentBegin(std::string s);
    std::string _eraseCommentBetween(std::string s, std::string begin,
                                                    std::string end);
    std::string _eraseComment(std::string s);

public:
    JackTokenizer(std::string filePath);
    bool hasMoreTokens();
    bool advance();
    TokenType tokenType() {return _tokenType;}
    KeyWord keyWord() {return _keyWord;}
    char symbol() {return _symbol;}
    std::string identifier() {return _identifier;}
    int intVal() {return _intVal;}
    std::string stringVal() {return _stringVal;}
};

#endif