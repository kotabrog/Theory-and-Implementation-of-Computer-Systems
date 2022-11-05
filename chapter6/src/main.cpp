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

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "specify a file name" << std::endl;
        std::exit(1);
    }
    std::string outPath = fileNameCheck(argv[1]);
    // WIP error handling
    std::ofstream ofs(outPath);
    Parser parser(argv[1]);
    while (parser.hasMoreCommands() && parser.advance()) {
        if (parser.commandType() == CommandType::C_COMMAND) {
            Code code;
            std::bitset<3> dest = code.dest(parser.dest());
            std::bitset<7> comp = code.comp(parser.comp());
            std::bitset<3> jump = code.jump(parser.jump());
            ofs << "111" << comp << dest << jump << std::endl;
        } else if (parser.commandType() == CommandType::A_COMMAND) {
            std::bitset<15> symbol(std::stoi(parser.symbol()));
            ofs << "0" << symbol << std::endl;
        }
    }
}
