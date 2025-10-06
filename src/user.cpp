#include "user.h"
#include <sqlite3.h>
#include <fstream>
#include <iostream>

using namespace std;

bool UserManager::addUser(const string& username, const string& password, const string& role, const string& imagePath) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);

    // check if user exists
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT username FROM users WHERE username=?;", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc == SQLITE_ROW) {
        cerr << "Warning: User '" << username << "' already exists!\n";
        sqlite3_close(db);
        return false;
    }

    // read image as binary
    ifstream file(imagePath, ios::binary);
    vector<unsigned char> buffer((istreambuf_iterator<char>(file)), {});
    file.close();

    sqlite3_prepare_v2(db, "INSERT INTO users(username,password,role,image) VALUES(?,?,?,?);", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, role.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 4, buffer.data(), (int)buffer.size(), SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}

bool UserManager::login(const string& username, const string& password, string& role) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "SELECT role FROM users WHERE username=? AND password=?;", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        role = (const char*)sqlite3_column_text(stmt, 0);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return true;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return false;
}

vector<unsigned char> UserManager::getUserImage(const string& username) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    vector<unsigned char> data;
    sqlite3_prepare_v2(db, "SELECT image FROM users WHERE username=?;", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const void* blob = sqlite3_column_blob(stmt, 0);
        int size = sqlite3_column_bytes(stmt, 0);
        data.assign((unsigned char*)blob, (unsigned char*)blob + size);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return data;
}
