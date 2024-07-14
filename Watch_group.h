
#ifndef GROUP_H_
#define GROUP_H_

#include "user.h"
#include "AVLTree.h"
  #include "wet1util.h"


class Group{
    public:
    //int views;
    AVLTree<User> *user;

    ~Group();
    Group();
    Group(AVLTree<User> *user);
    Group(const Group& group) = delete;
};

class GroupTree{
    public:
    GroupTree();
    ~GroupTree();
    GroupTree(const GroupTree &group) = delete;

    AVLTree<Group> *group;
    
    int comedieViews;
    int dramaViews;
    int actionViews;
    int fantasyViews;
};
//______________________ Group _______________________________

//
//__________________ AVL-Tree Group __________________________
/** Create an AVL tree for a group
 * params:
 * @ userId - an integer that represents the user a geiven node points to.
 * retun value:
 * @ pointer to the root of the group.
*/
AVLTree<Group> *createGroup();

/** Adding a new user (via it's pointer) to the correct position in the 
 * group tree.
 * params:
 * @ group - pointer to the root of the group tree.
 * @ user - pointer to the root of the user tree
 * @ userId - integer that identifies the user in the tree
 * retun value:
 * @ pointer to the root of the group.

AVLTree<Group> *groupAddUser(AVLTree<Group> *group ,AVLTree<User> *user, int groupId);
*/

/** Returning a pointer to the node in the AVL-tree with key <key>
 * params:
 * @ tree - a pointer to the tree's root.
 * @ key - the identification key of the new group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *seekGroup(AVLTree<GroupTree> *tree, int key);

/** Evaluating the favourit movie genre of the group
 * params:
 * @ group - a pointer to the root of the group tree.
 * retun value:
 * @ The favourite genre.
*/
Genre getFavouriteGenre(AVLTree<GroupTree> *tree);

/** Returns the value of "favouriteMovie", of the root of the group
 * params:
 * @ group - a pointer to the root of the group tree.
 * return value:
 * @ the value of the field in the root.
*/
int getFavouriteMovie(AVLTree<Group> *group);

//___________________ Group Tree ___________________
/** Create an AVL tree of the class "GroupTree"
 * params:
 * @ groupId - the groups Id number.
 * return value:
 * @ a pointer to the root of the tree.
*/
AVLTree<GroupTree> *CreateGroupTree(int groupId);
// default group tree key is 0

/** Addes a new group node to the AVL tree
 * params:
 * @ tree - a pointer to the tree's root.
 * @ key - the identification key of the new group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *insertGroup(AVLTree<GroupTree> *tree, int key);
// Take care of allocation problams

/** Deletes a node from the tree
 * params:
 * @ tree - a pointer to the tree's root.
 * @ key - the identification key of the group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *deleteGroupTreeNode(AVLTree<GroupTree> *tree, int key);

/** Addes a new user to a preffered group int the group-tree
 * params:
 * @ tree - a pointer to the tree's root.
 * @ user - a pointer to a User-node in the User-tree
 * @ groupId - the identification key of the group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *groupTreeAddUser(AVLTree<GroupTree> *tree, AVLTree<User> *user, int groupId);

/** Adds views to a given group according to the number of users in the tree
 * Also adds to each user in the group accordingly
 * params:
 * @ tree - a pointer to the tree's root.
 * @ groupId - the identification key of the group.
 * @ genre - the genre of the movie.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *groupAddViews(AVLTree<GroupTree> *tree, int groupId, Genre genre);

/** Returns a pointer to the correct node given one exists with the same id
 * params:
 * @ tree - a pointer to the tree's root.
 * @ groupId - the identification key of the group.
 * return value:
 * @ a pointer to the tree's root/
*/
AVLTree<GroupTree> *getGroup(AVLTree<GroupTree> *tree, int groupId);

//______________ Deleting a user that is in a group ______________
/** Given a user is being removed form the system,
 * we subtract it's views from the collective
*/
void removeuUserViews(AVLTree<GroupTree> *group, int comedie,int action, int drama, int fantasy);


int getGroupSize(AVLTree<GroupTree> *tree, int groupId);


#endif