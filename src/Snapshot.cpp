#include "../include/Snapshot.h"
#include <fstream>
#include <iostream>

void Snapshot::save(std::unordered_map<std::string,std::string> &db)
{
    std::ofstream file("../data/database.db");

    for (auto &p : db)
    {
        file << p.first << " " << p.second << std::endl;
    }

    file.close();

    std::cout << "Database saved.\n";
}

void Snapshot::load(std::unordered_map<std::string,std::string> &db)
{
    std::ifstream file("../data/database.db");

    if (!file)
    {
        std::cout << "No database file found.\n";
        return;
    }

    db.clear();   // important

    std::string key, value;

    while (file >> key >> value)
    {
        db[key] = value;
    }

    file.close();

    std::cout << "Database loaded.\n";
}