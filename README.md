# Mini Key-Value Database Engine (C++)

A lightweight in-memory key-value database engine written in C++.

This project simulates the internal architecture of modern databases by implementing core components such as in-memory storage, Write-Ahead Logging (WAL), snapshot persistence, crash recovery, TTL (Time-To-Live), and LRU (Least Recently Used) eviction.

---

# Features

* In-memory key-value storage using `unordered_map`
* O(1) average read/write operations
* Command Line Interface (CLI)
* Modular architecture (Database, WAL, Snapshot, StorageEngine)
* Write-Ahead Logging (WAL)
* Snapshot-based persistence
* Crash recovery (Snapshot + WAL replay)
* TTL (key expiration)
* Automatic cleanup of expired keys
* LRU eviction (memory limit handling)
* Auto snapshot after fixed number of commands
* Manual SAVE and LOAD support

---

# Supported Commands

| Command       | Description                         |
| ------------- | ----------------------------------- |
| SET key value | Insert or update a key-value pair   |
| GET key       | Retrieve value for a key            |
| DEL key       | Delete a key                        |
| KEYS          | List all keys                       |
| CLEAR         | Remove all keys from memory         |
| SAVE          | Save snapshot to disk and clear WAL |
| LOAD          | Load snapshot from disk             |
| EXIT          | Exit database                       |

---

# Example Usage

```
>> SET name Tarpan
OK

>> GET name
Tarpan

>> SET a 1
>> SET b 2
>> SET c 3
>> SET d 4
>> SET e 5
>> SET f 6
[LRU Evicted] a

>> SAVE
Database saved and WAL cleared
```

---

# How It Works

## Write Operation

When executing:

```
SET key value
```

The system performs:

1. Command is written to WAL (Write-Ahead Log)
2. Data is updated in memory
3. LRU and TTL logic are applied

---

## Read Operation

```
GET key
```

* Checks if key is expired (TTL)
* Updates LRU usage
* Returns value if exists

---

## Persistence

### Snapshot

* Stores full database state in:

```
data/database.db
```

* Triggered by:

  * Manual `SAVE`
  * Auto snapshot (every N commands)

---

### Write-Ahead Log (WAL)

* Stores commands in:

```
logs/commands.log
```

* Ensures durability before applying changes

---

## Crash Recovery

On restart:

1. Snapshot is loaded
2. WAL is replayed
3. Database state is restored

---

## TTL (Time-To-Live)

* Keys can expire after a given time
* Expired keys are removed:

  * During access (lazy deletion)
  * During periodic cleanup

---

## LRU Eviction

* Database has limited capacity
* When full:

```
Least Recently Used key is removed
```

---

# Architecture

```
User CLI
   ↓
CommandParser
   ↓
StorageEngine
   ↓
Database (RAM)
   ├── TTL (expiry)
   ├── LRU (eviction)
   ↓
Persistence Layer
   ├── WAL (logs/commands.log)
   └── Snapshot (data/database.db)
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
└── tests/
```

---

# Build and Run

Compile:

```
g++ src/*.cpp -Iinclude -o kvdb -std=c++17
```

Run:

```
./kvdb
```

---

# Key Concepts Implemented

* In-memory database design
* Write-Ahead Logging (WAL)
* Snapshot persistence
* Crash recovery mechanisms
* TTL-based expiration
* LRU cache eviction
* Modular system design

---

# Limitations

* Single-threaded (no concurrency)
* No indexing or query optimization
* WAL compaction is basic
* Snapshot is full dump (not incremental)

---

# Future Improvements

* WAL compaction (log optimization)
* Background snapshot thread
* Background TTL cleanup thread
* INFO / DBSIZE commands
* Multi-threaded support
* Disk-based storage engine (LSM Tree)

---

# Learning Outcomes

This project demonstrates:

* Database internals
* Storage engine design
* Logging and recovery systems
* Memory management strategies
* System design thinking

---

# Author

Tarpan Saikia

---

# Note

This project is built for learning system design concepts and simulating real-world database internals similar to Redis.
