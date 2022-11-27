#include "../inc/CodeWriter.hpp"

int CodeWriter::_relationalLabelNum = 0;
int CodeWriter::_returnAddressNum = 0;


std::string CodeWriter::_makeRelationalLabel()
{
    return "RELATIONAL" + std::to_string(_relationalLabelNum++);
}


std::string CodeWriter::_makeReturnAddress()
{
    return "RETURNADDRESS" + std::to_string(_returnAddressNum++);
}


CodeWriter::CodeWriter(std::string& filePath)
    : _ofs(filePath)
{
    if (!_ofs) {
        std::cerr << "Could not open file" << std::endl;
        std::exit(1);
    }
}


void CodeWriter::setFileName(std::string fileName)
{
    _fileName = fileName;
}


void CodeWriter::_writeACommand(std::string str)
{
    _ofs << "@" << str << std::endl;
}


void CodeWriter::_writeACommand(int value)
{
    _ofs << "@" << value << std::endl;
}


void CodeWriter::_writeCCommand(std::string dest, std::string comp,
                                std::string jump)
{
    if (!dest.empty())
        _ofs << dest << "=";
    if (!comp.empty())
        _ofs << comp;
    if (!jump.empty())
        _ofs << ";" << jump;
    _ofs << std::endl;
}


void CodeWriter::_writeLabel(std::string label)
{
    _ofs << "(" << label << ")" << std::endl;
}


void CodeWriter::_writePopStackAndSetA()
{
    _writeACommand("SP");
    _writeCCommand("M", "M-1", "");
    _writeCCommand("A", "M", "");
}


void CodeWriter::_writeSPPlus()
{
    _writeACommand("SP");
    _writeCCommand("M", "M+1", "");
}


void CodeWriter::_writeSetSPAddress()
{
    _writeACommand("SP");
    _writeCCommand("A", "M", "");
}


void CodeWriter::_writeSetBeforeSPAddress()
{
    _writeACommand("SP");
    _writeCCommand("D", "M-1", "");
    _writeCCommand("A", "D", "");
}


void CodeWriter::_writeDPush()
{
    _writeSetSPAddress();
    _writeCCommand("M", "D", "");
    _writeSPPlus();
}


void CodeWriter::_writeDSetR(int index)
{
    _writeACommand("R" + std::to_string(index));
    _writeCCommand("M", "D", "");
}


void CodeWriter::_writeSetRAddress(int index)
{
    _writeACommand("R" + std::to_string(index));
    _writeCCommand("A", "M", "");
}


void CodeWriter::_writeSetBaseAddressPlusIndex(std::string &segment, int index)
{
    if (segment == "local")
        _writeACommand("LCL");
    else if (segment == "argument")
        _writeACommand("ARG");
    else if (segment == "this")
        _writeACommand("THIS");
    else if (segment == "that")
        _writeACommand("THAT");
    _writeCCommand("D", "M", "");
    _writeACommand(index);
    _writeCCommand("A", "A+D", "");
}


void CodeWriter::_writeSetDirectMapAddressPlusIndex(std::string &segment, int index)
{
    int address = index;
    if (segment == "pointer")
        address += 3;
    else if (segment == "temp")
        address += 5;
    _writeACommand(address);
}


void CodeWriter::_writeNormalBinaryFunction(std::string &command)
{
    _writePopStackAndSetA();
    _writeCCommand("D", "M", "");
    _writePopStackAndSetA();
    if (command == "add")
        _writeCCommand("M", "D+M", "");
    else if (command == "sub")
        _writeCCommand("M", "M-D", "");
    else if (command == "and")
        _writeCCommand("M", "M&D", "");
    else if (command == "or")
        _writeCCommand("M", "M|D", "");
    _writeSPPlus();
}


void CodeWriter::_writeUnaryFunction(std::string &command)
{
    _writeSetBeforeSPAddress();
    if (command == "neg")
        _writeCCommand("M", "-M", "");
    else if (command == "not")
        _writeCCommand("M", "!M", "");
}


