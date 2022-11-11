#include "../inc/JackTokenizer.hpp"

JackTokenizer::JackTokenizer(std::string filePath)
    : _ifs(filePath)
{
    if (!_ifs) {
        std::cerr << "Could not open file" << std::endl;
        std::exit(1);
    }
}


bool JackTokenizer::hasMoreTokens()
{
    return !_restStr.empty() || !_ifs.eof();
}


std::string JackTokenizer::_ltrim(std::string s)
{
    const std::string space = " \n\r\t\f\v";
    std::size_t start = s.find_first_not_of(space);
    return (start == std::string::npos) ? "" : s.substr(start);
}


std::string JackTokenizer::_rtrim(std::string s)
{
    const std::string space = " \n\r\t\f\v";
    size_t end = s.find_last_not_of(space);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}


std::string JackTokenizer::_trim(std::string s)
{
    return _rtrim(_ltrim(s));
}


std::string JackTokenizer::_eraseCommentBegin(std::string s)
{
    std::size_t pos = s.find("//");
    if (pos != std::string::npos) {
        s.erase(s.begin() + pos, s.end());
    }
    return s;
}


std::string JackTokenizer::_eraseCommentBetween(std::string s, std::string begin,
                                                std::string end)
{
    std::size_t pos1 = s.find(begin);
    if (pos1 == std::string::npos) {
        return s;
    }
    std::size_t pos2 = s.find(end);
    s.erase(s.begin() + pos1, s.begin() + pos2 + 2);
    s.insert(s.begin() + pos1, ' ');
    return s;
}


std::string JackTokenizer::_eraseComment(std::string s)
{
    s = _eraseCommentBetween(s, "/*", "*/");
    s = _eraseCommentBegin(s);
    return s;
}


bool JackTokenizer::advance()
{
    std::string s;
    while (!_ifs.eof() && s.empty()) {
        // WIP error check
        std::getline(_ifs, s);
        s = _eraseComment(s);
        s = _trim(s);
    }
    std::cout << s << std::endl;
    return !s.empty();
}
