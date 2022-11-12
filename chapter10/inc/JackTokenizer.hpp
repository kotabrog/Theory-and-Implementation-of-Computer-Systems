#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

#include "Type.hpp"

class JackTokenizer
{
private:
    static std::map<std::string, KeyWord> _keyWordTable;
    static std::set<char> _symbolTable;

    std::ifstream _ifs;
    std::string _restStr;
    bool _commentFlag;
    TokenType _tokenType;
    KeyWord _keyWord;
    char _symbol;
    std::string _stringVal;
    int _intVal;

    std::string _ltrim(std::string s);
    std::string _rtrim(std::string s);
    std::string _trim(std::string s);
    std::string _eraseComment(std::string s);

    void _getNextLine();
    void _getNextToken(std::string s);
    void _determineType(std::string s);

public:
    static void makeTable();

    JackTokenizer(std::string filePath);
    bool hasMoreTokens();
    bool advance();
    TokenType tokenType() {return _tokenType;}
    KeyWord keyWord() {return _keyWord;}
    char symbol() {return _symbol;}
    std::string identifier() {return _stringVal;}
    int intVal() {return _intVal;}
    std::string stringVal() {return _stringVal;}
};

#endif