void CodeWriter::_writeRelationalFunction(std::string &command)
{
    // WIP Overflow of the difference between two values
    std::string label1 = _makeRelationalLabel();
    std::string label2 = _makeRelationalLabel();
    _writePopStackAndSetA();
    _writeCCommand("D", "M", "");
    _writePopStackAndSetA();
    _writeCCommand("D", "M-D", "");
    _writeACommand(label1);
    if (command == "eq")
        _writeCCommand("", "D", "JEQ");
    else if (command == "gt")
        _writeCCommand("", "D", "JGT");
    else if (command == "lt")
        _writeCCommand("", "D", "JLT");
    _writeSetSPAddress();
    _writeCCommand("M", "0", "");
    _writeACommand(label2);
    _writeCCommand("", "0", "JMP");
    _writeLabel(label1);
    _writeSetSPAddress();
    _writeCCommand("M", "-1", "");
    _writeLabel(label2);
    _writeSPPlus();
}


void CodeWriter::writeArithmetic(std::string command)
{
    if (command == "add" || command == "sub" ||
            command == "and" || command == "or")
        _writeNormalBinaryFunction(command);
    else if (command == "neg" || command == "not")
        _writeUnaryFunction(command);
    else
        _writeRelationalFunction(command);
}


void CodeWriter::_writeConstantPush(int value)
{
    _writeACommand(value);
    _writeCCommand("D", "A", "");
    _writeDPush();
}


void CodeWriter::_writeBaseAddressValuePush(std::string &segment, int index)
{
    _writeSetBaseAddressPlusIndex(segment, index);
    _writeCCommand("D", "M", "");
    _writeDPush();
}


void CodeWriter::_writeDirectMapAddressValuePush(std::string &segment, int index)
{
    _writeSetDirectMapAddressPlusIndex(segment, index);
    _writeCCommand("D", "M", "");
    _writeDPush();
}


void CodeWriter::_writeStaticPush(int index)
{
    _writeACommand(_fileName + "." + std::to_string(index));
    _writeCCommand("D", "M", "");
    _writeDPush();
}


void CodeWriter::_writeBaseAddressValuePop(std::string &segment, int index)
{
    _writeSetBaseAddressPlusIndex(segment, index);
    _writeCCommand("D", "A", "");
    _writeDSetR(13);
    _writePopStackAndSetA();
    _writeCCommand("D", "M", "");
    _writeSetRAddress(13);
    _writeCCommand("M", "D", "");
}


void CodeWriter::_writeDirectMapAddressValuePop(std::string &segment, int index)
{
    _writePopStackAndSetA();
    _writeCCommand("D", "M", "");
    _writeSetDirectMapAddressPlusIndex(segment, index);
    _writeCCommand("M", "D", "");
}


void CodeWriter::_writeStaticPop(int index)
{
    _writePopStackAndSetA();
    _writeCCommand("D", "M", "");
    _writeACommand(_fileName + "." + std::to_string(index));
    _writeCCommand("M", "D", "");
}


void CodeWriter::writePushPop(CommandType command, std::string segment, int index)
{
    if (command == CommandType::C_PUSH && segment == "constant")
        _writeConstantPush(index);
    else if (command == CommandType::C_PUSH &&
                (segment == "local" || segment == "argument" ||
                 segment == "this" || segment == "that"))
        _writeBaseAddressValuePush(segment, index);
    else if (command == CommandType::C_POP &&
                (segment == "local" || segment == "argument" ||
                 segment == "this" || segment == "that"))
        _writeBaseAddressValuePop(segment, index);
    else if (command == CommandType::C_PUSH &&
                (segment == "pointer" || segment == "temp"))
        _writeDirectMapAddressValuePush(segment, index);
    else if (command == CommandType::C_POP &&
                (segment == "pointer" || segment == "temp"))
        _writeDirectMapAddressValuePop(segment, index);
    else if (command == CommandType::C_PUSH && segment == "static")
        _writeStaticPush(index);
    else if (command == CommandType::C_POP && segment == "static")
        _writeStaticPop(index);
}


void CodeWriter::writeLabel(std::string label)
{
    if (_functionNames.empty())
        _writeLabel(_fileName + "$" + label);
    else
        _writeLabel(_functionNames + "$" + label);
}


