#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
#include <vector>

/**
 * @struct AttendanceRecord
 * @brief Represents a single attendance entry for a user.
 */
struct AttendanceRecord {
    std::string username; /**< Username of the student or employee. */
    std::string date;     /**< Date of the attendance record (format: YYYY-MM-DD). */
    bool present;         /**< True if the user was present, false otherwise. */
};

/**
 * @class AttendanceManager
 * @brief Manages attendance records and provides operations for marking and viewing attendance.
 * 
 * This class interacts with a database (or storage) to record and retrieve
 * attendance information based on user role.
 */
class AttendanceManager {
    std::string dbPath; /**< Path to the attendance database file. */

public:
    /**
     * @brief Constructs an AttendanceManager with the given database path.
     * @param path Path to the database file.
     */
    AttendanceManager(const std::string& path) : dbPath(path) {}

    /**
     * @brief Marks attendance for a specific user on a specific date.
     * @param username The username of the user.
     * @param date The date for which attendance is being marked.
     * @param present True if the user is present, false otherwise.
     * @param role Role of the user performing the operation (e.g., admin or user).
     * @return True if attendance was successfully marked, false otherwise.
     */
    bool markAttendance(const std::string& username, const std::string& date, bool present, const std::string& role);

    /**
     * @brief Retrieves attendance records.
     * @param role Role of the user requesting the records (e.g., admin or user).
     * @param username Username of the user whose attendance is being viewed. 
     *                 For admins, this may allow viewing all records.
     * @return A vector of AttendanceRecord containing the requested attendance data.
     */
    std::vector<AttendanceRecord> viewAttendance(const std::string& role, const std::string& username);

    /**
     * @brief Validates if a given date string is in the correct format (YYYY-MM-DD).
     * @param date The date string to validate.
     * @return True if the date is valid, false otherwise.
     */
    bool isValidDate(const std::string& date);
};

#endif
