#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_ELEMENT = 10;

struct Node {
  char name[255];
  Node *next;
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
  int index = djb2(str);

  if(head[index]) { // cek apakah dia sudah terisi
    Node *temp = createNode(str);
    tail[index]->next = temp;
    tail[index] = temp;
  } else { // cek apakah dia belum terisi
    head[index] = tail[index] = createNode(str);
  }
}

void view() {
  for(int i = 0; i < MAX_ELEMENT; i++) {
    printf("%d ", i);
    if(head[i]) {
      Node *curr = head[i];
      while(curr) {
        printf("%s -> ", curr->name);
        curr = curr->next;
      }
    }
    puts("");
  }
}

int main() {
  insert("romario");
  insert("admiralspoon");
  insert("kesya");
  insert("nich");
  insert("valencia");
  view();
  return 0;
}