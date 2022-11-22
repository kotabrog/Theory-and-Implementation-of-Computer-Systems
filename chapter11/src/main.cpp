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
    return filePath.substr(0, pos) + ".vm";
}


void oneFileCompile(bool debugMode, std::string filePath, std::string outPath)
{
    CompilationEngine compilationEngine(debugMode, filePath, outPath);
    compilationEngine.CompileClass();
}


int main(int argc, char** argv)
{
    bool debugMode = false;
    if (argc == 3) {
        if (argv[2] == std::string("-debug")) {
            std::cout << debugMode << std::endl;
        }
    } else if (argc != 2) {
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
        oneFileCompile(debugMode, inputPath, outPath);
    } else {
        dirent* entry = readdir(dp);
        while (entry != NULL) {
            std::string fileName = entry->d_name;
            std::string outName = fileCheck(fileName);
            if (!outName.empty()) {
                std::cout << "Compile: " << fileName << std::endl;
                oneFileCompile(debugMode, inputPath + "/" + fileName, inputPath + "/" + outName);
            }
            entry = readdir(dp);
        }
    }
}
