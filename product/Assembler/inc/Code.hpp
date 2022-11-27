#ifndef CODE_HPP
#define CODE_HPP

#include <iostream>
#include <string>
#include <bitset>

class Code
{
private:
    std::bitset<3> _dest;
    std::bitset<7> _comp;
    std::bitset<3> _jump;

public:
    Code() : _dest(0), _comp(0), _jump(0) {}
    std::bitset<3> dest(std::string s);
    std::bitset<7> comp(std::string s);
    std::bitset<3> jump(std::string s);
};

#endif