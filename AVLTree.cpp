

#include <assert.h>
#include "AVLTree.h"

//____________________________
int max(int a, int b)
{
    if(b < a){
        return a;
    }
    return b;
}
template <typename T>
static int height(AVLTree<T> *node)
{
    if(node == NULL){
        return 0;
    }
    return node->height;
}
template <typename T>
static int heap(AVLTree<T> *node)
{
    if(node == NULL){
        return 0;
    }
    return node->heap;
}
//_____________________________

template <typename T>
AVLTree<T>::AVLTree()
{
    node = T();
    key = 0;
    height = 0;
    heap = 1;
    vip = false;
    left_child = NULL;
    right_child = NULL;
}

template <typename T>
AVLTree<T>::AVLTree(int key) : key(key)
{
    T node;
    node = node;
    height = 0;
    heap = 1;
    vip = false;
    left_child = NULL;
    right_child = NULL;
}

/** Constructor of the class AVL-tree*/
template <typename T>
AVLTree<T>::AVLTree(int key, T &node) : key(key), node(node)
{
    height = 0;
    heap = 1;
    vip = false;
    left_child = NULL;
    right_child = NULL;
}

template <typename T>
bool AVLTree<T>::keyExists(int key)
{
    if(this->key == key){
        return true;
    }
    if(this->key < key && this->right_child != NULL){
        return this->right_child->keyExists(key);
    } else if(this->key > key && this->left_child != NULL){
        return this->left_child->keyExists(key);
    }
    return false;
}

template <typename T>
T &AVLTree<T>::getType(int key)
{
    /*Assuming that function keyExists() returned true, and we 
    should eventually get to the correct node*/
    if(this->key < key){
        assert(this->right_child != NULL);
        return this->right_child->getType(key);

    } else if(this->key > key) {
        assert(this->left_child != NULL);
        return this->left_child->getType(key);
    }
    return this->node;
}
//_______________ Height and heap __________________//

template <typename T>
void correctHeap(AVLTree<T> *node)
{
    if(node == NULL){
        return;
    }
    node->heap = heap(node->left_child) + heap(node->right_child) +1;
    return;
}

template <typename T>
void correctHeight(AVLTree<T> *node)
{
    if(node == NULL){
        return;
    }
    if(node->right_child == NULL )
    node->height = max(height(node->left_child), height(node->right_child)) + 1;
    return;
}

// __________ Tree correction section _____________ //

template <typename T>
static int getBalanceFactor(AVLTree<T> *node)
{
    if(node == NULL){
        return 0;
    }
    return height(node->left_child) - height(node->right_child);
}
//______________________________________________________________
/** In the next four roll-type functions we assume the system
 * called them after reashuring that the pointers in use are not
 * Null.
//______________________________________________________________*/


/** When the the right sub-tree of node->right_child is heigher than the left sub-tree,
 * param: @nod - the lowest node in the tree that is out of balance
 * return value - the root of the sub-tree after rotating
 *      0               
 *       \              0
 *        0     =>     / \
 *         \          0   0
 *          0          
*/
template <typename T>
AVLTree<T> *rollRightRight(AVLTree<T> *node)
{
    assert(node != NULL && node->right_child != NULL);
    // system knows that temp exists before callin it.
    //
    AVLTree<T> *temp = node->right_child;
    node->right_child = temp->left_child;
    temp->left_child = node;
    // Correcting node's members
    correctHeight(node);
    correctHeap(node);
    //
    correctHeight(temp);
    correctHeap(temp);
    //
    return temp;
}

