#ifndef CODEWRITER_HPP
#define CODEWRITER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "CommandType.hpp"

class CodeWriter
{
private:
    static int _relationalLabelNum;
    static int _returnAddressNum;

    static std::string _makeRelationalLabel();
    static std::string _makeReturnAddress();

    std::ofstream _ofs;
    std::string _fileName;
    std::string _functionNames;

    void _writeACommand(std::string str);
    void _writeACommand(int value);
    void _writeCCommand(std::string dest, std::string comp, std::string jump);
    void _writeLabel(std::string label);
    void _writePopStackAndSetA();
    void _writeSPPlus();
    void _writeSetSPAddress();
    void _writeSetBeforeSPAddress();
    void _writeDPush();
    void _writeDSetR(int index);
    void _writeSetRAddress(int index);
    void _writeSetBaseAddressPlusIndex(std::string &segment, int index);
    void _writeSetDirectMapAddressPlusIndex(std::string &segment, int index);
    void _writeNormalBinaryFunction(std::string &command);
    void _writeUnaryFunction(std::string &command);
    void _writeRelationalFunction(std::string &command);
    void _writeConstantPush(int value);
    void _writeBaseAddressValuePush(std::string &segment, int index);
    void _writeDirectMapAddressValuePush(std::string &segment, int index);
    void _writeStaticPush(int index);
    void _writeBaseAddressValuePop(std::string &segment, int index);
    void _writeDirectMapAddressValuePop(std::string &segment, int index);
    void _writeStaticPop(int index);

public:
    CodeWriter(std::string& filePath);
    void setFileName(std::string fileName);
    void writeArithmetic(std::string command);
    void writePushPop(CommandType command, std::string segment, int index);
    void writeLabel(std::string label);
    void writeGoto(std::string label);
    void writeIf(std::string label);
    void writeFunction(std::string functionName, int numLocals);
    void writeReturn();
    void writeCall(std::string functionName, int numArgs);
    void writeInit();
};

#endif
