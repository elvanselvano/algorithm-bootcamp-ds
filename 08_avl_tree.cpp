#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value, height, bf;
  Node *left, *right;
};

int max(int a, int b) { // maximum between 2 numbers
  return (a > b) ? a : b;
}

int getHeight(Node *root) { // height of a node
  return (root) ? root->height : 0;
}

int getBalanceFactor(Node *root) {  // height of left child - height of right child
  return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

int computeNewHeight(Node *root) { // new height after insertion or deletion
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}

Node *createNode(int value) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->value = value;
  newNode->height = 1;
  newNode->bf = 0;
  newNode->left = newNode->right = NULL;
  return newNode;
}

Node *updateNode(Node *root) {
  root->height = computeNewHeight(root);
  root->bf = getBalanceFactor(root);
  return root;
}

// Rotation: https://drive.google.com/drive/folders/1_dRl8kpv5TSJfLvUaGAuoyij0ZreyLSu?usp=sharing
Node *leftRotate(Node *root) {
  Node *pivot = root->right;
  Node *temp = pivot->left;
  pivot->left = root;
  root->right = temp;
  root = updateNode(root);
  pivot = updateNode(pivot);
  return pivot;
}

Node *rightRotate(Node *root) {
  Node *pivot = root->left;
  Node *temp = pivot->right;
  pivot->right = root;
  root->left = temp;
  root = updateNode(root);
  pivot = updateNode(pivot);
  return pivot;
}

Node *rotation(Node *root) {
  if(root->bf > 1 && root->left->bf >= 0) { // bf > 1 = left child unbalanced
    return rightRotate(root);
  } else if(root->bf > 1 && root->left->bf < 0) {
    root->left = leftRotate(root->left); // double rotation
    return rightRotate(root);
  } else if(root->bf < -1 && root->right->bf <= 0) { // bf < -1 = right child unbalanced
    return leftRotate(root);
  } else if(root->bf < - 1 && root->right->bf > 0) {
    root->right = rightRotate(root->right); // double rotation
    return leftRotate(root);
  }

  return root;
}

Node *insertNode(Node *root, int value) {
  if(!root) {
    return createNode(value);
  } else if(value < root->value) {
    root->left = insertNode(root->left, value);
  } else if(value > root->value) {
    root->right = insertNode(root->right, value);
  }

  return rotation(updateNode(root));
}

Node *predecessor(Node *root) {
  Node *curr = root->left;

  while(curr->right) {
    curr = curr->right;
  }

  return curr;
}

Node *deleteNode(Node *root, int value) {
  if(!root) {
    return root;
  } else if(value < root->value) {
    root->left = deleteNode(root->left, value);
  } else if(value > root->value) {
    root->right = deleteNode(root->right, value);
  } else {
    if(!root->left || !root->right) {
      Node *newRoot = root->left ? root->left : root->right;
      root->left = root->right = NULL;
      free(root);
      root = NULL;
      return newRoot;
    }
      
    Node *inOrderPredecessor = predecessor(root);
    root->value = inOrderPredecessor->value;
    root->left = deleteNode(root->left, inOrderPredecessor->value);
  }

  return rotation(updateNode(root));
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf("| %-3d | %4d   | %7d        |\n", root->value, root->height, root->bf);
    inOrder(root->right);
  }
}

int main() {
  Node *baseRoot = NULL;
  int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4};

  for(int i = 0; i < 9; i++) {
    baseRoot = insertNode(baseRoot, toInsert[i]);
    printf("\nAdded %d to the tree.\n", toInsert[i]);
    printf("| %-3s | %-5s | %-14s |\n", "Key", "Height", "Balance Factor");
    inOrder(baseRoot); getchar();
  }

  for(int i = 0; i < 9; i++) {
    baseRoot = deleteNode(baseRoot, toInsert[i]);
    printf("\nRemoved %d from the tree.\n", toInsert[i]);
    printf("| %-3s | %-5s | %-14s |\n", "Key", "Height", "Balance Factor");
    inOrder(baseRoot); getchar();
  }
  
  return 0;
}