

// author: Claude Du
#include "RedBlackTree.h"
#include <iostream>
int main()
{
    RBTree<int> rbTree;
    RBNode<int>* node8 = rbTree.RBInsert(8);
    RBNode<int>* node12 = rbTree.RBInsert(12);
    rbTree.RBInsert(5);
    rbTree.RBInsert(3);
    rbTree.RBInsert(7);
    rbTree.RBInsert(13);
    rbTree.RBInsert(10);
    rbTree.RBInsert(11);
    rbTree.RBInsert(9);
    rbTree.RBInsert(16);
    rbTree.Display();
    rbTree.RBDeletion(node12);
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "The node with value 12 has been deleted" << "\n";
    rbTree.Display();
    rbTree.RBDeletion(node8);
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "The node with value 8 has been deleted" << "\n";
    rbTree.Display();
}

