#include "../include/AVLTree.h"
#include <algorithm>
#include <iostream>

// Função para obter a altura de um nó
int AVLTree::height(AVLNode *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Função auxiliar para atualizar a altura de um nó
void AVLTree::updateHeight(AVLNode *node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
}

// Função para realizar rotação à direita
AVLNode* AVLTree::rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza alturas
    updateHeight(y);
    updateHeight(x);

    // Retorna nova raiz
    return x;
}

// Função para realizar rotação à esquerda
AVLNode* AVLTree::leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza alturas
    updateHeight(x);
    updateHeight(y);

    // Retorna nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int AVLTree::getBalance(AVLNode *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Função para inserir um nó e balancear a árvore
AVLNode* AVLTree::insert(AVLNode* node, int key) {
    // 1. Realiza a inserção normal de uma BST
    if (node == nullptr)
        return(new AVLNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Chaves duplicadas não são permitidas
        return node;

    // 2. Atualiza a altura do nó ancestral
    updateHeight(node);

    // 3. Obtém o fator de balanceamento para verificar se este nó se tornou desbalanceado
    int balance = getBalance(node);

    // 4. Se o nó está desbalanceado, então há 4 casos

    // Caso Esquerda-Esquerda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Direita-Direita
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Esquerda-Direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* retorna o ponteiro do nó (inalterado) */
    return node;
}

// Função para inserir um nó (pública)
void AVLTree::insert(int key) {
    root = insert(root, key);
}

// Função auxiliar para realizar travessia em ordem
void AVLTree::preOrder(AVLNode *root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Função para realizar travessia em ordem (pública)
void AVLTree::preOrder() {
    preOrder(root);
}

AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;

    /* loop para encontrar a folha mais à esquerda */
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Função para remover um nó da árvore AVL e balancear a árvore
AVLNode* AVLTree::deleteNode(AVLNode* root, int key) {
    // 1. Realizar a remoção padrão de BST
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // nó com apenas um filho ou sem filho
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVLNode *temp = root->left ? root->left : root->right;

            // Sem filho
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // Um filho
                *root = *temp; // Copia o conteúdo do filho não vazio
            delete temp;
        } else {
            // nó com dois filhos: pegue o sucessor inorder (menor na subárvore direita)
            AVLNode* temp = minValueNode(root->right);

            // Copia o valor do sucessor inorder para este nó
            root->key = temp->key;

            // Deleta o sucessor inorder
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Se a árvore tinha apenas um nó
    if (root == nullptr)
      return root;

    // 2. Atualiza a altura do nó atual
    updateHeight(root);

    // 3. Verifica o balanceamento deste nó ancestral
    int balance = getBalance(root);

    // Se este nó se tornar desbalanceado, então há 4 casos

    // Esquerda Esquerda
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Esquerda Direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Direita Direita
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Direita Esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Função pública para remover uma chave
void AVLTree::deleteKey(int key) {
    root = deleteNode(root, key);
}