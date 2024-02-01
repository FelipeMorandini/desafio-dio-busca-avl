#include "../include/AVLTree.h"
#include <iostream>

int main() {
    AVLTree tree;

    std::cout << "Inserindo elementos na árvore AVL:\n";
    tree.insert(9);
    tree.insert(5);
    tree.insert(10);
    tree.insert(0);
    tree.insert(6);
    tree.insert(11);
    tree.insert(-1);
    tree.insert(1);
    tree.insert(2);

    std::cout << "Travessia em pré-ordem da árvore AVL formada:\n";
    tree.preOrder();
    std::cout << "\n";

    std::cout << "Removendo 10 e depois 6...\n";
    tree.deleteKey(10);
    tree.preOrder();
    std::cout << "\n";

    tree.deleteKey(6);
    std::cout << "Travessia em pré-ordem após remoções:\n";
    tree.preOrder();
    std::cout << "\n";

    return 0;
}