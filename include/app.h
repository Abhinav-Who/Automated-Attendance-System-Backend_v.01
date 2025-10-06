#ifndef APP_H
#define APP_H

#include <string>

/**
 * @class App
 * @brief Represents the main application that interacts with a database.
 * 
 * The App class stores the path to a database and provides
 * a method to run the application.
 */
class App {
    std::string dbPath; /**< Path to the database file. */

public:
    /**
     * @brief Constructs an App with the specified database path.
     * @param db The path to the database file.
     */
    App(const std::string& db) : dbPath(db) {}

    /**
     * @brief Starts the application.
     * 
     * This function contains the main logic to run the application.
     */
    void run();
};

#endif
