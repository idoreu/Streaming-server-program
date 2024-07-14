#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
using namespace std;

template <typename T>
class AVLTree {
    public:

    AVLTree();
    AVLTree(int key);
    AVLTree(int key, T &node);
    ~AVLTree();

    AVLTree<T> *insertNode(const T &node, int key);
    //
    void setVip(int key, bool isVip);
    bool isVip(int key);
    //
    int countNodes();
    AVLTree *treeDeleteNode(int key);
    //
    T &getType(int key);// probably problamatic
    bool keyExists(int key);
    //
    int key;
    bool vip;
    int height;
    int heap;
    T node;
    AVLTree<T> *left_child;
    AVLTree<T> *right_child;

    AVLTree<T> *treeAddNode(T node, int groupId)
};

template <typename T>
AVLTree<T> *balanceTree(AVLTree<T> *tree);

template <typename T>
AVLTree<T> *deleteNode(AVLTree<T> *tree, int key);

// create and a return an array of pointers to the noads

#endif