#ifndef IMAGE_VERIFIER_H
#define IMAGE_VERIFIER_H

#include <string>

/**
 * @class ImageVerifier
 * @brief Provides functionality to verify user images by comparing them with stored images.
 * 
 * The ImageVerifier class interacts with a database to fetch stored images
 * and compare them with user-provided images, returning a similarity score.
 */
class ImageVerifier {
    std::string dbPath; /**< Path to the database file containing user images. */

public:
    /**
     * @brief Constructs an ImageVerifier with the specified database path.
     * @param path Path to the database containing user images.
     */
    ImageVerifier(const std::string& path) : dbPath(path) {}

    /**
     * @brief Compares a user-provided image with the stored image of the specified username.
     * @param username The username whose stored image will be used for comparison.
     * @param userImgPath Path to the user-provided image file.
     * @return A similarity score as a double, typically representing a percentage or confidence level.
     */
    double compareWithUserImage(const std::string& username, const std::string& userImgPath);
};

#endif
