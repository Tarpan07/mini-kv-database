#include "../include/Snapshot.h"
#include <fstream>
#include <iostream>

void Snapshot::save(std::unordered_map<std::string,std::string> &db)
{
    std::ofstream file("data/database.db");   // ✅ same path

    for (auto &p : db)
    {
        file << p.first << " " << p.second << std::endl;
    }

    file.close();

    std::cout << "Database saved.\n";
}

bool Snapshot::load(std::unordered_map<std::string,std::string> &db)
{
    std::ifstream file("data/database.db");   // ✅ FIXED

    if (!file)
    {
        std::cout << "No database file found.\n";
        return false;
    }

    db.clear();

    std::string key, value;

    while (file >> key >> value)
    {
        db[key] = value;
    }

    file.close();

    return true;
}