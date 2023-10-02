#include "network.h"
#include "user.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <stack>
// Default constructor
// Pre: None
// Post: Creates an empty Network object
Network::Network()
{
    users_.clear();
}
// Destructor
// Pre: None
// Post: Cleans up allocated resources when the Network object is destroyed
Network::~Network()
{
    for (User *userPtr : users_)
    {
        delete userPtr;
    }
}
// Add a User pointer to the network
// Pre: userPointer is a valid pointer to a User object
// Post: Adds the User to the network
void Network::addUser(User *userPointer)
{
    users_.push_back(userPointer);
}
// Add a connection between two users in the network
// Pre: s1 and s2 are valid user names in the network
// Post: Adds a connection between the users if they exist, returns -1 if not
int Network::addConnection(std::string s1, std::string s2)
{
    // no self connection
    if (s1 == s2)
    {
        return -1;
    }
    else
    {
        User *profileOne = nullptr;
        User *profileTwo = nullptr;
        for (User *userPtr : users_)
        {
            if (userPtr->getName() == s1)
                profileOne = userPtr;
        }
        for (User *userPtr : users_)
        {
            if (userPtr->getName() == s2)
                profileTwo = userPtr;
        }
        // if one of the profiles does not exist return -1
        if (!(profileOne && profileTwo))
            return -1;
        profileOne->addFriend(profileTwo->getId());
        profileTwo->addFriend(profileOne->getId());
    }
    return 0;
}
// Remove a connection between two users in the network
// Pre: s1 and s2 are valid user names in the network
// Post: Removes the connection between the users if it exists, returns -1 if not
int Network::removeConnection(std::string s1, std::string s2)
{
    User *profileOne = nullptr;
    User *profileTwo = nullptr;
    for (User *userPtr : users_)
    {
        if (userPtr->getName() == s1)
            profileOne = userPtr;
    }
    for (User *userPtr : users_)
    {
        if (userPtr->getName() == s2)
            profileTwo = userPtr;
    }
    if (!(profileOne && profileTwo))
        return -1;
    profileOne->deleteFriend(profileTwo->getId());
    profileTwo->deleteFriend(profileOne->getId());

    return 0;
}
// Get the unique ID associated with a user by their name
// Pre: name is a valid user name in the network
// Post: Returns the unique ID of the user if found, or 0 if not found
std::size_t Network::getId(std::string name)
{
    for (User *userPtr : users_)
    {
        if (userPtr->getName() == name)

            return userPtr->getId();
    }
    throw std::runtime_error("Name not found");
}
// Get the total number of users in the network
// Pre: None
// Post: Returns the number of users in the network
std::size_t Network::numUsers()
{
    return users_.size();
}
// Get a User pointer by their unique ID
// Pre: id is a valid user ID in the network
// Post: Returns a pointer to the User object if found, or nullptr if not found
User *Network::getUser(std::size_t id)
{
    for (User *userPtr : users_)
    {
        if (userPtr->getId() == id)
            return userPtr;
    }
    return nullptr;
}
// Read user data from a file and add users to the network
// Pre: fname is the name of a valid file containing user data
// Post: Reads user data from the file and adds users to the network, returns -1 if there is an error reading the file
int Network::readUsers(char *fname)
{

    std::ifstream myfile;
    myfile.open(fname);
    std::string firstLine;
    // so we can skip the first line
    std::getline(myfile, firstLine);
    std::string myline;
    int i = 0;
    if (!myfile.is_open())
    {
        return -1; // Indicate failure
    }
    User *userRead = new User();
    while (std::getline(myfile, myline))
    {
        std::stringstream ss(myline);
        switch (i % 5)
        {
        case 0:
        {
            int id;
            ss >> id;
            userRead->setId(id);
            break;
        }
        case 1:
        {
            std::string fullname;
            std::string name;
            bool isFirst = true; // Flag to track the first name
            // concatanate full name
            while (ss >> name)
            {
                if (!isFirst)
                {
                    fullname += " "; // Add a space between names
                }
                fullname += name;
                isFirst = false;
            }
            userRead->setName(fullname);

            break;
        }
        case 2:
        {
            int birthYear;
            ss >> birthYear;
            userRead->setBirthYear(birthYear);

            break;
        }
        case 3:
        {
            int zipCode;
            ss >> zipCode;
            userRead->setZipCode(zipCode);

            break;
        }
        case 4:
        {
            std::size_t friends;
            std::vector<std::size_t> result;
            while (ss >> friends)
            {
                result.push_back(friends);
            }
            userRead->setFriendsList(result);
            users_.push_back(userRead);
            userRead = new User();
            break;
        }
        default:
            // Code to handle any other case not covered by the above cases
            break;
        }
        i++;
    }

    return 0;
}
// Write user data from the network to a file
// Pre: fname is the name of a valid file where user data will be written
// Post: Writes user data from the network to the file, returns -1 if there is an error writing to the file
int Network::writeUsers(char *fname)
{
    std::ofstream myfile(fname);

    if (!myfile.is_open())
    {
        return -1; // Indicate failure
    }
    myfile << users_.size() << std::endl;

    // Loop through the network's users_
    for (const User *user : users_)
    {
        // Write user information to the file
        myfile << user->getId() << std::endl;
        myfile << "\t" << user->getName() << std::endl;
        myfile << "\t" << user->getBirthYear() << std::endl;
        myfile << "\t" << user->getZipCode() << std::endl;

        // Write the IDs of connected users (assuming you have a method to get them)

        for (int friends : user->getFriendsList())
        {
            myfile << friends << " ";
        }
        myfile << std::endl;
    }

    myfile.close();

    return 0; // Indicate success
}
std::vector<std::size_t> Network::shortestPath(std::size_t from, std::size_t to)
{
    std::vector<size_t> parent(users_.size(), -1);
    std::queue<size_t> q;
    std::vector<bool> visited(users_.size(), 0);
    std::vector<size_t> distance(users_.size(), -1);

    distance[from] = 0;
    q.push(from);

    while (q.size() > 0)
    {
        size_t current_id = q.front();
        q.pop();

        if (visited[current_id])
            continue;
        visited[current_id] = true;

        // add friends to queue
        User *currentUser = getUser(current_id);
        for (size_t i : currentUser->getFriendsList())
        {
            size_t friendId = i;
            q.push(friendId);
            if (distance[friendId] == -1)
            {
                distance[friendId] = distance[current_id] + 1;
                parent[friendId] = current_id;
            }
        }
    }
    std::vector<size_t> shortestPath;
    size_t endUser = to;
    while (endUser != from)
    {
        shortestPath.push_back(endUser);
        endUser = parent[endUser];
    }
    shortestPath.push_back(from);
    std::reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}
