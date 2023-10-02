#include "user.h"
#include "network.h"
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
void testAddFriend()
{
    cout << "testAddFriend...";
    User userOne(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    User userTwo(4, "Sami Shibli", 2000, 94087, vector<size_t>{0, 1, 2});
    userOne.addFriend(userTwo.getId());
    // cout << userOne;
    // algorithim to check if user two exist in user ones friends list
    assert((std::find(userOne.getFriendsList().begin(), userOne.getFriendsList().end(), userTwo.getId()) != userOne.getFriendsList().end()));
}
void testDeleteFriend()
{
    cout << "test Delete Friend...";
    User userOne(4, "Sami Shibli", 2000, 94087, vector<size_t>{0, 1, 2});
    // cout << userOne;
    // algorithim to check if user two exist in user ones friends list
    userOne.deleteFriend(2);
    // cout << userOne;
    bool found = false;
    for (auto v : userOne.getFriendsList())
    {
        if (v == 2)
            found = true;
    }

    // Check if userTwo's ID is no longer in userOne's friends list
    // cout << *(std::find(userOne.getFriendsList().begin(), userOne.getFriendsList().end(), 1)); // - userOne.getFriendsList().begin();
    // assert((std::find(userOne.getFriendsList().begin(), userOne.getFriendsList().end(), 1) == userOne.getFriendsList().end()));
    assert(found == false);
    // cout << userOne;
    cout << "Passed!" << endl;
}
void testUserGetId()
{
    cout << "test User GetId...";
    User userOne(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    assert(userOne.getId() == 3);
    // ...
    cout << "Passed!" << endl;
}
void testUserGetName()
{
    cout << "test User Get Name...";
    User userOne(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    assert(userOne.getName() == "Jason Chen");
    // ...
    cout << "Passed!" << endl;
}
void testUserGetBirthYear()
{
    cout << "test User Get BirthYear...";
    User userOne(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    assert(userOne.getBirthYear() == 2000);
    // ...
    cout << "Passed!" << endl;
}
void testUserGetZipCode()
{
    cout << "test User Get Zipcode...";
    User userOne(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    assert(userOne.getZipCode() == 94087);
    // ...
    cout << "Passed!" << endl;
}
void testUserGetFriendsList()
{
    cout << "test User Get Friends List...";
    User userOne(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    std::vector<size_t> expectedFriendsList = {0, 1, 2};

    assert(expectedFriendsList == userOne.getFriendsList());
    // ...
    cout << "Passed!" << endl;
}

void testConstructorGetter()
{
    cout << "testConstructorGetter...";
    User *u = new User(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    assert(u->getId() == 3);
    // ...
    cout << "Passed!" << endl;
}
// test add user functionality as well as numUsers. Assert would not pass if the add User does not work.
void testNumUsersAndAddUser()
{
    cout << "test numUsers function...";
    Network network;
    User *u = new User(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    User *x = new User(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    network.addUser(u);
    network.addUser(x);
    assert(network.numUsers() == 2);
    cout << "Passed!" << endl;
}
void testGetUser()
{
    cout << "test getUser function...";
    Network network;
    User *u = new User(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    network.addUser(u);
    User *foundUser = network.getUser(3);
    assert(foundUser != nullptr);
    assert(foundUser->getId() == 3);

    cout << "Passed!" << endl;
}
void testGetId()
{
    cout << "test GetId function...";
    Network network;
    User *u = new User(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    network.addUser(u);
    size_t result = network.getId("Jason Chen");
    assert(result == 3);
    cout << "Passed!" << endl;
}
void testAddConnection()
{
    cout << "add connection test...";
    Network network;
    User *u = new User(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    User *x = new User(4, "Sami Shibli", 2000, 94087, vector<size_t>{0, 1, 2});
    User *y = new User(5, "Drew Smith", 2000, 94087, vector<size_t>{0, 1, 2});
    network.addUser(x);
    network.addUser(u);
    network.addUser(y);
    // Create User objects and add them to the network

    int result = network.addConnection("Sami Shibli", "Drew Smith");
    // Check if the result is 0 (indicating success)
    assert(result == 0);
    cout << "passed" << endl;
}
void testRemoveConnection()
{
    cout << "remove connection test...";
    Network network;
    User *u = new User(3, "Jason Chen", 2000, 94087, vector<size_t>{0, 1, 2});
    User *x = new User(4, "Sami Shibli", 2000, 94087, vector<size_t>{0, 1, 2, 5});
    User *y = new User(5, "Drew Smith", 2000, 94087, vector<size_t>{});
    network.addUser(x);
    network.addUser(u);
    network.addUser(y);
    // Create User objects and add them to the network
    int result = network.removeConnection("Sami Shibli", "Drew Smith");
    // Check if the result is 0 (indicating success)
    assert(result == 0);
    cout << "passed" << endl;
}

int main()
{
    testConstructorGetter();
    testAddConnection();
    testRemoveConnection();
    testNumUsersAndAddUser();
    testGetUser();
    testGetId();
    testAddFriend();
    testDeleteFriend();
    testUserGetId();
    testUserGetName();
    testUserGetBirthYear();
    testUserGetFriendsList();
    testUserGetZipCode();

    return 0;
}