#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *left, *right;
};

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->left = temp->right = NULL;
  return temp;
}

Node *insertNode(Node *root, int value) {
  if(!root) { // root sekarang masih NULL
    return createNode(value); // buat nodenya
  } else if(value < root->value) { // masuk subtree kiri
    root->left = insertNode(root->left, value);
  } else if(value > root->value) { // masuk subtree kanan
    root->right = insertNode(root->right, value);
  }

  return root;
}

// mencari nilai terkecil di subtree kanan
Node *minValueNode(Node *root) { 
  Node *curr = root->right; // curr adalah parent di subtree kanan

  while(curr && curr->left) { 
    curr = curr->left; // traverse terus menerus ke kiri
  }

  return curr;
}

Node *deleteNode(Node *root, int value) {
  if(!root) { // yang mau didelete tidak ada
    return root;
  } else if(value < root->value) { // masuk subtree kiri
    root->left = deleteNode(root->left, value);
  } else if(value > root->value) { // masuk subtree kanan
    root->right = deleteNode(root->right, value);
  } else { // ketemu yang mau dihapus
    if(!root->left || !root->right) { // kasus 0 dan 1 anak
      // jika kiri null, kandidatnya kanan dan sebaliknya
      Node *newRoot = root->left ? root->left : root->right;
      free(root); // hapus root lama
      root = NULL;
      return newRoot;
    }

    // kasus 2 anak
    Node *inOrderSucessor = minValueNode(root); // nilai terkecil di subtree kanan
    root->value = inOrderSucessor->value; // copy valuenya
    root->right = deleteNode(root->right, inOrderSucessor->value); // hapus node pengganti
  }

  return root;
}

//                  15
//          10              23
//     8         12     18       27
// 15->left = insertNode(15->left, 13);
// 10->right = insertNode(10->right, 13);
// 12->right = insertNode(12->right, 13);
// if(!root), createNode(13)

bool searchNode(Node *root, int key) {
  if(root) {
    if(root->value == key) { // jika ketemu apa yang dicari
      return true;
    } else if(key < root->value) {
      return searchNode(root->left, key); // cari di subtree kiri
    } else if(key > root->value) {
      return searchNode(root->right, key); // cari di subtree kanan
    }
  }

  return false; // engga ketemu
}

void preOrder(Node *root) {
  if(root) {
    printf("%d ", root->value);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(Node *root) { // sorted
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
    // printf("Added %d to the tree.\n", toInsert[i]);
    inOrder(baseRoot);
    puts("");
  }

  for(int i = 0; i < 15; i++) {
    baseRoot = deleteNode(baseRoot, toInsert[i]);
    // printf("Removed %d from the tree.\n", toInsert[i]);
    inOrder(baseRoot);
    puts("");
  }

  return 0;
}
