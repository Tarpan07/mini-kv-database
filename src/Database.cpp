#include "../include/Database.h"
#include <ctime>

void Database::set(const std::string &key, const std::string &value)
{
    db[key] = value;
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

    return db[key];
}

bool Database::del(const std::string &key)
{
    expiry.erase(key);
    return db.erase(key);
}

std::unordered_map<std::string, std::string>& Database::getAll()
{
    return db;
}