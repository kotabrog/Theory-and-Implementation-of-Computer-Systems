#include "../inc/CompilationEngine.hpp"

std::map<TokenType, std::string> CompilationEngine::_tokenTypeTable;


void CompilationEngine::_makeTable()
{
    _tokenTypeTable[TokenType::KEYWORD] = "keyword";
    _tokenTypeTable[TokenType::SYMBOL] = "symbol";
    _tokenTypeTable[TokenType::IDENTIFIER] = "identifier";
    _tokenTypeTable[TokenType::INT_CONST] = "integerConstant";
    _tokenTypeTable[TokenType::STRING_CONST] = "stringConstant";
}


CompilationEngine::CompilationEngine(std::string filePath, std::string outPath)
    : _ofs(outPath), _jackTokenizer(filePath)
{
    if (!_ofs) {
        std::cerr << "Could not open file" << std::endl;
        std::exit(1);
    }
    if (_tokenTypeTable.empty()) {
        _makeTable();
    }
}


void CompilationEngine::_debugTokenizer()
{
    _ofs << "<tokens>" << std::endl;
    while (_jackTokenizer.hasMoreTokens() && _jackTokenizer.advance()) {
        if (_jackTokenizer.tokenType() == TokenType::KEYWORD) {
            _ofs << "<keyword> " << _jackTokenizer.stringVal() << "</keyword>" << std::endl;
        } else if (_jackTokenizer.tokenType() == TokenType::SYMBOL) {
            if (_jackTokenizer.symbol() == '<')
                _ofs << "<symbol> " << "&lt;" << " </symbol>" << std::endl;
            else if (_jackTokenizer.symbol() == '>')
                _ofs << "<symbol> " << "&gt;" << " </symbol>" << std::endl;
            else if (_jackTokenizer.symbol() == '&')
                _ofs << "<symbol> " << "&amp;" << " </symbol>" << std::endl;
            else
                _ofs << "<symbol> " << _jackTokenizer.symbol() << " </symbol>" << std::endl;
        } else if (_jackTokenizer.tokenType() == TokenType::IDENTIFIER) {
            _ofs << "<identifier> " << _jackTokenizer.identifier() << " </identifier>" << std::endl;
        } else if (_jackTokenizer.tokenType() == TokenType::INT_CONST) {
            _ofs << "<integerConstant> " << _jackTokenizer.intVal() << " </integerConstant>" << std::endl;
        } else {
            _ofs << "<stringConstant> " << _jackTokenizer.stringVal() << " </stringConstant>" << std::endl;
        }
    }
    _ofs << "</tokens>" << std::endl;
}


std::string CompilationEngine::_getSymbolTableString(std::string name)
{
    Kind kind = _symbolTable.kindOf(name);
    if (kind == Kind::NONE)
        return name;
    std::string kindStr;
    if (kind == Kind::STATIC)
        kindStr = "static";
    else if (kind == Kind::FIELD)
        kindStr = "field";
    else if (kind == Kind::ARG)
        kindStr = "arg";
    else
        kindStr = "var";
    std::string type = _symbolTable.typeOf(name);
    int index = _symbolTable.indexOf(name);
    return name + " | " + kindStr + " | " + type + " | " + std::to_string(index);
}


std::string CompilationEngine::_getTokenValueByType()
{
    if (_jackTokenizer.tokenType() == TokenType::KEYWORD) {
        return _jackTokenizer.stringVal();
    } else if (_jackTokenizer.tokenType() == TokenType::SYMBOL) {
        if (_jackTokenizer.symbol() == '<')
            return "&lt;";
        if (_jackTokenizer.symbol() == '>')
            return "&gt;";
        if (_jackTokenizer.symbol() == '&')
            return "&amp;";
        return {_jackTokenizer.symbol()};
    } else if (_jackTokenizer.tokenType() == TokenType::IDENTIFIER) {
        return _getSymbolTableString(_jackTokenizer.identifier());
    } else if (_jackTokenizer.tokenType() == TokenType::INT_CONST) {
        return std::to_string(_jackTokenizer.intVal());
    } else {
        return _jackTokenizer.stringVal();
    }
}


bool CompilationEngine::_nextToken()
{
    return _jackTokenizer.hasMoreTokens() && _jackTokenizer.advance();
}


void CompilationEngine::_nextTokenError(std::string errMessage)
{
    if (!_nextToken())
        _compileError(errMessage);
}


bool CompilationEngine::_checkTokenType(TokenType tokenType)
{
    return (tokenType == _jackTokenizer.tokenType());
}


void CompilationEngine::_checkTokenType(TokenType tokenType,
                                        std::string errMessage)
{
    if (tokenType != _jackTokenizer.tokenType())
        _compileError(errMessage);
}


