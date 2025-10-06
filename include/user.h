#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

/**
 * @class UserManager
 * @brief Manages user accounts including creation, authentication, and image retrieval.
 * 
 * The UserManager class interacts with a database to add users, verify login credentials,
 * and fetch stored user images.
 */
class UserManager {
    std::string dbPath; /**< Path to the database file storing user information. */

public:
    /**
     * @brief Constructs a UserManager with the specified database path.
     * @param path Path to the database containing user information.
     */
    UserManager(const std::string& path) : dbPath(path) {}

    /**
     * @brief Adds a new user to the database.
     * @param username The username for the new user.
     * @param password The password for the new user.
     * @param role The role of the user (e.g., "admin" or "user").
     * @param imagePath Path to the user's profile image.
     * @return True if the user was successfully added, false otherwise.
     */
    bool addUser(const std::string& username, const std::string& password,
                 const std::string& role, const std::string& imagePath);

    /**
     * @brief Authenticates a user by verifying their username and password.
     * @param username The username of the user.
     * @param password The password provided for authentication.
     * @param role Output parameter to store the user's role if login is successful.
     * @return True if login is successful, false otherwise.
     */
    bool login(const std::string& username, const std::string& password, std::string& role);

    /**
     * @brief Retrieves the stored image of a user.
     * @param username The username whose image will be retrieved.
     * @return A vector of bytes representing the user's image.
     */
    std::vector<unsigned char> getUserImage(const std::string& username);
};

#endif
