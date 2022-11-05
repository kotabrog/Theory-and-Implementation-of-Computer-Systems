#include "../inc/Code.hpp"

std::bitset<3> Code::dest(std::string s)
{
    _dest.reset();
    if (s.find('M') != std::string::npos)
        _dest.set(0);
    if (s.find('D') != std::string::npos)
        _dest.set(1);
    if (s.find('A') != std::string::npos)
        _dest.set(2);
    return _dest;
}


std::bitset<7> Code::comp(std::string s)
{
    _comp.reset();
    // WIP Poor searchability
    if (s == "0")
        _comp = std::bitset<7>("0101010");
    else if (s == "1")
        _comp = std::bitset<7>("0111111");
    else if (s == "-1")
        _comp = std::bitset<7>("0111010");
    else if (s == "D")
        _comp = std::bitset<7>("0001100");
    else if (s == "A")
        _comp = std::bitset<7>("0110000");
    else if (s == "!D")
        _comp = std::bitset<7>("0001101");
    else if (s == "!A")
        _comp = std::bitset<7>("0110001");
    else if (s == "-D")
        _comp = std::bitset<7>("0001111");
    else if (s == "-A")
        _comp = std::bitset<7>("0110011");
    else if (s == "D+1")
        _comp = std::bitset<7>("0011111");
    else if (s == "A+1")
        _comp = std::bitset<7>("0110111");
    else if (s == "D-1")
        _comp = std::bitset<7>("0001110");
    else if (s == "A-1")
        _comp = std::bitset<7>("0110010");
    else if (s == "D+A" || s == "A+D")
        _comp = std::bitset<7>("0000010");
    else if (s == "D-A")
        _comp = std::bitset<7>("0010011");
    else if (s == "A-D")
        _comp = std::bitset<7>("0000111");
    else if (s == "D&A" || s == "A&D")
        _comp = std::bitset<7>("0000000");
    else if (s == "D|A" || s == "A|D")
        _comp = std::bitset<7>("0010101");
    else if (s == "M")
        _comp = std::bitset<7>("1110000");
    else if (s == "!M")
        _comp = std::bitset<7>("1110001");
    else if (s == "-M")
        _comp = std::bitset<7>("1110011");
    else if (s == "M+1")
        _comp = std::bitset<7>("1110111");
    else if (s == "M-1")
        _comp = std::bitset<7>("1110010");
    else if (s == "D+M" || s == "M+D")
        _comp = std::bitset<7>("1000010");
    else if (s == "D-M")
        _comp = std::bitset<7>("1010011");
    else if (s == "M-D")
        _comp = std::bitset<7>("1000111");
    else if (s == "D&M" || s == "M&D")
        _comp = std::bitset<7>("1000000");
    else if (s == "D|M" || s == "M|D")
        _comp = std::bitset<7>("1010101");
    return _comp;
}


std::bitset<3> Code::jump(std::string s)
{
    _jump.reset();
    if (s == "JGT")
        _jump = std::bitset<3>("001");
    else if (s == "JEQ")
        _jump = std::bitset<3>("010");
    else if (s == "JGE")
        _jump = std::bitset<3>("011");
    else if (s == "JLT")
        _jump = std::bitset<3>("100");
    else if (s == "JNE")
        _jump = std::bitset<3>("101");
    else if (s == "JLE")
        _jump = std::bitset<3>("110");
    else if (s == "JMP")
        _jump = std::bitset<3>("111");
    return _jump;
}
