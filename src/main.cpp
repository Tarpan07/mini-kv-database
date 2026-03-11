#include <iostream>
#include <sstream>
#include <fstream>

#include "../include/Database.h"
#include "../include/WAL.h"
#include "../include/Snapshot.h"
#include "../include/CommandParser.h"

using namespace std;

int main()
{
    Database db;

    Snapshot::load(db.getAll());
    WAL::recover(db);

    string line;

    cout << "Mini Database Started\n";

    while (true)
    {
        cout << ">> " << flush;

        getline(cin, line);

        if (line.find_first_not_of(' ') == string::npos)
            continue;

        auto tokens = CommandParser::parse(line);

        if (tokens.empty())
            continue;

        string command = tokens[0];

        if (command == "SET")
        {
            if (tokens.size() < 3)
            {
                cout << "Usage: SET key value\n";
                continue;
            }
            string key = tokens[1];
            string value = tokens[2];

            WAL::write(line);
            db.set(key, value);

            cout << "OK\n";
        }

        else if (command == "GET")
        {
            string key = tokens[1];

            cout << db.get(key) << endl;
        }

        else if (command == "DEL")
        {
            string key = tokens[1];

            WAL::write(line);

            if (db.del(key))
                cout << "Deleted\n";
            else
                cout << "Key not found\n";
        }

        else if (command == "SAVE")
        {
            Snapshot::save(db.getAll());
            ofstream walFile("../log/commands.log", ios::trunc);
            walFile.close();

            cout << "Database saved and WAL cleared\n";
        }

        else if (command == "LOAD")
        {
            Snapshot::load(db.getAll());
            cout << "Database loaded\n";
        }

        else if (command == "EXIT")
        {
            break;
        }
        else if (command == "KEYS")
        {
            auto &data = db.getAll();

            if (data.empty())
            {
                cout << "Database empty\n";
                continue;
            }

            for (auto &p : data)
            {
                cout << p.first << endl;
            }
        }
        else if (command == "CLEAR")
        {
            db.getAll().clear();

            ofstream walFile("../log/commands.log", ios::trunc);
            walFile.close();

            cout << "Database cleared\n";
        }

        else
        {
            cout << "Unknown command\n";
        }
    }

    return 0;
}