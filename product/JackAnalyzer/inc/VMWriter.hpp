#ifndef VMWRITER_HPP
#define VMWRITER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Type.hpp"

class VMWriter
{
private:
    static std::map<Segment, std::string> _segmentTable;
    static std::map<Command, std::string> _commandTable;
    std::ofstream _ofs;

    void _makeTable();

public:
    VMWriter(std::string outPath);
    void writePush(Segment segment, int index);
    void writePop(Segment segment, int index);
    void writeArithmetic(Command command);
    void writeLabel(std::string label);
    void writeGoto(std::string label);
    void writeIf(std::string label);
    void writeCall(std::string name, int nArgs);
    void writeFunction(std::string name, int nLocals);
    void writeReturn();
};

#endif