/** When the left sub-tree of nod->right_child is heigher than the right sub-tree,
 * param: @node - the lowest node in the tree that is off balanced
 * return value - the root of the sub-tree after the correction
 * 
 *      0               
 *       \              0
 *        0     =>     / \
 *       /            0   0
 *      0             
*/
template <typename T>
AVLTree<T> *rollRightLeft(AVLTree<T> *node)
{
    assert(node != NULL && node->right_child != NULL && node->right_child->left_child != NULL);
    //
    AVLTree<T> *temp1 = node->right_child;
    AVLTree<T> *temp2 = temp1->left_child;
    //
    node->right_child = temp2->left_child;
    temp2->left_child = node;
    temp1->left_child = temp2->right_child;
    temp2->right_child = temp1;
    // Correcting node's members
    correctHeight(node);
    correctHeap(node);
    //
    correctHeight(temp1);
    correctHeap(temp1);
    //
    correctHeight(temp2);
    correctHeap(temp2);

    return temp2;
}
/** When the left sub-tree of nod->left_child is heigher than the right sub-tree,
 * param: @node - the lowest node in the tree that is off balanced
 * return value - the root of the sub-tree after the correction
 * 
 *          0           
 *         /            0
 *        0     =>     / \
 *       /            0   0
 *      0             
*/
template <typename T>
AVLTree<T> *rollLeftLeft(AVLTree<T> *node)
{
    assert(node != NULL && node->left_child != NULL);
    //
    AVLTree<T> *temp = node->left_child;
    node->left_child = temp->right_child;
    temp->right_child = node;
    // Correcting node's members
    correctHeight(node);
    correctHeap(node);
    //
    correctHeight(temp);
    correctHeap(temp);
    //
    return temp;
}

/** When the right sub-tree of nod->left_child is heigher than the left sub-tree,
 * param: @node - the lowest node in the tree that is off balanced
 * return value - the root of the sub-tree after the correction
 * 
 *          0           
 *         /            0
 *        0     =>     / \
 *         \          0   0
 *          0       
*/
template <typename T>
AVLTree<T> *rollLeftRight(AVLTree<T> *node)
{
    assert(node != NULL && node->left_child != NULL && node->left_child->right_child != NULL);
    //
    AVLTree<T> *temp1 = node->left_child;
    AVLTree<T> *temp2 = node->right_child;
    //
    node->left_child = temp2->right_child;
    temp2->right_child = node;
    temp1->right_child = temp2->left_child;
    temp2->left_child = temp1;
    // Correcting node's members
    correctHeight(node);
    correctHeap(node);
    //
    correctHeight(temp1);
    correctHeap(temp1);
    //
    correctHeight(temp2);
    correctHeap(temp2);
    return temp2;
}

//assuming node is the lowest node in the tree that is not balanced
template <typename T>
AVLTree<T> *rotateRight(AVLTree<T> *node)
{
    assert(node != NULL);
    if(getBalanceFactor(node->right_child) > 0){
        return rollRightLeft(node);
    } else{
        return rollRightRight(node);
    }
}

template <typename T>
AVLTree<T> *rotateLeft(AVLTree<T> *node)
{
    assert(node != NULL);
    if(getBalanceFactor(node->left_child) > 0){
        return rollLeftLeft(node);
    } else {
        return rollLeftRight(node);
    }
}

template <typename T>
AVLTree<T> *balanceTree(AVLTree<T> *tree)
{
    if(tree == NULL){
        return NULL;
    }
    if(getBalanceFactor(tree) > 1){
        int check = getBalanceFactor(tree->left_child);
        if(check > 1 || check < -1){
            tree->left_child = balanceTree(tree->left_child);
            return tree = balanceTree(tree);// this is for balancing after a deletion of a node
        } else {
            AVLTree<T> *temp = rotateLeft(tree);
            return temp;
        }
    } else if(getBalanceFactor(tree) < -1){
        int check = getBalanceFactor(tree->right_child);
        if(check > 1 || check < -1){
            tree->right_child = balanceTree(tree->right_child);
            return tree->balanceTree();
        } else {
            AVLTree<T> *temp = rotateRight(tree);
            return temp;
        }
    }
    return tree;
}

template <typename T>
int AVLTree<T>::countNodes()
{
    return this->heap;
}


//__________________ Data insertion ____________________

