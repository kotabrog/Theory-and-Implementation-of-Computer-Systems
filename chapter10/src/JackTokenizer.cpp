#include "../inc/JackTokenizer.hpp"

std::map<std::string, KeyWord> JackTokenizer::_keyWordTable;
std::set<char> JackTokenizer::_symbolTable;


void JackTokenizer::makeTable()
{
    _keyWordTable["class"] = KeyWord::CLASS;
    _keyWordTable["method"] = KeyWord::METHOD;
    _keyWordTable["function"] = KeyWord::FUNCTION;
    _keyWordTable["constructor"] = KeyWord::CONSTRUCTOR;
    _keyWordTable["field"] = KeyWord::FIELD;
    _keyWordTable["static"] = KeyWord::STATIC;
    _keyWordTable["var"] = KeyWord::VAR;
    _keyWordTable["int"] = KeyWord::INT;
    _keyWordTable["char"] = KeyWord::CHAR;
    _keyWordTable["boolean"] = KeyWord::BOOLEAN;
    _keyWordTable["void"] = KeyWord::VOID;
    _keyWordTable["true"] = KeyWord::TRUE;
    _keyWordTable["false"] = KeyWord::FALSE;
    _keyWordTable["null"] = KeyWord::NULL_;
    _keyWordTable["this"] = KeyWord::THIS;
    _keyWordTable["let"] = KeyWord::LET;
    _keyWordTable["do"] = KeyWord::DO;
    _keyWordTable["if"] = KeyWord::IF;
    _keyWordTable["else"] = KeyWord::ELSE;
    _keyWordTable["while"] = KeyWord::WHILE;
    _keyWordTable["return"] = KeyWord::RETURN;

    _symbolTable.insert('{');
    _symbolTable.insert('}');
    _symbolTable.insert('(');
    _symbolTable.insert(')');
    _symbolTable.insert('[');
    _symbolTable.insert(']');
    _symbolTable.insert('.');
    _symbolTable.insert(',');
    _symbolTable.insert(';');
    _symbolTable.insert('+');
    _symbolTable.insert('-');
    _symbolTable.insert('*');
    _symbolTable.insert('/');
    _symbolTable.insert('&');
    _symbolTable.insert('|');
    _symbolTable.insert('<');
    _symbolTable.insert('>');
    _symbolTable.insert('=');
    _symbolTable.insert('~');
}


JackTokenizer::JackTokenizer(std::string filePath)
    : _ifs(filePath), _commentFlag(false)
{
    if (!_ifs) {
        std::cerr << "Could not open file" << std::endl;
        std::exit(1);
    }
}


bool JackTokenizer::hasMoreTokens()
{
    return !_restStr.empty() || !_ifs.eof();
}


std::string JackTokenizer::_ltrim(std::string s)
{
    const std::string space = " \n\r\t\f\v";
    std::size_t start = s.find_first_not_of(space);
    return (start == std::string::npos) ? "" : s.substr(start);
}


std::string JackTokenizer::_rtrim(std::string s)
{
    const std::string space = " \n\r\t\f\v";
    size_t end = s.find_last_not_of(space);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}


std::string JackTokenizer::_trim(std::string s)
{
    return _rtrim(_ltrim(s));
}


std::string JackTokenizer::_eraseComment(std::string s)
{
    bool continueFlag = true;
    while (continueFlag) {
        continueFlag = false;
        std::size_t pos1 = 0;
        std::size_t pos3 = s.find("//");
        if (!_commentFlag) {
            pos1 = s.find("/*");
            if (pos3 < pos1) {
                s.erase(s.begin() + pos3, s.end());
            } else if (pos1 != std::string::npos) {
                _commentFlag = true;
            }
        }
        if (_commentFlag) {
            std::size_t pos2 = s.find("*/");
            if (pos2 == std::string::npos) {
                s.erase(pos1);
            } else {
                s.erase(s.begin() + pos1, s.begin() + pos2 + 2);
                _commentFlag = false;
                continueFlag = true;
            }
        }
    }
    return s;
}


void JackTokenizer::_getNextLine()
{
    std::string s;
    while (!_ifs.eof() && s.empty()) {
        // WIP error check
        std::getline(_ifs, s);
        s = _eraseComment(s);
        s = _trim(s);
    }
    _restStr = s;
}


void JackTokenizer::_getNextToken(std::string s)
{
    std::size_t length = s.size();
    bool stringFlag = false;

    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '"') {
            if (!stringFlag)
                stringFlag = true;
            else {
                length = i + 1;
                break;
            }
        }
        if (!stringFlag && (_symbolTable.count(s[i]) || std::isspace(s[i]))) {
            if (i == 0)
                length = 1;
            else if (i != 0)
                length = i;
            break;
        }
    }
    _stringVal = s.substr(0, length);
    s.erase(0, length);
    _restStr = _ltrim(s);
}


void JackTokenizer::_determineType(std::string s)
{
    if (_keyWordTable.count(s)) {
        _tokenType = TokenType::KEYWORD;
        _keyWord = _keyWordTable[s];
    } else if (_symbolTable.count(s[0])) {
        _tokenType = TokenType::SYMBOL;
        _symbol = s[0];
    } else if (s[0] == '"') {
        _tokenType = TokenType::STRING_CONST;
        _stringVal = s.substr(1, s.size() - 2);
    } else if ('0' <= s[0] && s[0] <= '9') {
        _tokenType = TokenType::INT_CONST;
        _intVal = std::stoi(s);
    } else {
        _tokenType = TokenType::IDENTIFIER;
    }
}


bool JackTokenizer::advance()
{
    if (_restStr.empty())
        _getNextLine();
    if (_restStr.empty())
        return false;
    _getNextToken(_restStr);
    _determineType(_stringVal);
    return !_stringVal.empty();
}