bool CompilationEngine::_checkKeyWord(KeyWord keyWord)
{
    return (_jackTokenizer.tokenType() == TokenType::KEYWORD &&
            _jackTokenizer.keyWord() == keyWord);
}


void CompilationEngine::_checkKeyWord(KeyWord keyWord,
                                      std::string errMessage)
{
    if (_jackTokenizer.tokenType() != TokenType::KEYWORD ||
            _jackTokenizer.keyWord() != keyWord)
        _compileError(errMessage);
}


bool CompilationEngine::_checkSymbol(char symbol)
{
    return (_jackTokenizer.tokenType() == TokenType::SYMBOL &&
            _jackTokenizer.symbol() == symbol);
}


void CompilationEngine::_checkSymbol(char symbol,
                                     std::string errMessage)
{
    if (_jackTokenizer.tokenType() != TokenType::SYMBOL ||
            _jackTokenizer.symbol() != symbol)
        _compileError(errMessage);
}


void CompilationEngine::_writeBegin(std::string s)
{
    _ofs << "<" << s << ">" << std::endl;
}


void CompilationEngine::_writeEnd(std::string s)
{
    _ofs << "</" << s << ">" << std::endl;
}


void CompilationEngine::_writeBetween(std::string label, std::string s)
{
    _ofs << "<" << label << "> " << s << " </" << label << ">" << std::endl;
}


void CompilationEngine::_writeBetween(TokenType label, std::string s)
{
    _writeBetween(_tokenTypeTable[label], s);
}


void CompilationEngine::_writeBetween()
{
    _writeBetween(_jackTokenizer.tokenType(), _getTokenValueByType());
}


void CompilationEngine::_compileError(std::string s)
{
    std::cerr << "compile error: " << s << std::endl;
    std::exit(1);
}


bool CompilationEngine::_isClassVarDec()
{
    return _checkKeyWord(KeyWord::STATIC) ||
            _checkKeyWord(KeyWord::FIELD);
}


bool CompilationEngine::_isSubroutineDec()
{
    return _checkKeyWord(KeyWord::CONSTRUCTOR) ||
            _checkKeyWord(KeyWord::FUNCTION) ||
            _checkKeyWord(KeyWord::METHOD);
}


bool CompilationEngine::_istype()
{
    return _checkKeyWord(KeyWord::INT) ||
            _checkKeyWord(KeyWord::CHAR) ||
            _checkKeyWord(KeyWord::BOOLEAN) ||
            _checkTokenType(TokenType::IDENTIFIER);
}


void CompilationEngine::_istype(std::string errMessage)
{
    if (!_istype())
        _compileError(errMessage);
}


std::string CompilationEngine::_typeToString()
{
    if (_checkKeyWord(KeyWord::INT))
        return "int";
    if (_checkKeyWord(KeyWord::CHAR))
        return "char";
    if (_checkKeyWord(KeyWord::BOOLEAN))
        return "boolean";
    return _jackTokenizer.identifier();
}


bool CompilationEngine::_isKeywordConstant()
{
    return _checkKeyWord(KeyWord::TRUE) ||
            _checkKeyWord(KeyWord::FALSE) ||
            _checkKeyWord(KeyWord::NULL_) ||
            _checkKeyWord(KeyWord::THIS);
}


bool CompilationEngine::_isOp()
{
    return _checkSymbol('+') ||
            _checkSymbol('-') ||
            _checkSymbol('*') ||
            _checkSymbol('/') ||
            _checkSymbol('&') ||
            _checkSymbol('|') ||
            _checkSymbol('<') ||
            _checkSymbol('>') ||
            _checkSymbol('=');
}


bool CompilationEngine::_isUnaryOp()
{
    return _checkSymbol('-') ||
            _checkSymbol('~');
}


void CompilationEngine::compileClassVarDec()
{
    _writeBegin("classVarDec");
    Kind kind = (_jackTokenizer.keyWord() == KeyWord::STATIC) ? Kind::STATIC : Kind::FIELD;
    _writeBetween();
    _nextTokenError();
    _istype("Not classVarDec type");
    std::string type = _typeToString();
    _writeBetween();
    _nextTokenError();
    _checkTokenType(TokenType::IDENTIFIER, "Not classVarDec varName");
    _symbolTable.define(_jackTokenizer.identifier(), type, kind);
    _writeBetween();
    _nextTokenError();
    while (_checkSymbol(',')) {
        _writeBetween();
        _nextTokenError();
        _checkTokenType(TokenType::IDENTIFIER, "Not classVarDec varName");
        _symbolTable.define(_jackTokenizer.identifier(), type, kind);
        _writeBetween();
        _nextTokenError();
    }
    _checkSymbol(';', "Not classVarDec ;");
    _writeBetween();
    _writeEnd("classVarDec");
}


