#include "attendance.h"
#include <sqlite3.h>
#include <iostream>
#include <regex>
#include <ctime>

using namespace std;

// Check valid YYYY-MM-DD and no future date
bool AttendanceManager::isValidDate(const std::string& date) {
    regex pattern(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(date, pattern)) return false;

    int y, m, d;
    sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d);

    if (m < 1 || m > 12 || d < 1 || d > 31) return false;

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int cy = now->tm_year + 1900;
    int cm = now->tm_mon + 1;
    int cd = now->tm_mday;

    // Reject future dates
    if (y > cy || (y == cy && (m > cm || (m == cm && d > cd)))) return false;

    return true;
}

bool AttendanceManager::markAttendance(const std::string& username, const std::string& date, bool present, const std::string& role) {
    if (!isValidDate(date)) {
        cerr << "Invalid or future date: " << date << endl;
        return false;
    }

    sqlite3* db = nullptr;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Failed to open DB: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    const char* selectSQL = "SELECT present FROM attendance WHERE username=? AND date=?;";
    sqlite3_stmt* selectStmt = nullptr;
    bool exists = false;
    int currentPresent = 0;

    if (sqlite3_prepare_v2(db, selectSQL, -1, &selectStmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(selectStmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(selectStmt, 2, date.c_str(), -1, SQLITE_STATIC);
        int rc = sqlite3_step(selectStmt);
        if (rc == SQLITE_ROW) {
            exists = true;
            currentPresent = sqlite3_column_int(selectStmt, 0);
        }
    }
    sqlite3_finalize(selectStmt);

    if (exists && role != "admin") {
        cout << "Attendance already marked for " << username << " on " << date << ".\n";
        cout << "Current status: " << (currentPresent ? "Present" : "Absent") << ". Only admin can overwrite.\n";
        sqlite3_close(db);
        return false;
    }

    const char* sql = exists
        ? "UPDATE attendance SET present=? WHERE username=? AND date=?;"
        : "INSERT INTO attendance(username,date,present) VALUES(?,?,?);";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    if (exists) {
        sqlite3_bind_int(stmt, 1, present ? 1 : 0);
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, date.c_str(), -1, SQLITE_STATIC);
    } else {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, date.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, present ? 1 : 0);
    }

    int rc = sqlite3_step(stmt);
    bool ok = (rc == SQLITE_DONE);
    if (!ok) cerr << "Failed to insert/update attendance: " << sqlite3_errmsg(db) << endl;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return ok;
}

vector<AttendanceRecord> AttendanceManager::viewAttendance(const std::string& role, const std::string& username) {
    vector<AttendanceRecord> records;
    sqlite3* db = nullptr;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Failed to open DB: " << sqlite3_errmsg(db) << endl;
        return records;
    }

    bool bindUsername = false;
    string sql = "SELECT username, date, present FROM attendance";

    if (role == "admin") {
        if (!username.empty()) { sql += " WHERE username=?"; bindUsername = true; }
    } else if (role == "teacher") {
        if (!username.empty()) { sql += " WHERE username=?"; bindUsername = true; }
    } else {
        sql += " WHERE username=?"; bindUsername = true;
    }

    sql += " ORDER BY date DESC;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare select: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return records;
    }

    if (bindUsername) sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        AttendanceRecord rec;
        rec.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        rec.date     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        rec.present  = sqlite3_column_int(stmt, 2) != 0;
        records.push_back(rec);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return records;
}
