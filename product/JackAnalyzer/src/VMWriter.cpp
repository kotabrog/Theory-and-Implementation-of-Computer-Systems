#include "../inc/VMWriter.hpp"


std::map<Segment, std::string> VMWriter::_segmentTable;
std::map<Command, std::string> VMWriter::_commandTable;


void VMWriter::_makeTable()
{
    _segmentTable[Segment::CONST] = "constant";
    _segmentTable[Segment::ARG] = "argument";
    _segmentTable[Segment::LOCAL] = "local";
    _segmentTable[Segment::STATIC] = "static";
    _segmentTable[Segment::THIS] = "this";
    _segmentTable[Segment::THAT] = "that";
    _segmentTable[Segment::POINTER] = "pointer";
    _segmentTable[Segment::TEMP] = "temp";

    _commandTable[Command::ADD] = "add";
    _commandTable[Command::SUB] = "sub";
    _commandTable[Command::NEG] = "neg";
    _commandTable[Command::EQ] = "eq";
    _commandTable[Command::GT] = "gt";
    _commandTable[Command::LT] = "lt";
    _commandTable[Command::AND] = "and";
    _commandTable[Command::OR] = "or";
    _commandTable[Command::NOT] = "not";
}


VMWriter::VMWriter(std::string outPath)
    : _ofs(outPath)
{
    if (!_ofs) {
        std::cerr << "Could not open file" << std::endl;
        std::exit(1);
    }
    if (_segmentTable.empty()) {
        _makeTable();
    }
}

void VMWriter::writePush(Segment segment, int index)
{
    _ofs << "push " << _segmentTable[segment] << " " << index << std::endl;
}


void VMWriter::writePop(Segment segment, int index)
{
    _ofs << "pop " << _segmentTable[segment] << " " << index << std::endl;
}


void VMWriter::writeArithmetic(Command command)
{
    _ofs << _commandTable[command] << std::endl;
}


void VMWriter::writeLabel(std::string label)
{
    _ofs << "label " << label << std::endl;
}


void VMWriter::writeGoto(std::string label)
{
    _ofs << "goto " << label << std::endl;
}


void VMWriter::writeIf(std::string label)
{
    _ofs << "if-goto " << label << std::endl;
}


void VMWriter::writeCall(std::string name, int nArgs)
{
    _ofs << "call " << name << " " << nArgs << std::endl;
}


void VMWriter::writeFunction(std::string name, int nLocals)
{
    _ofs << "function " << name << " " << nLocals << std::endl;
}


void VMWriter::writeReturn()
{
    _ofs << "return" << std::endl;
}
