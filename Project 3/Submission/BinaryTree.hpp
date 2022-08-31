/*
  Name: CJ Hess
  Date: 03/16/2022
  File: BinaryTree.hpp
*/

#include <iostream>
#include "TreeNode.hpp"

class BinaryTree {
  public:
    TreeNode* root;

    // Default constructor
    BinaryTree(): root(new TreeNode()) {}
    
    // insert function that will rebalance to AVL standards
    TreeNode* insertAVL(TreeNode* n, std::string data);

    // insert function for unbalanced Binary Tree
    TreeNode* insertBinaryTree(TreeNode* n , std::string data);

    // Perform right rotation for AVL Balance
    TreeNode* rotateRight(TreeNode* n);
    
    // Perform left rotation for AVL Balance
    TreeNode* rotateLeft(TreeNode* n);

    // Find data in tree
    bool searchValue(TreeNode* n, std::string data);
    
    friend int max(int a, int b);

    friend int getBalance(TreeNode* n);
};