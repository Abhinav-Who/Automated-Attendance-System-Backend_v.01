#ifndef DB_H
#define DB_H

#include <string>

/**
 * @file db.h
 * @brief Provides functions for database creation and table setup.
 */

/**
 * @brief Creates the database file if it does not already exist.
 * 
 * @param dbPath Path to the database file to create.
 */
void createDBIfNotExists(const std::string& dbPath);

/**
 * @brief Creates the 'users' table in the database.
 * 
 * @param dbPath Path to the database file where the table should be created.
 */
void createUsersTable(const std::string& dbPath);

/**
 * @brief Creates the 'attendance' table in the database.
 * 
 * @param dbPath Path to the database file where the table should be created.
 */
void createAttendanceTable(const std::string& dbPath);

#endif
