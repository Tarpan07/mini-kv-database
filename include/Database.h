#pragma once
#include <string>
#include <unordered_map>

class Database
{
private:
    std::unordered_map<std::string, std::string> db;
    std::unordered_map<std::string,time_t> expiry;

public:
    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key);
    bool del(const std::string &key);

    void setExpiry(const std::string &key, int seconds);
    bool isExpired(const std::string &key);

    void cleanupExpiredKeys();
    
    std::unordered_map<std::string, std::string>& getAll();
};