std::vector<std::size_t> Network::distanceUser(std::size_t from, std::size_t &to, std::size_t distance)
{
    std::vector<size_t> parent(users_.size(), -1);
    std::stack<size_t> stck;                     // First in, last out
    std::vector<bool> visited(users_.size(), 0); // bool visited[n];
    stck.push(from);

    while (stck.size() > 0 && distance > 0)
    {
        // Visit the next user
        size_t current_id = stck.top();
        stck.pop();
        if (visited[current_id])
        {
            continue;
        }
        visited[current_id] = true;
        User *currentUser = getUser(current_id);
        for (size_t friendId : currentUser->getFriendsList())
        {
            stck.push(friendId);
            parent[friendId] = current_id;
        }
        distance--;
    }
    while (!stck.empty())
    {
        std::size_t endCanadite = stck.top();
        User *currentEndCanadite = getUser(endCanadite);
        User *fromUser = getUser(from);
        for (size_t neighbor : currentEndCanadite->getFriendsList())
        {
            auto it = std::find(fromUser->getFriendsList().begin(), fromUser->getFriendsList().end(), neighbor);
            if (it == fromUser->getFriendsList().end())
            {
                to = neighbor;
                break;
            }
        }
        stck.pop();
    }
    std::vector<size_t> nearestNeighbor;
    size_t endUser = to;
    while (endUser != from)
    {
        nearestNeighbor.push_back(endUser);
        endUser = parent[endUser];
    }
    nearestNeighbor.push_back(from);
    std::reverse(nearestNeighbor.begin(), nearestNeighbor.end());
    return nearestNeighbor;
}
