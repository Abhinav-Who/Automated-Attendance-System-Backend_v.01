#include "app.h"
#include "db.h"
#include "user.h"
#include "image_verifier.h"
#include "attendance.h"

#include <iostream>
#include <ctime>

using namespace std;

// Get current date in YYYY-MM-DD
static string currentDate() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", now);
    return string(buf);
}

void App::run() {
    createDBIfNotExists(dbPath);
    createUsersTable(dbPath);
    createAttendanceTable(dbPath);

    UserManager userMgr(dbPath);
    AttendanceManager attMgr(dbPath);

    // Ensure default admin exists
    userMgr.addUser("admin", "admin123", "admin", "images/admin.jpg");

    // LOGIN
    string username, password, role;
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    if (!userMgr.login(username, password, role)) {
        cerr << "Invalid login!" << endl;
        return;
    }
    cout << "Login successful! Role: " << role << "\n";

    // ADMIN: Add new users
    if (role == "admin") {
        cout << "Add new user? (y/n): ";
        char choice; cin >> choice;
        if (choice == 'y') {
            string u, p, r, imgPath;
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;
            cout << "Role: "; cin >> r;
            cout << "Path to reference image: "; cin >> imgPath;
            userMgr.addUser(u, p, r, imgPath);
        }

        // Admin override attendance
        cout << "Do you want to mark/overwrite attendance for any user? (y/n): ";
        char c; cin >> c;
        if (c == 'y') {
            string targetUser, date;
            cout << "Enter username: "; cin >> targetUser;
            cout << "Enter date (YYYY-MM-DD) or 'n' for today: "; cin >> date;
            if (date == "n") date = currentDate();

            cout << "Is present? (1=Yes, 0=No): ";
            int p; cin >> p;
            bool present = (p == 1);

            if (attMgr.markAttendance(targetUser, date, present, role)) {
                cout << "Attendance marked/overwritten for " << targetUser << " on " << date << ".\n";
            } else {
                cout << "Failed to mark/overwrite attendance.\n";
            }
        }
    }

    // NON-ADMIN: Image verification and attendance
    if (role != "admin") {
        ImageVerifier verifier(dbPath);
        string userImg;
        cout << "Enter path of image to compare: ";
        cin >> userImg;

        double match = verifier.compareWithUserImage(username, userImg);
        cout << "Match Percentage: " << match << "%\n";

        if (match >= 80.0) {
            string date;
            cout << "Enter date (YYYY-MM-DD) or 'n' for today: ";
            cin >> date;
            if (date == "n") date = currentDate();

            if (!attMgr.isValidDate(date)) {
                cerr << "Invalid or future date. Attendance not marked.\n";
            } else {
                if (attMgr.markAttendance(username, date, true, role)) {
                    cout << "Attendance marked for " << username << " on " << date << ".\n";
                } else {
                    cout << "Attendance not marked (already exists or error).\n";
                }
            }
        } else {
            cout << "Image verification failed. Attendance not marked.\n";
        }
    }

    // ATTENDANCE VIEW
    cout << "View attendance? (y/n): ";
    char viewChoice; cin >> viewChoice;
    if (viewChoice == 'y') {
        string viewUser = username; // default for non-admin
        if (role == "admin") {
            cout << "Enter username to view attendance: ";
            cin >> viewUser;
        }

        auto recs = attMgr.viewAttendance(role, viewUser);

        cout << "\n+----------------+------------+---------+\n";
        cout << "| Username       | Date       | Present |\n";
        cout << "+----------------+------------+---------+\n";
        for (auto& r : recs) {
            printf("| %-14s | %-10s | %-7s |\n",
                   r.username.c_str(),
                   r.date.c_str(),
                   r.present ? "Yes" : "No");
        }
        cout << "+----------------+------------+---------+\n";
    }
}

// MAIN ENTRY
int main() {
    App app("images.db");
    app.run();
    return 0;
}
