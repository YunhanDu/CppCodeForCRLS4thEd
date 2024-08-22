

// author: Claude Du
#include "TreeNode.h"
#include "AVLTree.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>


int main() {
    // Test BST
    AVLTree<int> bst;
    bst.TreeInsert(11);    
    bst.TreeInsert(8);
    bst.TreeInsert(9);
    bst.TreeInsert(10);
    bst.TreeInsert(12);
    bst.TreeInsert(13);
    bst.TreeInsert(5);
    bst.TreeInsert(3);
    bst.TreeInsert(1);
    bst.TreeInsert(12);
    bst.TreeInsert(0);
    bst.TreeInsert(4);
    bst.TreeInsert(7);   
    bst.TreeInsert(6);

    std::cout << "The size of Avl tree is " << bst.size() << "\n";
    bst.Display();
    std::cout << "A node with val 0 will be deleteded, so that case 3, left-left, will be satisfied at the first iteration." 	 << "\n";
    std::cout << "Then it will satisfy case 2, Right-left, at the second iteration." << "\n";
    bst.TreeDeletion(0);
    std::cout << "The size of Avl tree is " << bst.size() << "\n";
    bst.Display();    
}