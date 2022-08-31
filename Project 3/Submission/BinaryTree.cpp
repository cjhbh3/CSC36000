/*
  Name: CJ Hess
  Date: 03/16/2022
  File: BinaryTree.cpp
*/

#include "BinaryTree.hpp"
#include <iostream>

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Get balance factor, to check if we need to apply AVL standards
int getBalance(TreeNode* n) {
  if (n == nullptr) {
    return 0;
  }
  return getHeight(n->left) - getHeight(n->right);
}

// Insert into tree, then check balance, make necessary rotations
TreeNode* BinaryTree::insertAVL(TreeNode* n, std::string data) {
  if (n == nullptr) {
    n = new TreeNode(data);
    return n;
  }

  if (data < n->value) {
    n->left = insertAVL(n->left, data);
  }
  else if (data > n->value) {
    n->right = insertAVL(n->right, data);
  }
  else {
    return n;
  }

  n->height = 1 + max(getHeight(n->left), getHeight(n->right));

  int balance = getBalance(n);

  if (balance > 1 && data < n->left->value)
		return rotateRight(n);

	// Right Right Case
	if (balance < -1 && data > n->right->value)
		return rotateLeft(n);

	// Left Right Case
	if (balance > 1 && data > n->left->value)
	{
		n->left = rotateLeft(n->left);
		return rotateRight(n);
	}

	// Right Left Case
	if (balance < -1 && data < n->right->value)
	{
		n->right = rotateRight(n->right);
		return rotateLeft(n);
	}

  return n;
}

// Insert into tree, unbalanced 
TreeNode* BinaryTree::insertBinaryTree(TreeNode* n,std::string data) {
  if (n == nullptr) {
    n = new TreeNode(data);
    return n;
  }

  if (data < n->value) {
    n->left = insertBinaryTree(n->left, data);
  }
  else if (data > n->value) {
    n->right = insertBinaryTree(n->right, data);
  }

  n->height = 1 + max(getHeight(n->left), getHeight(n->right));

  return n;
}

// Perform a left rotation
TreeNode* BinaryTree::rotateLeft(TreeNode* n) {
  TreeNode* a = n->right;
  TreeNode* b = a->left;

  a->left = n;
  n->right = b;

  n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
  a->height = max(getHeight(a->left), getHeight(a->right)) + 1;

  return a;
}

// Perform a right rotation
TreeNode* BinaryTree::rotateRight(TreeNode* n) {
  TreeNode* a = n->left;
  TreeNode* b = a->right;

  a->right = n;
  n->left = b;

  n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
  a->height = max(getHeight(a->left), getHeight(a->right)) + 1;

  return a;
}

bool BinaryTree::searchValue(TreeNode* n, std::string data) {
  if (n == nullptr) {
    return false;
  }

  if (n->value == data) {
    return true;
  }
  else if (n->value < data) {
    return searchValue(n->right, data);
  }
  else if (n->value > data) {
    return searchValue(n->left, data);
  }
}