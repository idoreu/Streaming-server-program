
#include <assert.h>
#include "wet1util.h"
#include "Watch_group.h"
#include "user.h"

//____________ User ____________
User::User()
{
    groupId = 0;
    total_comedy_views = 0;
    total_drama_views = 0;
    total_action_views = 0;
    total_fantasy_views = 0;
}

User::~User()
{
    group = NULL;
    delete this;
}
//__________ End of User __________


//_________ Standard AVL functions _________
AVLTree<User> *createUser(int key, bool vip)
{
    User node;
    AVLTree<User> *tree = new AVLTree<User>(key);
    tree->vip = vip;
    tree->node = node;
    return tree;
}

AVLTree<User> *seekUser(AVLTree<User> *tree, int key)
{
    assert(key > 0);
    bool check = tree->keyExists(key);
    assert(check);
    if(!check){
        throw StatusType::FAILURE;
    }
    if(key < tree->key){
        return seekUser(tree->left_child, key);
    } else if( tree->key< key){
        return seekUser(tree->right_child, key);
    }
    return tree;
}

AVLTree<User> *insertUser(AVLTree<User> *user, int key, bool vip)
{
    assert(user != NULL);
    assert(key > 0);

    User node;
    user = user->insertNode(node, key);

    AVLTree<User> *temp = seekUser(user, key);
    temp->vip = vip;
    return user;
}

AVLTree<User> *deleteUser(AVLTree<User> *user, int key)
{
    assert(key > 0);
    bool check = user->keyExists(key);
    if(!check){
        return user;
    }
    AVLTree<User> *temp = seekUser(user, key);
    int comedie = temp->node.total_comedy_views, drama = temp->node.total_drama_views;
    int action = temp->node.total_action_views, fantasy = temp->node.total_fantasy_views;
    removeuUserViews(user->node.group, comedie, action, drama, fantasy);

    temp = user->treeDeleteNode(key);
    return temp;
}

bool userInGroup(AVLTree<User> *user, int userId, int gorupId)
{
    assert(gorupId >= 0 && user != NULL);
    bool check = user->keyExists(userId);
    assert(check);
    if(!check){
        throw StatusType::FAILURE;
    }
    AVLTree<User> *temp = seekUser(user, userId);
    if(temp->node.groupId == gorupId){
        return true;
    }
    return false;
}

AVLTree<User> *userAddViews(AVLTree<User> *user, int key, Genre genre)
{
    assert(genre != Genre::NONE);
    bool check = user->keyExists(key);
    assert(check);
    if(!check){
        throw StatusType::FAILURE;
    }
    AVLTree<User> *temp = seekUser(user, key);
    switch (genre)
    {
    case Genre::COMEDY:
        temp->node.total_comedy_views++;
        break;
    case Genre::DRAMA:
        temp->node.total_drama_views++;
        break;
    case Genre::ACTION:
        temp->node.total_action_views++;
        break;
    case Genre::FANTASY:
        temp->node.total_fantasy_views++;
        break;
    default:
        break;
    }
    return user;
}

AVLTree<User> *setGroup(AVLTree<User> *user, int key, AVLTree<GroupTree> *group)
{
    assert(key > 0);
    //bool userExist = user->keyExists(key);
    assert(user->keyExists(key));
    bool check = userInGroup(user, key, 0);
    if(!check){
        return user;
    }

    int groupId = group->key;
    AVLTree<User> *temp = seekUser(user, key);
    temp->node.groupId = groupId;
    (temp->node.group) = group;
    return user;
}

int userGetViews(AVLTree<User> *user, int key, Genre genre)
{
    assert(key > 0 && user != NULL);
    bool check = user->keyExists(key);
    if(!check){
        throw StatusType::FAILURE;
    }
    AVLTree<User> * temp = seekUser(user, key);
    int ans = 0;
    switch (genre)
    {
    case Genre::COMEDY :
        ans = temp->node.total_comedy_views;
        break;
    case Genre::DRAMA :
        ans = temp->node.total_drama_views;
        break;
    case Genre::ACTION :
        ans = temp->node.total_action_views;
        break;
    case Genre::FANTASY :
        ans = temp->node.total_fantasy_views;
        break;   
    default :
        ans = temp->node.total_comedy_views;
        ans += temp->node.total_drama_views;
        ans += temp->node.total_action_views;
        ans += temp->node.total_fantasy_views;
        break;
    }
    return ans;
}
