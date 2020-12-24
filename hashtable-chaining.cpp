#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max_element bukan menandakan panjang node
// dari sebuah linked list akan tetapi jumlah linked list 
// maksimal dalam sebuah hashtable
const int MAX_ELEMENT = 10;

struct Node {
  char name[255];
  Node *next;
  // terdapat 10 buah linked list dengan 10 head dan tail
} *head[MAX_ELEMENT], *tail[MAX_ELEMENT];

Node *createNode(const char *name) {
  Node *temp = (Node*)malloc(sizeof(Node));
  strcpy(temp->name, name);
  temp->next = NULL;
  return temp;
}

unsigned long djb2(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
    
  return hash % MAX_ELEMENT;
}

void insert(const char *str) {
  // 0 -> .. -> ..
  // 1 -> .. 
  // 2
  // 3 -> .. -> .. -> ..
  Node *temp = createNode(str);
  int index = djb2(str);

  if(!head[index]) { // cek apakah headnya kosong
    head[index] = tail[index] = temp;
  } else { // jika sudah terisi lakukan push tail
    tail[index]->next = temp;
    tail[index] = temp;
  }
}

void traverseLinkedList(int i) {
  Node *curr = head[i];

  while(curr) {
    printf("%s -> ", curr->name);
    curr = curr->next;
  }
}

void view() {
  for(int i = 0; i < MAX_ELEMENT; i++) {
    printf("Index %d: ", i);
    if(head[i]) { // jika ada head
      traverseLinkedList(i); // kita traverse
    } 
    puts("NULL");
  }
}

int main() {
  insert("romario");
  insert("admiralspoon");
  insert("kesya");
  insert("nich");
  insert("valencia");
  insert("laffpai");
  insert("kevice");
  view();
  return 0;
}