# Mini Key-Value Database Engine (C++)

A lightweight in-memory key-value database engine written in C++.

This project explores how modern databases work internally by implementing
core features such as in-memory storage, Write-Ahead Logging (WAL),
snapshot persistence, and crash recovery.

---

## Features

- In-memory key-value storage using `unordered_map`
- O(1) average read/write operations
- Command Line Interface (CLI)
- Snapshot persistence (save database state to disk)
- Write-Ahead Logging (WAL) for durability
- Crash recovery using snapshot + WAL replay
- Modular architecture (Database / WAL / Snapshot)

---

## Supported Commands

| Command | Description |
|--------|-------------|
| SET key value | Insert or update a key-value pair |
| GET key | Retrieve value for a key |
| DEL key | Delete a key from the database |
| KEYS | List all keys stored in the database |
| CLEAR | Remove all keys from the database |
| SAVE | Save current database state to disk |
| LOAD | Load database snapshot from disk |
| EXIT | Exit the database program |
---
## Example Usage
```
>> SET name Tarpan
OK
>> GET name
Tarpan
>> KEYS
name
>> SAVE
Database saved.
>> EXIT
```
---
## Project Architecture
```
User CLI
   ↓
Command Parser
   ↓
Database (unordered_map)
   ↓
Persistence Layer
   ├── WAL Logger
   └── Snapshot System
```
---
## Project Structure
```
mini-kv-database
│
├── src/
│   ├── main.cpp
│   ├── Database.cpp
│   ├── Snapshot.cpp
│   └── WAL.cpp
│
├── include/
│   ├── Database.h
│   ├── Snapshot.h
│   └── WAL.h
│
├── data/
│   └── database.db
│
├── log/
│   └── commands.log
│
├── docs/
│
└── tests/
```
---
## How It Works
### Write Operation
When a command like:
```
SET name Tarpan
```
is executed:

1. The command is first written to the WAL log
2. The database is updated in memory
3. A snapshot can later persist the database state to disk
---
### Crash Recovery

When the database starts:
1. Snapshot file is loaded
2. WAL log is replayed
3. Database state is restored
---
## Build and Run

Compile:
```
g++ src/*.cpp -Iinclude -o kvdb
```
Run:
```
./kvdb
```
---
## Future Improvements
Planned features:

- CommandParser module
- TTL (key expiration)
- LRU eviction policy
- Background snapshot thread
- WAL compaction
- Statistics commands
---
## Learning Goals
This project helps understand:

- Database internals
- Storage engine design
- Persistence mechanisms
- Logging and recovery systems
