#include <stdio.h>
#include <stdlib.h>

// Reading material: https://medium.com/@elvanselvano/avl-tree-perfectly-balanced-as-all-things-should-be-ca15a6d59ac5
struct Node {
  int value, height;
  Node *left, *right;
};

int max(int a, int b) { // find maximum between 2 numbers
  return (a > b) ? a : b;
}

int getHeight(Node *root) { // find height of a root
  return (root) ? root->height : 0;
}

// BF = height of left child - height of right child
int getBalanceFactor(Node *root) { 
  return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

// find new height of a root during insertion or deletion
// height = max between left child or right child, plus 1
int computeNewHeight(Node *root) {
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// Rotation: https://drive.google.com/drive/folders/1_dRl8kpv5TSJfLvUaGAuoyij0ZreyLSu?usp=sharing
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *z = y->left;
  y->left = x;
  x->right = z;
  x->height = computeNewHeight(x);
  y->height = computeNewHeight(y);
  return y;
}

Node *rightRotate(Node *x) {
  Node *y = x->left;
  Node *z = y->right;
  y->right = x;
  x->left = z;
  x->height = computeNewHeight(x);
  y->height = computeNewHeight(y);
  return y;
}

Node *createNode(int value) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->value = value;
  newNode->height = 1;
  newNode->left = newNode->right = NULL;
  return newNode;
}

Node *rotation(Node *root) {
  root->height = computeNewHeight(root); // get new height after insertion/deletion
  int BFRoot = getBalanceFactor(root); // balance factor root
  int BFRight = getBalanceFactor(root->right); // balance factor right child
  int BFLeft = getBalanceFactor(root->left); // balance factor left child

  if(BFRoot > 1 && BFLeft >= 0) { // BFRoot > 1 = left child unbalanced
    return rightRotate(root);
  } else if(BFRoot > 1 && BFLeft < 0) { // BFRoot < -1 = right child unbalanced
    root->left = leftRotate(root->left);
    return rightRotate(root);
  } else if(BFRoot < -1 && BFRight <= 0) {
    return leftRotate(root);
  } else if(BFRoot < -1 && BFRight > 0) {
    root->right = rightRotate(root->right);
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

  return rotation(root);
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
      free(root);
      root = NULL;
      return newRoot;
    }
      
    Node *temp = predecessor(root);
    root->value = temp->value;
    root->left = deleteNode(root->left, temp->value);
  }

  return (root) ? rotation(root) : root;
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf("Height: %d, Value %d\n", root->height, root->value);
    inOrder(root->right);
  }
}

int main() {
  Node *baseRoot = NULL;
  int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4};

  for(int i = 0; i < 9; i++) {
    baseRoot = insertNode(baseRoot, toInsert[i]);
    printf("\nAdded %d to the tree.\n", toInsert[i]);
    inOrder(baseRoot);
  }

  for(int i = 0; i < 9; i++) {
    baseRoot = deleteNode(baseRoot, toInsert[i]);
    printf("\nRemoved %d from the tree.\n", toInsert[i]);
    inOrder(baseRoot);
  }
  
  return 0;
}