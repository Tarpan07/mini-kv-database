#include <iostream>
#include <sstream>
#include <fstream>

#include "../include/Database.h"
#include "../include/WAL.h"
#include "../include/Snapshot.h"

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

        stringstream ss(line);
        string command;

        ss >> command;

        if (command == "SET")
        {
            string key, value;
            ss >> key >> value;

            WAL::write(line);
            db.set(key, value);

            cout << "OK\n";
        }

        else if (command == "GET")
        {
            string key;
            ss >> key;

            cout << db.get(key) << endl;
        }

        else if (command == "DEL")
        {
            string key;
            ss >> key;

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