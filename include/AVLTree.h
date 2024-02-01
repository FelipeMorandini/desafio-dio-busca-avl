#ifndef AVL_TREE_H
#define AVL_TREE_H

class AVLNode {
public:
    int key;
    AVLNode *left, *right;
    int height;

    AVLNode(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    AVLNode* insert(AVLNode* node, int key);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* deleteNode(AVLNode* node, int key);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    int getBalance(AVLNode* N);
    int height(AVLNode* N);
    void preOrder(AVLNode* root);
    void updateHeight(AVLNode* node);

public:
    AVLTree() : root(nullptr) {}
    void insert(int key);
    void deleteKey(int key);
    void preOrder();
};

#endif