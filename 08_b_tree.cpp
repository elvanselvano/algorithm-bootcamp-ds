#include <stdio.h>
#include <stdlib.h>
#define MAX 2 // maksimal key sebuah node
#define MIN 1 // minimal key sebuah node didapat dari max/2 atau max/2+1 (dibulatkan).

struct Node {
  int key[MAX + 1]; // array berisi nilai-nilai dalam sebuah node
  int ctr; // jumlah key sekarang, menentukan split atau tidak
  Node *child[MAX + 1]; // pointer ke anak dari sebuah node
} *root; // global root

Node *createNode(int key, Node *child) {
  Node *newNode = (Node*)malloc(sizeof(Node)); // alokasi memory
  newNode->key[1] = key; // index 1 agar sesuai dengan counter
  newNode->ctr = 1; // jumlah key mula2 dari sebuah node
  newNode->child[0] = root; // menunjuk ke global root
  newNode->child[1] = child; // menampung childnya, bisa null kalau node baru
  return newNode;
}

void insertKey(int key, int targetPosition, Node *leaf, Node *child) {
  int currentPosition = leaf->ctr; // loop dari belakang

  // Jika kita ingin mengisi 55 ke node berisi 50 80 90
  // targetPositionnya adalah 1
  while(currentPosition > targetPosition) {
    // 50 80 90 buat menjadi 50 55 80 90 dengan geser2 nilai
    leaf->key[currentPosition+1] = leaf->key[currentPosition]; // geser nilai
    leaf->child[currentPosition+1] = leaf->child[currentPosition]; // geser anak
    currentPosition--; // loop berlanjut sampai current key == target position
  }

  leaf->key[currentPosition+1] = key; // assign key di target position
  leaf->child[currentPosition+1] = child; // assign child di target position
  leaf->ctr++; // jumlah anak bertambah
}

void split(int key, int *potKey, int pos, Node *node, Node *child, Node **newNode) {
  int median = (pos > MIN) ? MIN + 1 : MIN; // menentukan median suatu node
  int j = median + 1; // index untuk looping dari akhir
  *newNode = (Node*)malloc(sizeof(Node)); // buat sebuah node baru

  while (j <= MAX) { // ngesplit, key yang kiri menjadi anak yang kiri
    (*newNode)->key[j - median] = node->key[j];
    (*newNode)->child[j - median] = node->child[j];
    j++;
  }

  node->ctr = median; // kita membagi 2 array
  // yang array kiri memiliki elemen sebanyak median

  (*newNode)->ctr = MAX - median; // jika kita membagi 2 array, array kanan memiliki max - median

  (pos <= MIN) ? insertKey(key, pos, node, child) : insertKey(key, pos - median, *newNode, child);  // max-median karena jika function split ini dipanggil, array ini sudah pasti lebih besar 1 max

  *potKey = node->key[node->ctr];  // assign nilai median di potKey, diingat, potKey lah yang akan dipassing kembali di insertion
  (*newNode)->child[0] = node->child[node->ctr]; // elemen paling kiri dari array kanan, mengambil anak paling kanan dari array kiri
  node->ctr--; // karena ada 1 elemen yang dilempar ke atas, maka jumlah dikurang 1
}

int setKeyNode(int key, int *potKey, Node *node, Node **child) {
  int pos;
  if (!node) { // sudah di root/leaf
    *potKey = key;
    *child = NULL;
    return 1;
  }

  if (key < node->key[1]) {
    pos = 0; // pasti leaf paling kiri  
  } else {
    pos = node->ctr; // mencari leaf yang tepat
    while (key < node->key[pos] && pos > 1) {
      pos--;
    }
    if (key == node->key[pos]) {
      return 0; // prompt udah ada
    }
  }

  if (setKeyNode(key, potKey, node->child[pos], child)) {
    if (node->ctr < MAX) {
      insertKey(*potKey, pos, node, *child); // ga perlu split == ga perlu malloc
    }
    else {
      split(*potKey, potKey, pos, node, *child, child);
      return 1;
    }
  }

  return 0; // buat rekursi ke leaf
}

void insertion(int key) {
  int keyCopy; // menyimpan nilai key di dalam keycopy
  Node *child; // menampung child dari node

  // setKeyNode return 1: b tree kosong atau ketika split, kita ingin membuat node di atasnya
  // setKeyNode return 0: insert dilakukan tanpa split atau split terjadi namun tidak membutuhkan malloc
  if (setKeyNode(key, &keyCopy, root, &child) == 1) {
    root = createNode(keyCopy, child); // root berubah menjadi root baru
  }
}

void inorder(Node *root) {
  int i;
  if(root) {
    for(i = 0; i < root->ctr; i++) {
      inorder(root->child[i]);
      printf("%d ", root->key[i+1]);
    }
    inorder(root->child[i]);
  }
}

int main() {
  insertion(15);
  insertion(12);
  insertion(13);
  insertion(24);
  insertion(18);
  inorder(root);
  return 0;
}