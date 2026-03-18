#include "../include/Database.h"
#include <ctime>
#include <iostream>


void Database::set(const std::string &key, const std::string &value)
{
    // if key already exists → update position
    if (db.find(key) != db.end())
    {
        if (lruMap.find(key) != lruMap.end())
        {
            lruList.erase(lruMap[key]);
        }
    }
    else if (!isRecovering && db.size() >= capacity && !lruList.empty())
    {
        // remove least recently used safely
        std::string lruKey = lruList.back();
        lruList.pop_back();

        db.erase(lruKey);
        expiry.erase(lruKey);
        lruMap.erase(lruKey);

        std::cout << "[LRU Evicted] " << lruKey << "\n";
    }

    db[key] = value;

    // insert as most recently used
    lruList.push_front(key);
    lruMap[key] = lruList.begin();
}

void Database::setExpiry(const std::string &key, int seconds)
{
    expiry[key] = time(nullptr) + seconds;
}

bool Database::isExpired(const std::string &key)
{
    if (expiry.find(key) == expiry.end())
        return false;

    if (time(nullptr) > expiry[key])
    {
        db.erase(key);

        if (lruMap.find(key) != lruMap.end())
        {
            lruList.erase(lruMap[key]);
            lruMap.erase(key);
        }

        expiry.erase(key);
        return true;
    }

    return false;
}

std::string Database::get(const std::string &key)
{
    if (isExpired(key))
        return "Key not found";

    if (db.find(key) == db.end())
        return "Key not found";

    // update LRU safely
    if (lruMap.find(key) != lruMap.end())
    {
        lruList.erase(lruMap[key]);
    }

    lruList.push_front(key);
    lruMap[key] = lruList.begin();

    return db[key];
}

bool Database::del(const std::string &key)
{
    expiry.erase(key);

    if (lruMap.find(key) != lruMap.end())
    {
        lruList.erase(lruMap[key]);
        lruMap.erase(key);
    }

    return db.erase(key);
}

std::unordered_map<std::string, std::string> &Database::getAll()
{
    return db;
}

void Database::cleanupExpiredKeys()
{
    time_t now = time(nullptr);

    for (auto it = expiry.begin(); it != expiry.end();)
    {
        if (now > it->second)
        {
            std::string key = it->first;

            db.erase(key);

            if (lruMap.find(key) != lruMap.end())
            {
                lruList.erase(lruMap[key]);
                lruMap.erase(key);
            }

            it = expiry.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Database::startRecovery()
{
    isRecovering = true;
}

void Database::endRecovery()
{
    isRecovering = false;
}