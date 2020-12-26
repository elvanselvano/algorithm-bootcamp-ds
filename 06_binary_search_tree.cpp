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
  if (!root) { // jika tidak ada root
    return createNode(value);
  } else if(value < root->value) { // masuk subtree kiri
    root->left = insertNode(root->left, value); // traverse ke subtree kiri
  } else if(value > root->value) { // masuk subtree kanan
    root->right = insertNode(root->right, value); // traverse ke subtree kanan
  }

  return root;
}

// mencari minimum value dalam sebuah subtree
Node *minValueNode(Node *root) {
  Node *curr = root;

  // traverse terus ke kiri sampai sukses
  while(curr && curr->left) {
    curr = curr->left;
  }

  return curr;
}

Node *deleteNode(Node *root, int value) {
  if(!root) { // yg kita mw delete tidak ada
    return root;
  } else if(value < root->value) { // traverse kiri
    // sambil initialize link karna nanti bakal ada perubahan link
    root->left = deleteNode(root->left, value);
  } else if(value > root->value) { // traverse kanan
    // sambil initialize link karna nanti bakal ada perubahan link
    root->right = deleteNode(root->right, value);
  } else if(value == root->value) { // ketemu apa yang mau kita delete

    // kasus 0 anak dan 1 anak
    if(!root->left) { // jika kiri null, kandidat kanan
      Node *temp = root->right; 
      free(root);
      return temp;
    } else if(!root->right) { // jika kanan null, kandidat kiri
      Node *temp = root->left; // kandidat pengganti anak kiri
      free(root); // hapus rootnya
      return temp; // return anak kiri
    }

    // Initial Tree
    //    10
    //  4   12  

    // delete 10
    // temp = 12
    // root->value = temp->value

    // After Delete
    //    12
    //  4    

    // cari temp->value di subtree kanan
    // root->right = deleteNode(root->right, temp->value);

    // jika kedua if di atas tidak dijalankan, artinya dia masuk kasus 2 anak

    // cari nilai terkecil di subtree kanan (pembuktian tonton di recording)
    Node *temp = minValueNode(root->right);
    root->value = temp->value; // copy valuenya dulu sebelum dihapus
    // ketika kita ingin hapus sebuah node 2 anak, bukan node itu yg dihapus tapi penggantinya
    root->right = deleteNode(root->right, temp->value); // bakal hapus nilai dari node terkecil di subtree kanan (hapus penggantinya)
  }

  return root;
}

// tidak perlu initialize link, cukup rekursi
bool searchNode(Node *root, int key) {
  if(root) { // selama root bukan null
    if(root->value == key) { // jika nilai root adalah yang dicari
      return true;
    } else if(key < root->value) { // masuk subtree kiri
      return searchNode(root->left, key);
    } else if(key > root->value) { // masuk subtree kanan
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

void postOrder(Node *root) {
  if(root) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->value);
  }
}

void printAll(Node *root) { // inorder: print sorted
  if(root) {
    printAll(root->left);
    printf("%d ", root->value);
    printAll(root->right);
  }
}

int main() {
  Node *baseRoot = NULL; // init null
  baseRoot = insertNode(baseRoot, 15);
  baseRoot = insertNode(baseRoot, 20); // add new item
  baseRoot = insertNode(baseRoot, 10); // ...
  baseRoot = insertNode(baseRoot, 7);
  printAll(baseRoot); puts("");
  baseRoot = deleteNode(baseRoot, 7);
  printAll(baseRoot); puts("");
  baseRoot = deleteNode(baseRoot, 10);
  printAll(baseRoot); puts("");
  baseRoot = deleteNode(baseRoot, 15);
  printAll(baseRoot); puts("");
  baseRoot = deleteNode(baseRoot, 20);
  printAll(baseRoot); puts("");
  return 0;
}