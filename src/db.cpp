#include "db.h"
#include <sqlite3.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

// Utility to check if file exists
static bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void createDBIfNotExists(const std::string& dbPath) {
    if (!fileExists(dbPath)) {
        cout << "Database file not found. Creating new DB at: " << dbPath << endl;
        sqlite3* db;
        if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
            cerr << "Failed to create DB: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return;
        }
        sqlite3_close(db);
    }
}

void createUsersTable(const std::string& dbPath) {
    sqlite3* db;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Error opening DB for users table: " << sqlite3_errmsg(db) << endl;
        return;
    }
    const char* sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "username TEXT PRIMARY KEY, "
        "password TEXT NOT NULL, "
        "role TEXT NOT NULL, "
        "image BLOB"
        ");";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Error creating users table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);
}

void createAttendanceTable(const std::string& dbPath) {
    sqlite3* db;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Error opening DB for attendance table: " << sqlite3_errmsg(db) << endl;
        return;
    }
    const char* sql =
        "CREATE TABLE IF NOT EXISTS attendance ("
        "username TEXT, "
        "date TEXT, "
        "present INTEGER, "
        "PRIMARY KEY(username, date)"
        ");";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Error creating attendance table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);
}
