#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *left, *right; // left and right child
};

Node *createNode(int value) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->value = value;
  newNode->left = newNode->right = NULL;
  return newNode;
}

//                  15
//          10              23
//     8         12     18       27

// 15->left = insertNode(15->left, 13);
// insertNode(10->right, 13);
// insertNode(12->right, 13);
// createNode(13) // stop recursion
// 12->right = 13
// 10->right->right = 13
// 15->left->right->right = 13

Node *insertNode(Node *root, int value) {
  if(!root) { // empty node
    return createNode(value);
  } else if(value < root->value) { // enter left subtree
    root->left = insertNode(root->left, value);
  } else if(value > root->value) { // enter right subtree
    root->right = insertNode(root->right, value);
  }

  return root;
}

Node *inOrderSucessor(Node *root) { // minimum value in right subtree
  Node *curr = root->right; // root of right subtree

  while(curr && curr->left) { 
    curr = curr->left; // find minimum value by traversing left
  }

  return curr;
}

Node *inOrderPredecessor(Node *root) { // maximum value in left subtree
  Node *curr = root->left; // root of left subtree

  while(curr && curr->right) { 
    curr = curr->right; // find maximum value by traversing right
  }

  return curr;
}

Node *deleteNode(Node *root, int value) {
  if(!root) { // empty tree
    return root; // return unchanged tree
  } else if(value < root->value) { // enter left subtree
    root->left = deleteNode(root->left, value);
  } else if(value > root->value) { // enter right subtree
    root->right = deleteNode(root->right, value);
  } else {
    if(!root->left || !root->right) { // 0 or 1 child
      // if left child is null, new root is right child
      // if right child is null, new root is left child
      Node *newRoot = root->left ? root->left : root->right;
      root->left = root->right = NULL;
      free(root); // remove old root
      root = NULL;
      return newRoot;
    }

    // 2 children using inOrderSucessor
    Node *newRoot = inOrderSucessor(root);
    root->value = newRoot->value; // copy value
    root->right = deleteNode(root->right, newRoot->value); // remove the inorder successor

    // 2 children using inOrderPredecessor
    // Node *newRoot = inOrderPredecessor(root);
    // root->value = newRoot->value; // copy value
    // root->left = deleteNode(root->left, newRoot->value); // remove the inorder predecessor
  }

  return root;
}

bool searchNode(Node *root, int key) {
  if(root) {
    if(root->value == key) {
      return true;
    } else if(key < root->value) {
      return searchNode(root->left, key); 
    } else if(key > root->value) {
      return searchNode(root->right, key);
    }
  }

  return false;
}

void preOrder(Node *root) {
  if(root) {
    printf("%d ", root->value);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf("%d ", root->value);
    inOrder(root->right);
  }
}

void postOrder(Node *root) {
  if(root) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->value);
  }
}

int main() {
  Node *baseRoot = NULL;
  int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4, 1, 9, 25, 6, 30, 31};

  for(int i = 0; i < 15; i++) {
    baseRoot = insertNode(baseRoot, toInsert[i]);
    printf("Added %d to the tree.\n", toInsert[i]);
    inOrder(baseRoot);
    puts("");
  }

  for(int i = 0; i < 15; i++) {
    baseRoot = deleteNode(baseRoot, toInsert[i]);
    printf("Removed %d from the tree.\n", toInsert[i]);
    inOrder(baseRoot);
    puts("");
  }

  return 0;
}
