#ifndef USER_H_
#define USER_H_

#include "AVLTree.h"
#include "group.h"
#include "wet1util.h"

/** The following is a data structure of the type ob binary search tree
 * 
*/
class GroupTree;

class User {
public:

    User();
    ~User();

    class GroupTree;
    class AVLTree<GroupTree>;

    AVLTree<GroupTree> *group;
    int groupId;

    int total_comedy_views;
    int total_drama_views;
    int total_action_views;
    int total_fantasy_views;

};
//
//_____________________ User __________________________

AVLTree<User> *createUser(int key, bool vip);
// add allocation errors

void putInGroup(AVLTree<User> * user, AVLTree<GroupTree> *group, int userId);

AVLTree<User> *insertUser(AVLTree<User> *user, int key, bool vip);

AVLTree<User> *deleteUser(AVLTree<User> *user, int key);

AVLTree<User> *seekUser(AVLTree<User> *user, int key);

AVLTree<User> *setGroup(AVLTree<User> *user, int key, AVLTree<GroupTree> *group);

bool userInGroup(AVLTree<User> *user, int userId, int gorupId);

AVLTree<User> *userAddViews(AVLTree<User> *user, int key, Genre genre);

int userGetViews(AVLTree<User> *user, int key, Genre genre);






/*
    User(int id = 0, bool vip = false);
    ~User();
    //
    int get_genre_views(Genre genre);//
    StatusType add_genre_view(Genre genre);
    //
    bool is_user_vip();//
    //
    void add_user_to_group(int group_id);//
    int get_user_group();//
*/
#endif