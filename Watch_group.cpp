
#include <assert.h>
#include "group.h"
#include "AVLTree.h"
#include"wet1util.h"
#include "user.h"

//____________________ Group ______________________
Group::Group()
{
    //views = 0;
    user = new AVLTree<User>();
}
Group::Group(AVLTree<User> *user) : user(user)
{
    //views = 0;
}
Group::~Group()
{
    user = NULL;
}
//=================================================


//___________________ GroupTree ___________________
GroupTree::GroupTree()
{
    group = new AVLTree<Group>();
    //favouriteMovie = 0;
    comedieViews = 0;
    dramaViews = 0;
    actionViews = 0;
    fantasyViews = 0;
}
GroupTree::~GroupTree()
{
    AVLTree<Group> *temp = group;
    while(temp->left_child != NULL && temp->right_child != NULL)
    {
        if(temp->left_child != NULL){
            int key = temp->left_child->key;
            temp = temp->treeDeleteNode(key);
        }
        if(temp->right_child != NULL){
            int key = temp->right_child->key;
            temp = temp->treeDeleteNode(key);
        }
    }
    int key = temp->key;
    temp->treeDeleteNode(key);
}
//=================================================

//__________________ AVL-Tree Group __________________________
/** Create an AVL tree for a group
 * params:
 * @ userId - an integer that represents the user a geiven node points to.
 * retun value:
 * @ pointer to the root of the group.
*/
AVLTree<Group> *createGroup()
{
    AVLTree<Group> *group = new AVLTree<Group>();
    group->key = 0;
    group->heap = 0;
    group->height = 0;
    group->vip = false;
    group->node = Group();
}

/** Addes a new user to a preffered group int the group-tree
 * params:
 * @ tree - a pointer to the tree's root.
 * @ user - a pointer to a User-node in the User-tree
 * @ groupId - the identification key of the group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *groupTreeAddUser(AVLTree<GroupTree> *tree, AVLTree<User> *user, int groupId)
{
    bool check = tree->keyExists(groupId);
    assert(groupId >= 0 && check && user != NULL);
    
    int userId = user->key;
    Group node(user);
    AVLTree<GroupTree> *temp = seekGroup(tree, groupId);
//----
    if(temp->node.group->key == 0){// If the group has no users
        temp->node.group->key = userId;
        temp->node.group->node.user = user;
        return tree;
    } else {
        Group node(user);
        temp->node.group = temp->node.group->insertNode(node, userId);
    }
//---
    return tree;
}

//============== Helper function for get-favourite-movie
int evaluateMax(int num0, int num1, int num2, int num3)
{
    if(num0 < num1 && num2 < num3){
        if(num1 < num3){
            return 3;
        } else {
            return 1;
        }
    } else if(num1 < num0 && num2 < num3){
        if(num0 < num3){
            return 3;
        }
        return 0;
    } else if(num0 < num1 && num3 < num2){
        if(num1 < num2){
            return 2;
        }
        return 1;
    } else { // num1 < num0 && num3 < num2
        if(num0 < num2){
            return 2;
        }
    }
    return 0;
}//getType

/** Returns the value of "favouriteMovie", of the root of the group
 * params:
 * @ group - a pointer to the root of the group tree.
 * return value:
 * @ the value of the field in the root.
*/
int getFavouriteMovie(AVLTree<Group> *group)
{
    int favouriteGenre;
}


//___________________ Group Tree ___________________
/** Create an AVL tree of the class "GroupTree"
 * params:
 * @ groupId - the groups Id number.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<GroupTree> *CreateGroupTree(int groupId)
{
    AVLTree<GroupTree> *tree = new AVLTree<GroupTree>();
    tree->key = groupId;
    return tree;
}

/** Addes a new group node to the AVL tree
 * params:
 * @ tree - a pointer to the tree's root.
 * @ key - the identification key of the new group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *insertGroup(AVLTree<GroupTree> *tree, int key)
{
    GroupTree node;
    tree->insertNode(node, key);
    return tree;
}

/** incrementing the views counts of the users in a given group before earasing the group
 * 
*/
void addViewsToUsers(AVLTree<Group> *tree, int comedie, int drama, int action, int fantasy)
{
    if(tree == NULL){
        return;
    }
    addViewsToUsers(tree->left_child, comedie, drama, action, fantasy);
    tree->node.user->node.total_comedy_views += comedie;
    tree->node.user->node.total_drama_views += drama;
    tree->node.user->node.total_action_views += action;
    tree->node.user->node.total_fantasy_views += fantasy;
    addViewsToUsers(tree->left_child, comedie, drama, action, fantasy);
}

