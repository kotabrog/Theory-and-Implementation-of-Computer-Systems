#include "../inc/Assembler.hpp"

void fileNameCheck(std::string fileName)
{
    std::size_t pos = fileName.rfind('.');
    if (pos == std::string::npos || fileName.substr(pos, 4) != ".asm") {
        std::cerr << "specify files with .asm extension" << std::endl;
        std::exit(1);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "specify a file name" << std::endl;
        std::exit(1);
    }
    fileNameCheck(argv[1]);
    Parser parser(argv[1]);
    while (parser.hasMoreCommands() && parser.advance()) {
        ;
    }
}
