#include "../inc/CodeWriter.hpp"

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
    if (!dest.empty())
        _ofs << ";" << jump;
    _ofs << std::endl;
}


void CodeWriter::_writeAdd()
{
    _writeACommand("SP");
    _writeCCommand("M", "M-1", "");
    _writeCCommand("A", "M", "");
    _writeCCommand("D", "M", "");
    _writeACommand("SP");
    _writeCCommand("M", "M-1", "");
    _writeCCommand("A", "M", "");
    _writeCCommand("M", "D+M", "");
    _writeACommand("SP");
    _writeCCommand("M", "M+1", "");
}


void CodeWriter::writeArithmetic(std::string command)
{
    if (command == "add")
        _writeAdd();
}


void CodeWriter::_writeConstantPush(int value)
{
    _writeACommand(value);
    _writeCCommand("D", "A", "");
    _writeACommand("SP");
    _writeCCommand("A", "M", "");
    _writeCCommand("M", "D", "");
    _writeACommand("SP");
    _writeCCommand("M", "M+1", "");
}


void CodeWriter::writePushPop(CommandType command, std::string segment, int index)
{
    if (command == CommandType::C_PUSH && segment == "constant")
        _writeConstantPush(index);
}
