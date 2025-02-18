#include "User.h"
#include "SortedLinkedList.h"
#include <cstddef>

User::User()
{
    id = 0;
    name = "";
    followers = new SortedLinkedList();
    followeds = new SortedLinkedList();
}

User::~User()
{
}

int User::getId()
{
    return id;
}

void User::setId(int user_id)
{
    id = user_id;
}

std::string User::getName()
{
    return name;
}

void User::setName(std::string user_name)
{
    name = user_name;
}

bool User::addFollower(User *user)
{
    return followers->add(user);
}

bool User::removeFollower(int userId)
{
    return followers->remove(userId);
}

bool User::addFollowed(User *user)
{
    return followeds->add(user);
}

bool User::removeFollowed(int userId)
{
    return followeds->remove(userId);
}

SortedLinkedList *User::getFollowers()
{
    return followers;
}

SortedLinkedList *User::getFolloweds()
{
    return followeds;
}