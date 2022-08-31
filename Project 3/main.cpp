/*
  Name: CJ Hess
  Date: 03/22/2022
  File: main.cpp
*/

#include <fstream>
#include <iostream>
#include <string>

#include "BinaryTree.hpp"

#define COUNT 10;

using namespace std;

int getTreeHeight(TreeNode* n) {
  if (n == nullptr) {
    return -1;
  }
  else {
    int lDepth = getTreeHeight(n->left);
    int rDepth = getTreeHeight(n->right);

    if (lDepth > rDepth) {
      return lDepth+1;
    }
    else {
      return rDepth+1;
    }
  }
}

void print2DTree(TreeNode* n, int space) {
  if (n == nullptr) {
    return;
  }

  space += COUNT;

  print2DTree(n->right, space);

  cout << endl;
  int i = COUNT;
  while (i < space) {
    cout << " ";
    i++;
  }

  cout << n->value << "\n";

  print2DTree(n->left, space);
}

void printTree(TreeNode* n) {
  print2DTree(n, 0);
}

int main(int argc, char *argv[]) {
  // argv[1] - input file
  // argv[2] - unbalanced or avl

  string fileName = argv[1];
  string insertMethod = argv[2];
  
  // Insert Section
  ifstream insertFile(fileName);
  int sizeOf;

  BinaryTree* bt = new BinaryTree();

  insertFile >> sizeOf;

  if (insertMethod == "avl") {
    while (!insertFile.eof()) {
      string data;
      insertFile >> data;
      bt->root = bt->insertAVL(bt->root, data);
    }
  }
  else {
    while (!insertFile.eof()) {
      string data;
      insertFile >> data;
      bt->root = bt->insertBinaryTree(bt->root, data);
    }
  }

  insertFile.close();
  cout << getTreeHeight(bt->root) << endl;
  printTree(bt->root);

  // Search Section
  ifstream searchFile(fileName);
  searchFile >> sizeOf;

  while (!searchFile.eof()) {
    string data;
    searchFile >> data;
    bool found = bt->searchValue(bt->root, data);
  }
  
  searchFile.close();
  
  delete bt;
  return 0;
}