void CodeWriter::writeGoto(std::string label)
{
    if (_functionNames.empty())
        _writeACommand(_fileName + "$" + label);
    else
        _writeACommand(_functionNames + "$" + label);
    _writeCCommand("", "0", "JMP");
}


void CodeWriter::writeIf(std::string label)
{
    _writePopStackAndSetA();
    _writeCCommand("D", "M", "");
    if (_functionNames.empty())
        _writeACommand(_fileName + "$" + label);
    else
        _writeACommand(_functionNames + "$" + label);
    _writeCCommand("", "D", "JNE");
}


void CodeWriter::writeFunction(std::string functionName, int numLocals)
{
    _writeLabel(functionName);
    _functionNames = functionName;
    for (int i = 0; i < numLocals; ++i) {
        _writeConstantPush(0);
    }
}


void CodeWriter::writeReturn()
{
    // FRAME = LCL
    _writeACommand("LCL");
    _writeCCommand("D", "M", "");
    _writeDSetR(13);

    // RET = *(FRAME-5)
    _writeACommand("R" + std::to_string(13));
    _writeCCommand("A", "M-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("D", "M", "");
    _writeDSetR(14);

    // *ARG = pop()
    _writePopStackAndSetA();
    _writeCCommand("D", "M", "");
    _writeACommand("ARG");
    _writeCCommand("A", "M", "");
    _writeCCommand("M", "D", "");

    // SP = ARG+1
    _writeACommand("ARG");
    _writeCCommand("D", "M+1", "");
    _writeACommand("SP");
    _writeCCommand("M", "D", "");

    // THAT = *(FRAME-1)
    _writeACommand("R" + std::to_string(13));
    _writeCCommand("A", "M-1", "");
    _writeCCommand("D", "M", "");
    _writeACommand("THAT");
    _writeCCommand("M", "D", "");

    // THIS = *(FRAME-2)
    _writeACommand("R" + std::to_string(13));
    _writeCCommand("A", "M-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("D", "M", "");
    _writeACommand("THIS");
    _writeCCommand("M", "D", "");

    // ARG = *(FRAME-3)
    _writeACommand("R" + std::to_string(13));
    _writeCCommand("A", "M-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("D", "M", "");
    _writeACommand("ARG");
    _writeCCommand("M", "D", "");

    // LCL = *(FRAME-4)
    _writeACommand("R" + std::to_string(13));
    _writeCCommand("A", "M-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("A", "A-1", "");
    _writeCCommand("D", "M", "");
    _writeACommand("LCL");
    _writeCCommand("M", "D", "");

    // goto RET
    _writeACommand("R" + std::to_string(14));
    _writeCCommand("A", "M", "");
    _writeCCommand("", "0", "JMP");
}


void CodeWriter::writeCall(std::string functionName, int numArgs)
{
    std::string returnAddress = _makeReturnAddress();

    _writeACommand(returnAddress);
    _writeCCommand("D", "A", "");
    _writeDPush();
    _writeACommand("LCL");
    _writeCCommand("D", "M", "");
    _writeDPush();
    _writeACommand("ARG");
    _writeCCommand("D", "M", "");
    _writeDPush();
    _writeACommand("THIS");
    _writeCCommand("D", "M", "");
    _writeDPush();
    _writeACommand("THAT");
    _writeCCommand("D", "M", "");
    _writeDPush();

    // ARG = SP-n-5
    _writeACommand("SP");
    _writeCCommand("D", "M-1", "");
    for (int i = 0; i < 3 + numArgs; ++i)
        _writeCCommand("D", "D-1", "");
    _writeACommand("ARG");
    _writeCCommand("M", "D-1", "");

    // LCL = SP
    _writeACommand("SP");
    _writeCCommand("D", "M", "");
    _writeACommand("LCL");
    _writeCCommand("M", "D", "");

    // goto f
    _writeACommand(functionName);
    _writeCCommand("", "0", "JMP");

    _writeLabel(returnAddress);
}


void CodeWriter::writeInit()
{
    _writeACommand(256);
    _writeCCommand("D", "A", "");
    _writeACommand("SP");
    _writeCCommand("M", "D", "");
    writeCall("Sys.init", 0);
}
