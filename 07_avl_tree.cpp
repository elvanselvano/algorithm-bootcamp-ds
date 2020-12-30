#include <stdio.h>
#include <stdlib.h>

// Teori: https://medium.com/@elvanselvano/avl-tree-perfectly-balanced-as-all-things-should-be-ca15a6d59ac5
struct Node {
  int value, height;
  Node *left, *right;
};

// mencari nilai maksimal dari dua angka
int max(int a, int b) {
  return (a > b) ? a : b;
}

// mendapatkan tinggi sebuah node
// jika NULL, heightnya adalah 0
int getHeight(Node *root) {
  return (root) ? root->height : 0;
}

// Balance Factor = H1 - H2
// H1 = tinggi anak kiri, H2 = tinggi anak kanan
// jika NULL, Balance Factornya adalah 0
int getBalanceFactor(Node *root) {
  return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

// mendapatkan tinggi baru sebuah node
// ketika ada insert atau delete (karena posisi bakal berubah)
// new height = nilai maksimal tinggi anak kiri dan kanan, ditambahin 1
int computeNewHeight(Node *root) {
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}

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
  root->height = computeNewHeight(root); // update tinggi root setelah insert/delete
  int BFRoot = getBalanceFactor(root); // balance factor root
  int BFRight = getBalanceFactor(root->right); // balance factor anak kanan
  int BFLeft = getBalanceFactor(root->left); // balance factor anak kiri

  // BFRoot > 1 = condong kiri
  // BFRoot < -1 = condong kanan
  if(BFRoot > 1 && BFLeft >= 0) {
    return rightRotate(root);
  } else if(BFRoot > 1 && BFLeft < 0) {
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