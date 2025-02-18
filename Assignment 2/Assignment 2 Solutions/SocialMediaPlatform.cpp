#include "SocialMediaPlatform.h"
#include "SortedLinkedList.h"
#include "User.h"
#include "LinkedListNode.h"
#include <iostream>
#include <cstddef>

SocialMediaPlatform::SocialMediaPlatform()
{
    users = new SortedLinkedList();
}

SocialMediaPlatform::~SocialMediaPlatform()
{
    delete users;
}

bool SocialMediaPlatform::addUser(const int userId, const std::string name)
{
    if (users->checkIfExist(userId))
    {
        return false;
    }

    User *newUser = new User();
    newUser->setName(name);
    newUser->setId(userId);

    return users->add(newUser);
}

bool SocialMediaPlatform::removeUser(const int userId)
{
    if (!users->checkIfExist(userId))
    {
        return false;
    }

    LinkedListNode *tmp = users->getPointerTo(userId)->u->getFolloweds()->getHead();

    for (LinkedListNode *currFollowedUser = tmp; currFollowedUser != NULL; currFollowedUser = currFollowedUser->next)
    {
        users->getPointerTo(currFollowedUser->u->getId())->u->removeFollower(userId);
    }

    return users->remove(userId);
}

bool SocialMediaPlatform::followUser(const int firstUserId, const int secondUserId)
{
    if (!(users->checkIfExist(firstUserId)))
    {
        return false;
    }

    else if (!(users->checkIfExist(secondUserId)))
    {
        return false;
    }
    else if (users->getPointerTo(firstUserId)->u->getFolloweds()->checkIfExist(secondUserId))
    {
        return false;
    }
    else
    {
        users->getPointerTo(firstUserId)->u->addFollowed(users->getPointerTo(secondUserId)->u);
        users->getPointerTo(secondUserId)->u->addFollower(users->getPointerTo(firstUserId)->u);
        return true;
    }
}

bool SocialMediaPlatform::unfollowUser(const int firstUserId, const int secondUserId)
{
    if (!(users->checkIfExist(firstUserId)))
    {
        return false;
    }
    else if (!(users->checkIfExist(secondUserId)))
    {
        return false;
    }
    else if (!(users->getPointerTo(firstUserId)->u->getFolloweds()->checkIfExist(secondUserId)))
    {
        return false;
    }
    else
    {
        users->getPointerTo(firstUserId)->u->removeFollowed(secondUserId);
        users->getPointerTo(secondUserId)->u->removeFollower(firstUserId);
        return true;
    }
}

void SocialMediaPlatform::showFollowersOf(const int userId) const
{
    if (!users->checkIfExist(userId))
    {
        std::cout << "Cannot show. There is no user with ID " << userId << "." << std::endl;
        return;
    }
    std::cout << "Users following the user with ID " << userId << ":" << std::endl;
    users->getPointerTo(userId)->u->getFollowers()->print();
}

void SocialMediaPlatform::showAllUsers() const
{
    std::cout << "Users in the social media platform:"
              << std::endl;
    users->print();
}