#ifndef CODEWRITER_HPP
#define CODEWRITER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "CommandType.hpp"

class CodeWriter
{
private:
    std::ofstream _ofs;
    std::string _fileName;

    void _writeACommand(std::string str);
    void _writeACommand(int value);
    void _writeCCommand(std::string dest, std::string comp, std::string jump);
    void _writeAdd();
    void _writeConstantPush(int value);

public:
    CodeWriter(std::string& filePath);
    void setFileName(std::string fileName);
    void writeArithmetic(std::string command);
    void writePushPop(CommandType command, std::string segment, int index);
};

#endif
