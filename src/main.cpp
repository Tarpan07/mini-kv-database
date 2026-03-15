#include <iostream>
#include <string>

#include "../include/Database.h"
#include "../include/Snapshot.h"
#include "../include/WAL.h"
#include "../include/CommandParser.h"
#include "../include/StorageEngine.h"
using namespace std;


int main()
{
    Database db;

    Snapshot::load(db.getAll());
    WAL::recover(db);

    StorageEngine engine(db);

    string line;
    int commandCount = 0;
    cout << "Mini Database Started\n";

    while (true)
    {
        cout << ">> " << flush;

        getline(cin, line);

        if (line.empty())
            continue;

        auto tokens = CommandParser::parse(line);

        engine.execute(tokens, line);
        commandCount++;

        if (commandCount % 5 == 0)
        {
            Snapshot::save(db.getAll());
            cout << "[Auto Snapshot Saved]\n";
        }
    }
}