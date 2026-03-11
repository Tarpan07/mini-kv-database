# Mini Key-Value Database Engine (C++)

A lightweight in-memory key-value database written in C++.

## Features

- SET / GET / DEL commands
- Snapshot persistence
- Write Ahead Logging (WAL)
- Crash recovery
- KEYS and CLEAR commands

## Build

g++ src/*.cpp -Iinclude -o kvdb

## Run

./kvdb