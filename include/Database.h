#pragma once
#include <string>
#include <unordered_map>

class Database
{
private:
    std::unordered_map<std::string, std::string> db;

public:
    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key);
    bool del(const std::string &key);

    std::unordered_map<std::string, std::string>& getAll();
};