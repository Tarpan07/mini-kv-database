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
| CLEAR | Remove all keys |
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

The system performs:

1. Command is written to WAL
2. Database is updated in memory
3. Snapshot can persist the state to disk

---

## Crash Recovery

When the database starts:

1. Snapshot is loaded
2. WAL log is replayed
3. Database state is restored

---

# Architecture

```
User CLI
   ↓
CommandParser
   ↓
Command Execution (main.cpp)
   ↓
Database (unordered_map)
   ↓
Persistence Layer
   ├── WAL Logger
   └── Snapshot System
```

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
│   └── CommandParser.cpp
│
├── include/
│   ├── Database.h
│   ├── Snapshot.h
│   ├── WAL.h
│   └── CommandParser.h
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

- StorageEngine layer
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
- logging systems
- persistence mechanisms
- crash recovery