#pragma once
#include <string>
#include <unordered_map>
#include <list>
#include <ctime>

class Database
{
private:
    // main storage
    std::unordered_map<std::string, std::string> db;

    // TTL storage
    std::unordered_map<std::string, time_t> expiry;
    // LRU structures
    std::list<std::string> lruList; // front = most recent
    std::unordered_map<std::string, std::list<std::string>::iterator> lruMap;

    size_t capacity = 5; // max keys allowed
    bool isRecovering = false;

public:
    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key);
    bool del(const std::string &key);

    void setExpiry(const std::string &key, int seconds);
    bool isExpired(const std::string &key);

    void cleanupExpiredKeys();

    void startRecovery();
    void endRecovery();


    std::unordered_map<std::string, std::string> &getAll();
};