# Mini Key-Value Database Engine (C++)

A lightweight in-memory key-value database engine written in C++.

This project explores the internal architecture of modern databases by implementing
core components such as in-memory storage, Write-Ahead Logging (WAL), snapshot
persistence, crash recovery, and command parsing.

---

# Features

- In-memory key-value storage using `unordered_map`
- O(1) average read/write operations
- Command Line Interface (CLI)
- CommandParser for structured command parsing
- StorageEngine layer for command execution
- Snapshot persistence
- Write-Ahead Logging (WAL)
- Crash recovery using snapshot + WAL replay
- Modular architecture

---

# Supported Commands

| Command | Description |
|-------|-------------|
| SET key value | Insert or update a key-value pair |
| GET key | Retrieve value for a key |
| DEL key | Delete a key |
| KEYS | List all keys in the database |
| CLEAR | Remove all keys from memory |
| SAVE | Save database snapshot |
| LOAD | Load database snapshot |
| EXIT | Exit database |

---

# Example Usage

```
>> SET name Tarpan
OK

>> GET name
Tarpan

>> KEYS
name

>> SAVE
Database saved and WAL cleared
```

---

# How It Works

## Write Operation

When executing:

```
SET name Tarpan
```

The system performs the following steps:

1. The command is written to the WAL log
2. The database is updated in memory
3. A snapshot can later persist the state to disk

---

## Crash Recovery

When the database starts:

1. Snapshot is loaded from disk
2. WAL log is replayed
3. Database state is restored

This ensures durability even if the system crashes.

---

# Architecture

```
User CLI
   ↓
CommandParser
   ↓
StorageEngine
   ↓
Database (unordered_map)
   ↓
Persistence Layer
   ├── WAL Logger
   └── Snapshot System
```

### Component Responsibilities

**CLI (main.cpp)**  
Handles user input and interaction.

**CommandParser**  
Tokenizes user commands into structured arguments.

**StorageEngine**  
Coordinates command execution and interacts with the database and persistence layer.

**Database**  
Stores key-value pairs in memory using `unordered_map`.

**WAL (Write Ahead Log)**  
Logs write operations before execution for crash recovery.

**Snapshot System**  
Periodically saves the entire database state to disk.

---

# Project Structure

```
mini-kv-database
│
├── src/
│   ├── main.cpp
│   ├── Database.cpp
│   ├── Snapshot.cpp
│   ├── WAL.cpp
│   ├── CommandParser.cpp
│   └── StorageEngine.cpp
│
├── include/
│   ├── Database.h
│   ├── Snapshot.h
│   ├── WAL.h
│   ├── CommandParser.h
│   └── StorageEngine.h
│
├── data/
│   └── database.db
│
├── logs/
│   └── commands.log
│
├── docs/
│
└── tests/
```

---

# Build and Run

Compile:

```
g++ src/*.cpp -Iinclude -o kvdb
```

Run:

```
./kvdb
```

---

# Future Improvements

Planned features:

- TTL (key expiration)
- LRU eviction policy
- Background snapshot thread
- WAL compaction
- Statistics commands
- Performance improvements

---

# Learning Goals

This project helps understand:

- database internals
- storage engine design
- persistence mechanisms
- write-ahead logging
- crash recovery systems
- modular system architecture