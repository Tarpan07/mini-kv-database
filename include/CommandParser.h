#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <vector>

class CommandParser
{
public:
    static std::vector<std::string> parse(const std::string &input);
};

#endif