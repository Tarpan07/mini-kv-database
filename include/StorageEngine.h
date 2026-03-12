#ifndef STORAGEENGINE_H
#define STORAGEENGINE_H

#include <vector>
#include <string>
#include "Database.h"

class StorageEngine
{
private:
    Database &db;

public:
    StorageEngine(Database &database);

    void execute(const std::vector<std::string> &tokens, const std::string &rawCommand);
};

#endif