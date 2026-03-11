#include "../include/Database.h"

void Database::set(const std::string &key, const std::string &value)
{
    db[key] = value;
}

std::string Database::get(const std::string &key)
{
    if (db.find(key) == db.end())
        return "Key not found";

    return db[key];
}

bool Database::del(const std::string &key)
{
    return db.erase(key);
}

std::unordered_map<std::string, std::string>& Database::getAll()
{
    return db;
}