#include "../include/StorageEngine.h"
#include "../include/WAL.h"
#include "../include/Snapshot.h"

#include <iostream>
#include <fstream>

using namespace std;

StorageEngine::StorageEngine(Database &database) : db(database) {}

void StorageEngine::execute(const vector<string> &tokens, const string &rawCommand)
{
    if (tokens.empty())
        return;

    string command = tokens[0];

    if (command == "SET")
    {
        if (tokens.size() < 3)
        {
            cout << "Usage: SET key value\n";
            return;
        }

        string key = tokens[1];
        string value = tokens[2];

        WAL::write(rawCommand);
        db.set(key, value);
        if (tokens.size() == 5 && tokens[3] == "EX")
        {
            int seconds = stoi(tokens[4]);
            db.setExpiry(key, seconds);
        }

        cout << "OK\n";
    }

    else if (command == "GET")
    {
        if (tokens.size() < 2)
        {
            cout << "Usage: GET key\n";
            return;
        }

        cout << db.get(tokens[1]) << endl;
    }

    else if (command == "DEL")
    {
        if (tokens.size() < 2)
        {
            cout << "Usage: DEL key\n";
            return;
        }

        WAL::write(rawCommand);

        if (db.del(tokens[1]))
            cout << "Deleted\n";
        else
            cout << "Key not found\n";
    }

    else if (command == "SAVE")
    {
        Snapshot::save(db.getAll());

        ofstream walFile("logs/commands.log", ios::trunc);
        walFile.close();

        cout << "Database saved and WAL cleared\n";
    }

    else if (command == "LOAD")
    {
        if (Snapshot::load(db.getAll()))
            cout << "Database loaded\n";
    }
    else if (command == "KEYS")
    {
        auto &data = db.getAll();

        if (data.empty())
        {
            cout << "Database empty\n";
            return;
        }

        for (auto &p : data)
            cout << p.first << endl;
    }

    else if (command == "CLEAR")
    {
        db.getAll().clear();

        ofstream walFile("logs/commands.log", ios::trunc);
        walFile.close();
        remove("data/database.db");

        cout << "Database cleared\n";
    }

    else if (command == "EXIT")
    {
        exit(0);
    }

    else
    {
        cout << "Unknown command\n";
    }
}