#pragma once
#include <string>
#include "Database.h"

class WAL
{
public:
    static void write(const std::string &command);
    static void recover(Database &db);
};