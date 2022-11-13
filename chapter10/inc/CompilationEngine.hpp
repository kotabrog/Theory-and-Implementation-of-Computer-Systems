#ifndef COMPILATIONENGINE_HPP
#define COMPILATIONENGINE_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "Type.hpp"
#include "JackTokenizer.hpp"

class CompilationEngine
{
private:
    std::ofstream _ofs;
    JackTokenizer _jackTokenizer;

public:
    CompilationEngine(std::string filePath, std::string outPath);
    void CompileClass();
};

#endif
