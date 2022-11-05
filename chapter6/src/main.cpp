#include "../inc/Assembler.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "specify a file name" << std::endl;
        std::exit(1);
    }
    // ファイルの確認
    Parser parser(argv[1]);
    while (parser.hasMoreCommands()) {
        if (!parser.advance()) {
            std::cout << "empty" << std::endl;
        }
    }
}