/** Deletes a node from the tree
 * params:
 * @ tree - a pointer to the tree's root.
 * @ key - the identification key of the group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *deleteGroupTreeNode(AVLTree<GroupTree> *tree, int key)
{
    AVLTree<GroupTree> *seek = seekGroup(tree, key);
    //___
    int comedie = seek->node.comedieViews, drama = seek->node.dramaViews;
    int action = seek->node.actionViews, fantasy = seek->node.fantasyViews;
    //===
    addViewsToUsers(tree->node.group, comedie, drama, action, fantasy);
    return tree->treeDeleteNode(key);
}

AVLTree<GroupTree> *seekGroup(AVLTree<GroupTree> *tree, int key)
{
    assert(key > 0 && tree != NULL);
    bool check = tree->keyExists(key);
    if(!check){
        return tree;
    }
    if(key < tree->key){
        return seekGroup(tree->left_child, key);
    } else if(tree->key < key){
        return seekGroup(tree->right_child, key);
    }
    return tree;
}

/** Adds views to a given group according to the number of users in the tree
 * Also adds to each user in the group accordingly
 * params:
 * @ tree - a pointer to the tree's root.
 * @ groupId - the identification key of the group.
 * @ genre - the genre of the movie.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *groupAddViews(AVLTree<GroupTree> *tree, int groupId, Genre genre)
{
    if(tree == NULL){
        return NULL;
    }
    assert(groupId >= 0 && genre != Genre::NONE);
    bool check = tree->keyExists(groupId);
    assert(check);
    //
    AVLTree<GroupTree> *temp = seekGroup(tree, groupId);
    int viewers = temp->node.group->heap;
    switch (genre)
    {
    case Genre::COMEDY :
        temp->node.comedieViews += viewers;
        break;
    case Genre::DRAMA :
        temp->node.dramaViews += viewers;
        break;
    case Genre::ACTION :
        temp->node.actionViews += viewers; 
        break;
    case Genre::FANTASY :
        temp->node.fantasyViews += viewers;  
    default:
        break;
    }
    return tree;
}
//______________ Deleting a user that is in a group ______________
/** Given a user is being removed form the system,
 * we subtract it's views from the collective
*/
void removeuUserViews(AVLTree<GroupTree> *group, int comedie,int action, int drama, int fantasy)
{
    if(group->node.comedieViews < comedie){
        group->node.comedieViews = 0;
    } else{
        group->node.comedieViews -= comedie;
    }
    if(group->node.dramaViews < drama){
        group->node.dramaViews = 0;
    } else{
        group->node.dramaViews -= comedie;
    }
    if(group->node.actionViews < action){
        group->node.actionViews = 0;
    } else{
        group->node.actionViews -= action;
    }
    if(group->node.fantasyViews < fantasy){
        group->node.fantasyViews = 0;
    } else{
        group->node.fantasyViews -= fantasy;
    }
}


//++++++++++++++++++
/** Evaluating the favourit movie genre of the group
 * params:
 * @ group - a pointer to the root of the group tree.
 * retun value:
 * @ The favourite genre.
*/
Genre getFavouriteGenre(AVLTree<GroupTree> *group)
{
    int comedie = group->node.comedieViews, drama = group->node.dramaViews;
    int action = group->node.actionViews, fantasy = group->node.fantasyViews;
    int evaluate = evaluateMax(comedie, drama, action, fantasy);
    switch (evaluate)
    {
    case 0:
        return Genre::COMEDY;
        break;
    case 1:
        return Genre::DRAMA;
        break;
    case 2:
        return Genre::ACTION;
        break;
    }
    return Genre::FANTASY;
}

int getGroupSize(AVLTree<GroupTree> *tree, int groupId)
{
    AVLTree<GroupTree> *temp = seekGroup(tree, groupId);
    return temp->node.group->heap;
}