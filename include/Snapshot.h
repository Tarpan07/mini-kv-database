#pragma once
#include <unordered_map>
#include <string>

class Snapshot
{
public:
    static void save(std::unordered_map<std::string,std::string> &db);
    static void load(std::unordered_map<std::string,std::string> &db);
};