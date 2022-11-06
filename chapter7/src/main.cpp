#include "../inc/VMtranslator.hpp"

std::string getDirName(const std::string &path)
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

    return "";
}

std::string fileCheck(std::string fileName, DIR* dp)
{
    std::string outPath;
    dp = opendir(fileName.c_str());
    if (dp != NULL) {
        outPath = fileName + "/" + getDirName(fileName) + ".asm";
    } else {
        std::size_t pos = fileName.rfind('.');
        if (pos == std::string::npos || fileName.substr(pos, 3) != ".vm") {
            std::cerr << "specify files with .asm extension" << std::endl;
            std::exit(1);
        }
        outPath = fileName.substr(0, pos) + ".asm";
    }
    return outPath;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "specify a file name" << std::endl;
        std::exit(1);
    }
    DIR* dp = NULL;
    std::string outPath = fileCheck(argv[1], dp);
    Parser::makeCommandMap();
    // WIP ディレクトリの場合
    Parser parser(argv[1]);
    while (parser.hasMoreCommands() && parser.advance()) {
        ;
    }
}
