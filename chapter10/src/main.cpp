#include "../inc/JackAnalyzer.hpp"

std::string getFileName(const std::string &path)
{
    // WIP If the path ends with a slash
    size_t pos;

    pos = path.rfind('\\');
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }

    pos = path.rfind('/');
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }

    return path;
}


std::string fileCheck(std::string filePath)
{
    std::size_t pos = filePath.rfind('.');
    if (pos == std::string::npos || filePath.substr(pos, 5) != ".jack") {
        return "";
    }
    return filePath.substr(0, pos) + ".xml";
}


void oneFileCompile(std::string filePath, std::string outPath)
{
    JackTokenizer jackTokenizer(filePath);
    std::ofstream ofs(outPath);
    ofs << "<tokens>" << std::endl;
    while (jackTokenizer.hasMoreTokens() && jackTokenizer.advance()) {
        if (jackTokenizer.tokenType() == TokenType::KEYWORD) {
            ofs << "<keyword> " << jackTokenizer.stringVal() << "</keyword>" << std::endl;
        } else if (jackTokenizer.tokenType() == TokenType::SYMBOL) {
            if (jackTokenizer.symbol() == '<')
                ofs << "<symbol> " << "&lt;" << " </symbol>" << std::endl;
            else if (jackTokenizer.symbol() == '>')
                ofs << "<symbol> " << "&gt;" << " </symbol>" << std::endl;
            else if (jackTokenizer.symbol() == '&')
                ofs << "<symbol> " << "&amp;" << " </symbol>" << std::endl;
            else
                ofs << "<symbol> " << jackTokenizer.symbol() << " </symbol>" << std::endl;
        } else if (jackTokenizer.tokenType() == TokenType::IDENTIFIER) {
            ofs << "<identifier> " << jackTokenizer.identifier() << " </identifier>" << std::endl;
        } else if (jackTokenizer.tokenType() == TokenType::INT_CONST) {
            ofs << "<integerConstant> " << jackTokenizer.intVal() << " </integerConstant>" << std::endl;
        } else {
            ofs << "<stringConstant> " << jackTokenizer.stringVal() << " </stringConstant>" << std::endl;
        }
    }
    ofs << "</tokens>" << std::endl;
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "specify a file name" << std::endl;
        std::exit(1);
    }
    DIR* dp = NULL;
    dp = opendir(argv[1]);
    std::string inputPath(argv[1]);
    JackTokenizer::makeTable();

    if (dp == NULL) {
        std::string outPath = fileCheck(inputPath);
        if (outPath.empty()) {
            std::cerr << "specify files with .jack extension" << std::endl;
            std::exit(1);
        }
        oneFileCompile(inputPath, outPath);
    } else {
        dirent* entry = readdir(dp);
        while (entry != NULL) {
            std::string fileName = entry->d_name;
            std::string outName = fileCheck(fileName);
            if (!outName.empty()) {
                std::cout << "Compile: " << fileName << std::endl;
                oneFileCompile(inputPath + "/" + fileName, inputPath + "/" + outName);
            }
            entry = readdir(dp);
        }
    }
}
