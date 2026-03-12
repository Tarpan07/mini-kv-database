#include "../include/WAL.h"
#include <fstream>
#include <sstream>

void WAL::write(const std::string &command)
{
    std::ofstream log("logs/commands.log", std::ios::app);
    log << command << std::endl;
}

void WAL::recover(Database &database)
{
    std::ifstream log("logs/commands.log");

    if (!log)
        return;

    std::string line;

    while (getline(log, line))
    {
        std::stringstream ss(line);
        std::string cmd;

        ss >> cmd;

        if (cmd == "SET")
        {
            std::string key, value;
            ss >> key >> value;
            database.set(key, value);
        }
        else if (cmd == "DEL")
        {
            std::string key;
            ss >> key;
            database.del(key);
        }
    }
}