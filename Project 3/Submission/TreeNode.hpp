/*
  Name: CJ Hess
  Date: 03/16/2022
  File: TreeNode.hpp
*/

#include <iostream>


class TreeNode {
  public:
    std::string value;
    int height;
    TreeNode* left;
    TreeNode* right;

    // Default constructor
    TreeNode(): value(""), height(0), left(nullptr), right(nullptr) {}

    // Constructor for new data
    TreeNode(std::string data): value(data), height(1), left(nullptr), right(nullptr) {}
    
    // Copy constructor
    TreeNode(TreeNode* node): value(node->value), height(node->height), left(node->left), right(node->right) {}
    
    friend int getHeight(TreeNode* n);

    friend std::string getValue(TreeNode* n);

    
};