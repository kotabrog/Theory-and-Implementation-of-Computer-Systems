#include "../inc/CompilationEngine.hpp"

CompilationEngine::CompilationEngine(std::string filePath, std::string outPath)
    : _ofs(outPath), _jackTokenizer(filePath)
{
    if (!_ofs) {
        std::cerr << "Could not open file" << std::endl;
        std::exit(1);
    }
}


void CompilationEngine::CompileClass()
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
