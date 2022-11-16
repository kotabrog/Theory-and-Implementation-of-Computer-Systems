#ifndef COMPILATIONENGINE_HPP
#define COMPILATIONENGINE_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "Type.hpp"
#include "JackTokenizer.hpp"
#include "SymbolTable.hpp"

class CompilationEngine
{
private:
    static std::map<TokenType, std::string> _tokenTypeTable;

    std::ofstream _ofs;
    JackTokenizer _jackTokenizer;
    SymbolTable _symbolTable;
    std::string _className;

    static void _makeTable();

    void _debugTokenizer();

    std::string _getSymbolTableString(std::string name);

    std::string _getTokenValueByType();
    bool _nextToken();
    void _nextTokenError(std::string errMessage = "The code is only written halfway through.");
    bool _checkTokenType(TokenType tokenType);
    void _checkTokenType(TokenType tokenType, std::string errMessage);
    bool _checkKeyWord(KeyWord keyWord);
    void _checkKeyWord(KeyWord keyWord, std::string errMessage);
    bool _checkSymbol(char symbol);
    void _checkSymbol(char symbol, std::string errMessage);

    void _writeBegin(std::string s);
    void _writeEnd(std::string s);
    void _writeBetween(std::string label, std::string s);
    void _writeBetween(TokenType label, std::string s);
    void _writeBetween();

    void _compileError(std::string s = "");

    bool _isClassVarDec();
    bool _isSubroutineDec();
    bool _istype();
    void _istype(std::string errMessage);
    std::string _typeToString();
    bool _isKeywordConstant();
    bool _isOp();
    bool _isUnaryOp();

    void compileClassVarDec();
    void compileSubroutine();
    void compileParameterList();
    void compileSubroutineBody();
    void compileVarDec();
    void compileStatements();
    void compileLet();
    void compileIf();
    void compileWhile();
    void compileDo();
    void compileReturn();
    void compileExpression();
    void compileSubroutineCall(std::string subroutineName = "");
    void compileTerm();
    void compileExpressionList();


public:
    CompilationEngine(std::string filePath, std::string outPath);
    void CompileClass();
};

#endif