void CompilationEngine::compileParameterList()
{
    _writeBegin("parameterList");
    if (_istype()) {
        _writeBetween();
        _nextTokenError();
        _checkTokenType(TokenType::IDENTIFIER, "Not parameterList varName");
        _writeBetween();
        _nextTokenError();
        while (_checkSymbol(',')) {
            _writeBetween();
            _nextTokenError();
            _istype("Not parameterList type");
            _writeBetween();
            _nextTokenError();
            _checkTokenType(TokenType::IDENTIFIER, "Not parameterList varName");
            _writeBetween();
            _nextTokenError();
        }
    }
    _writeEnd("parameterList");
}


void CompilationEngine::compileVarDec()
{
    _writeBegin("varDec");
    _writeBetween();
    _nextTokenError();
    _istype("Not varDec type");
    _writeBetween();
    _nextTokenError();
    _checkTokenType(TokenType::IDENTIFIER, "Not varDec varName");
    _writeBetween();
    _nextTokenError();
    while (_checkSymbol(',')) {
        _writeBetween();
        _nextTokenError();
        _checkTokenType(TokenType::IDENTIFIER, "Not varDec varName");
        _writeBetween();
        _nextTokenError();
    }
    _checkSymbol(';', "Not varDec ;");
    _writeBetween();
    _writeEnd("varDec");
}


void CompilationEngine::compileTerm()
{
    _writeBegin("term");
    if (_checkTokenType(TokenType::INT_CONST) ||
            _checkTokenType(TokenType::STRING_CONST) ||
            _isKeywordConstant()) {
        _writeBetween();
        _nextTokenError();
    } else if (_checkSymbol('(')) {
        _writeBetween();
        _nextTokenError();
        compileExpression();
        _checkSymbol(')', "Not compileTerm )");
        _writeBetween();
        _nextTokenError();
    } else if (_isUnaryOp()) {
        _writeBetween();
        _nextTokenError();
        compileTerm();
    } else {
        _checkTokenType(TokenType::IDENTIFIER, "Not compileTerm IDENTIFIER");
        std::string identifier = _jackTokenizer.identifier();
        _nextTokenError();
        if (_checkSymbol('[')) {
            _writeBetween(TokenType::IDENTIFIER, identifier);
            _writeBetween();
            _nextTokenError();
            compileExpression();
            _checkSymbol(']', "Not compileTerm ]");
            _writeBetween();
            _nextTokenError();
        } else if (_checkSymbol('.') || _checkSymbol('(')){
            compileSubroutineCall(identifier);
            _nextTokenError();
        } else {
            _writeBetween(TokenType::IDENTIFIER, identifier);
        }
    }
    _writeEnd("term");
}


void CompilationEngine::compileExpression()
{
    _writeBegin("expression");
    compileTerm();
    while (_isOp()) {
        _writeBetween();
        _nextTokenError();
        compileTerm();
    }
    _writeEnd("expression");
}


void CompilationEngine::compileExpressionList()
{
    _writeBegin("expressionList");
    if (!_checkSymbol(')')) {
        compileExpression();
        while (_checkSymbol(',')) {
            _writeBetween();
            _nextTokenError();
            compileExpression();
        }
    }
    _writeEnd("expressionList");
}


void CompilationEngine::compileSubroutineCall(std::string subroutineName)
{
    if (subroutineName.empty()) {
        _checkTokenType(TokenType::IDENTIFIER, "Not SubroutineCall subroutineName");
        _writeBetween();
        _nextTokenError();
    } else {
        _writeBetween(TokenType::IDENTIFIER, subroutineName);
    }
    if (_checkSymbol('.')) {
        _writeBetween();
        _nextTokenError();
        _checkTokenType(TokenType::IDENTIFIER, "Not SubroutineCall subroutineName");
        _writeBetween();
        _nextTokenError();
    }
    _checkSymbol('(', "Not SubroutineCall (");
    _writeBetween();
    _nextTokenError();
    compileExpressionList();
    _checkSymbol(')', "Not SubroutineCall )");
    _writeBetween();
}


void CompilationEngine::compileLet()
{
    _writeBegin("letStatement");
    _writeBetween();
    _nextTokenError();
    _checkTokenType(TokenType::IDENTIFIER, "Not letStatement varName");
    _writeBetween();
    _nextTokenError();
    if (_checkSymbol('[')) {
        _writeBetween();
        _nextTokenError();
        compileExpression();
        _checkSymbol(']', "Not letStatement ]");
        _writeBetween();
        _nextTokenError();
    }
    _checkSymbol('=', "Not letStatement =");
    _writeBetween();
    _nextTokenError();
    compileExpression();
    _checkSymbol(';', "Not letStatement ;");
    _writeBetween();
    _nextTokenError();
    _writeEnd("letStatement");
}


