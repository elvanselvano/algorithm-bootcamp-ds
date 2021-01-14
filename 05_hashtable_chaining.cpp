#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_BUCKETS = 5; // 5 linked lists

struct Node {
  char name[255];
  Node *next;
} *head[MAX_BUCKETS], *tail[MAX_BUCKETS];

Node *createNode(const char *name) {
  Node *temp = (Node*)malloc(sizeof(Node));
  strcpy(temp->name, name);
  temp->next = NULL;
  return temp;
}

unsigned long djb2(const char *str) {
  unsigned long hash = 5381;
  int c;
  // *str++ is going to the next address in memory, 
  // where the next char in the string is stored
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
    
  return hash % MAX_BUCKETS;
}

void insert(const char *str) { // similar to pushTail()
  Node *temp = createNode(str);
  int index = djb2(str); // use djb2 hashing algorithm

  if(!head[index]) { // if head is empty
    head[index] = tail[index] = temp;
  } else { // else push tail
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
  for(int i = 0; i < MAX_BUCKETS; i++) {
    printf("Index %d: ", i);
    if(head[i]) { // if head exists
      traverseLinkedList(i);
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
  insert("darnell");
  view();
  return 0;
}