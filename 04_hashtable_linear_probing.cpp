#include <stdio.h>
#include <string.h>

const int MAX_ELEMENT = 5;
const int MAX_LENGTH = 255;
char HASHTABLES[MAX_ELEMENT][MAX_LENGTH]; 

int hash(const char *str) { // hash function ascii sum
  int sum = 0;

  for(int i = 0; str[i] != '\0'; i++) {
    sum += str[i] - '0';
  }

  return sum % MAX_ELEMENT; // avoid out of bounds
}

void linearProbing(int idx, const char *str) {
  for(int i = (idx+1) % MAX_ELEMENT; i != idx; i = (i+1) % MAX_ELEMENT) {
    if(!HASHTABLES[i][0]) { // find empty slot from idx+1 to idx-1
      strcpy(HASHTABLES[i], str);
      return;
    }
  }

  puts("Table is full!");
}

void insert(const char *str) {
  int idx = hash(str); // hash the string to get the index

  if(!HASHTABLES[idx][0]) { // if empty
    strcpy(HASHTABLES[idx], str);
  } else { // else do linear probing
    linearProbing(idx, str);
  }
}

void view() {
  for(int i = 0; i < MAX_ELEMENT; i++) {
    printf("%d -> %s\n", i, HASHTABLES[i]);
  }
}

int main() {
  insert("romario");
  insert("admiralspoon");
  insert("kesya");
  insert("nich");
  insert("valencia");
  // insert("laffpai");
  view();
  return 0;
}