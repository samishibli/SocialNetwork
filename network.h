#ifndef NETWORK_H
#define NETWORK_H

#include <cstddef>
#include <vector>
#include <string>
#include "user.h" // Include the necessary header file for User

class Network
{
public:
    // Default constructor
    // Pre: None
    // Post: Creates an empty Network object
    Network();

    // Destructor
    // Pre: None
    // Post: Cleans up allocated resources when the Network object is destroyed
    ~Network();

    // Add a User pointer to the network
    // Pre: userPointer is a valid pointer to a User object
    // Post: Adds the User to the network
    void addUser(User *userPointer);

    // Add a connection between two users in the network
    // Pre: s1 and s2 are valid user names in the network
    // Post: Adds a connection between the users if they exist, returns -1 if not
    int addConnection(std::string s1, std::string s2);

    // Remove a connection between two users in the network
    // Pre: s1 and s2 are valid user names in the network
    // Post: Removes the connection between the users if it exists, returns -1 if not
    int removeConnection(std::string s1, std::string s2);

    // Get the unique ID associated with a user by their name
    // Pre: name is a valid user name in the network
    // Post: Returns the unique ID of the user if found, or 0 if not found
    std::size_t getId(std::string name);

    // Read user data from a file and add users to the network
    // Pre: fname is the name of a valid file containing user data
    // Post: Reads user data from the file and adds users to the network, returns -1 if there is an error reading the file
    int readUsers(char *fname);

    // Write user data from the network to a file
    // Pre: fname is the name of a valid file where user data will be written
    // Post: Writes user data from the network to the file, returns -1 if there is an error writing to the file
    int writeUsers(char *fname);

    // Get the total number of users in the network
    // Pre: None
    // Post: Returns the number of users in the network
    std::size_t numUsers();

    // Get a User pointer by their unique ID
    // Pre: id is a valid user ID in the network
    // Post: Returns a pointer to the User object if found, or nullptr if not found
    User *getUser(std::size_t id);

    // Get a vector containing pointers to all users in the network
    // Pre: None
    // Post: Returns a vector of User pointers representing all users in the network
    std::vector<User *> getUsers() { return users_; }

    std::vector<std::size_t> shortestPath(std::size_t from, std::size_t to);
    std::vector<std::size_t> distanceUser(std::size_t from, std::size_t &to, std::size_t distance);

private:
    std::vector<User *> users_;
};

#endif