template <typename T>
AVLTree<T> *AVLTree<T>::insertNode(const T &node, int key)
{   
    assert(key >= 0);
    if(this->key == 0){
        this->key = key;
        this->node = node;
        return this;
    }
    if(this->key == key){
        this->node = node;
        return this;
    }
    if(key < this->key){
        if(this->left_child == NULL){
            AVLTree<T> temp(key);
            this->left_child = &temp;
            if(this->right_child == NULL){
                this->height += 1;
                this->heap +=1;
            }
        } else if(this->left_child->key != key){
            int check = this->left_child->height;
            this->left_child->insertNode(node, key);
            if(check > this->left_child->height){
                this->height = this->left_child->height +1;
            }
        }
    } else {
        if(this->right_child->key == NULL){
            AVLTree<T> temp(key);
            this->right_child = &temp;
            if(this->left_child == NULL){
                this->height +=1;
                this->heap +=1;
            }
        }   
        else if(this->right_child->key != key){
            int check = this->right_child->height;
            this->right_child->insertNode(node, key);
            if(check < this->right_child->height){
                this->height = this->right_child->height +1;
            }
        }
    }
    AVLTree<T> *tree = balanceTree(this);
    return tree;
}

//________________ Deletion Section ____________________

template <typename T>
AVLTree<T> *trickleDown(AVLTree<T> *root)
{
    assert(root != NULL);
    assert(root->left_child != NULL && root->right_child != NULL);
    AVLTree<T> *father = root->right_child;
    
    if(father->left_child == NULL){
        father->left_child = root->left_child;
        root->left_child = NULL;
        root->right_child = father->right_child;
        father->right_child = root;
        return father;
    }//else father's left child isn't  NULL;
    while (father->left_child->left_child != NULL)
    {
        father = father->left_child;
    }
    // father->left_child is the node to replace with
    // take care of it's left
    AVLTree<T> *temp = father->left_child;
    temp->left_child = root->left_child;
    root->left_child = NULL;
    // take care of it's right
    AVLTree<T> *temp2 = temp;
    temp->right_child = root->right_child;
    root->right_child = temp2->right_child;
    //take care of root's pointer
    father->left_child = root;
    return temp;
}

template <typename T>
AVLTree<T> *deleteNode(AVLTree<T> *tree, int key)
{
    if(tree == NULL){
        return NULL;
    }
    if(key < tree->key){
        tree->left_child = deleteNode(tree->left_child, key);
        tree->left_child = balanceTree(tree->left_child);
    } else if( tree->key < key){
        tree->right_child = deleteNode(tree->right_child ,key);
        tree->right_child = balanceTree(tree->right_child);
    } else {
        // we found the node with the correct key
        if(tree->left_child == NULL || tree->right_child == NULL){
            AVLTree<T> *temp = tree->left_child ? tree->left_child : tree->right_child;
            if(temp == NULL){// if both of tree's children are NULL then:
                delete tree;
                return NULL;
            } else {// if only one of tree's children are NULL then secound one 
                    // is a sub-tree of one node.
                if(tree->right_child == NULL){
                    tree->left_child = NULL;
                } else{
                    tree->right_child =NULL;
                }
                delete tree;
                return temp;
            }
        } else {
            // if bothe childrern are not NULL then:
            tree = trickleDown(tree);
            tree = deleteNode(tree);
        }
    }
    if(tree->left_child == NULL && tree->right_child == NULL){
        tree->height = 0;
        tree->heap = 1;
    }
    tree = balanceTree(tree);
    return tree;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    AVLTree<T> *searchMax = this->right_child;
    while(searchMax->right_child != NULL){
        searchMax = searchMax->right_child;
    }
    int maxIndex = searchMax->key;
    AVLTree<T> *temp = this;
    for(int i = 0; i < maxIndex + 1; i++){
        temp = deleteNode(temp, i);
    }
}

template <typename T>
AVLTree<T> *AVLTree<T>::treeDeleteNode(int key)
{
    return deleteNode(this, key);
}

//________________ VIP section ________________

template <typename T>
void AVLTree<T>::setVip(int key, bool isVip)
{
    if(!this->keyExists(key)){
        return;
    }
    if(key < this->key){
        this->left_child->setVip(key, isVip);
    } else if(this->key < key){
        this->right_child->setVip(key, isVip);
    } else {
        this->vip = isVip;
    }
    return;
}

template <typename T>
bool AVLTree<T>::isVip(int key)
{
    //assuming this key exists
    assert(this->keyExists(key));
    if(key < this->key){
        return this->left_child->isVip(key);
    } else if(this->key < key){
        return this->right_child->isVip(key);
    } else {
        return this->vip;
    }
}


