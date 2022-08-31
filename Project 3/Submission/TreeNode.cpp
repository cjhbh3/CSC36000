/*
  Name: CJ Hess
  Date: 03/16/2022
  File: TreeNode.cpp
*/

#include "TreeNode.hpp"

int getHeight(TreeNode* n) {
  if (n == nullptr) {
    return 0;
  }
  return n->height;
}

std::string getValue(TreeNode* n) {
  if (n == nullptr) {
    return "";
  }
  return n->value;
}