void CompilationEngine::compileIf()
{
    _writeBegin("ifStatement");
    _writeBetween();
    _nextTokenError();
    _checkSymbol('(', "Not ifStatement (");
    _writeBetween();
    _nextTokenError();
    compileExpression();
    _checkSymbol(')', "Not ifStatement )");
    _writeBetween();
    _nextTokenError();
    _checkSymbol('{', "Not ifStatement {");
    _writeBetween();
    _nextTokenError();
    compileStatements();
    _checkSymbol('}', "Not ifStatement }");
    _writeBetween();
    _nextTokenError();
    if (_checkKeyWord(KeyWord::ELSE)) {
        _writeBetween();
        _nextTokenError();
        _checkSymbol('{', "Not ifStatement {");
        _writeBetween();
        _nextTokenError();
        compileStatements();
        _checkSymbol('}', "Not ifStatement }");
        _writeBetween();
        _nextTokenError();
    }
    _writeEnd("ifStatement");
}


void CompilationEngine::compileWhile()
{
    _writeBegin("whileStatement");
    _writeBetween();
    _nextTokenError();
    _checkSymbol('(', "Not whileStatement (");
    _writeBetween();
    _nextTokenError();
    compileExpression();
    _checkSymbol(')', "Not whileStatement )");
    _writeBetween();
    _nextTokenError();
    _checkSymbol('{', "Not whileStatement {");
    _writeBetween();
    _nextTokenError();
    compileStatements();
    _checkSymbol('}', "Not whileStatement }");
    _writeBetween();
    _nextTokenError();
    _writeEnd("whileStatement");
}


void CompilationEngine::compileDo()
{
    _writeBegin("doStatement");
    _writeBetween();
    _nextTokenError();
    compileSubroutineCall();
    _nextTokenError();
    _checkSymbol(';', "Not doStatement ;");
    _writeBetween();
    _nextTokenError();
    _writeEnd("doStatement");
}


void CompilationEngine::compileReturn()
{
    _writeBegin("returnStatement");
    _writeBetween();
    _nextTokenError();
    if (!_checkSymbol(';')) {
        compileExpression();
    }
    _checkSymbol(';', "Not returnStatement ;");
    _writeBetween();
    _nextTokenError();
    _writeEnd("returnStatement");
}


void CompilationEngine::compileStatements()
{
    _writeBegin("statements");
    while (true) {
        if (_checkKeyWord(KeyWord::LET))
            compileLet();
        else if (_checkKeyWord(KeyWord::IF))
            compileIf();
        else if (_checkKeyWord(KeyWord::WHILE))
            compileWhile();
        else if (_checkKeyWord(KeyWord::DO))
            compileDo();
        else if (_checkKeyWord(KeyWord::RETURN))
            compileReturn();
        else
            break;
    }
    _writeEnd("statements");
}


void CompilationEngine::compileSubroutineBody()
{
    _writeBegin("subroutineBody");
    _checkSymbol('{', "Not subroutineBody {");
    _writeBetween();
    _nextTokenError();
    while (_checkKeyWord(KeyWord::VAR)) {
        compileVarDec();
        _nextTokenError();
    }
    compileStatements();
    _checkSymbol('}', "Not subroutineBody }");
    _writeBetween();
    _writeEnd("subroutineBody");
}


void CompilationEngine::compileSubroutine()
{
    _writeBegin("subroutineDec");
    _writeBetween();
    _nextTokenError();
    if (!_checkKeyWord(KeyWord::VOID) && !_istype())
        _compileError("Not subroutineDec type");
    _writeBetween();
    _nextTokenError();
    _checkTokenType(TokenType::IDENTIFIER, "Not subroutineDec subroutineName");
    _writeBetween();
    _nextTokenError();
    _checkSymbol('(', "Not subroutineDec (");
    _writeBetween();
    _nextTokenError();
    compileParameterList();
    _checkSymbol(')', "Not subroutineDec )");
    _writeBetween();
    _nextTokenError();
    compileSubroutineBody();
    _writeEnd("subroutineDec");
}


void CompilationEngine::CompileClass()
{
    _writeBegin("class");
    _nextTokenError();
    _checkKeyWord(KeyWord::CLASS, "Not class");
    _writeBetween();
    _nextTokenError();
    _checkTokenType(TokenType::IDENTIFIER, "Not class name");
    _writeBetween();
    _nextTokenError();
    _checkSymbol('{', "Not class {");
    _writeBetween();
    _nextTokenError();
    while (_isClassVarDec()) {
        compileClassVarDec();
        _nextTokenError();
    }
    while (_isSubroutineDec()) {
        compileSubroutine();
        _nextTokenError();
    }
    _checkSymbol('}', "Not class }");
    _writeBetween();
    _writeEnd("class");
}
