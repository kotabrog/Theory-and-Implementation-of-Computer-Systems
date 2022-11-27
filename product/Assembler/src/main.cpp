#include "../inc/Assembler.hpp"

std::string fileNameCheck(std::string fileName)
{
    std::size_t pos = fileName.rfind('.');
    if (pos == std::string::npos || fileName.substr(pos, 4) != ".asm") {
        std::cerr << "specify files with .asm extension" << std::endl;
        std::exit(1);
    }
    return fileName.substr(0, pos) + ".hack";
}

void setSymbolTable(SymbolTable& symbolTable, std::string fileName)
{
    int row = 0;
    Parser parser(fileName);
    while (parser.hasMoreCommands() && parser.advance()) {
        if (parser.commandType() == CommandType::L_COMMAND) {
            // WIP error handling for duplicates
            symbolTable.addEntity(parser.symbol(), row);
        } else {
            row += 1;
        }
    }
}

void assemble(SymbolTable& symbolTable, std::string fileName, std::ofstream &ofs)
{
    Parser parser(fileName);
    int newVariable = 16;
    while (parser.hasMoreCommands() && parser.advance()) {
        if (parser.commandType() == CommandType::C_COMMAND) {
            Code code;
            std::bitset<3> dest = code.dest(parser.dest());
            std::bitset<7> comp = code.comp(parser.comp());
            std::bitset<3> jump = code.jump(parser.jump());
            ofs << "111" << comp << dest << jump << std::endl;
        } else if (parser.commandType() == CommandType::A_COMMAND) {
            int symbolValue;
            try {
                symbolValue = std::stoi(parser.symbol());
            } catch(const std::exception& e) {
                if (!symbolTable.contains(parser.symbol())) {
                    symbolTable.addEntity(parser.symbol(), newVariable++);
                }
                symbolValue = symbolTable.getAddress(parser.symbol());
            }
            std::bitset<15> symbol(symbolValue);
            ofs << "0" << symbol << std::endl;
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "specify a file name" << std::endl;
        std::exit(1);
    }
    std::string outPath = fileNameCheck(argv[1]);
    // WIP error handling
    std::ofstream ofs(outPath);
    SymbolTable symbolTable;
    setSymbolTable(symbolTable, argv[1]);
    assemble(symbolTable, argv[1], ofs);
}
