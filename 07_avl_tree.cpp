#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct Node {
  int value, height;
  Node *left, *right;
};

int max(int a, int b) {
  return (a > b) ? a : b;
}

int getHeight(Node *root) {
  return (root) ? root->height : 0;
}

int getBalanceFactor(Node *root) {
  return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

int computeNewHeight(Node *root) {
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}

Node *rotationType(Node *x, const char *type) {
  Node *y, *z;

  if(strcmp(type, "left") == 0) {
    y = x->right;
    z = y->left;
    y->left = x;
    x->right = z;
  } else {
    y = x->left;
    z = y->right;
    y->right = x;
    x->left = z;
  }

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
  root->height = computeNewHeight(root);  
  int balanceFactorRoot = getBalanceFactor(root);
  int balanceFactorRight = getBalanceFactor(root->right);
  int balanceFactorLeft = getBalanceFactor(root->left);

  if(balanceFactorRoot > 1 && balanceFactorLeft >= 0) {
    return rotationType(root, "right");
  } else if(balanceFactorRoot > 1 && balanceFactorLeft < 0) {
    root->left = rotationType(root->left, "left");
    return rotationType(root, "right");
  } else if(balanceFactorRoot < -1 && balanceFactorRight <= 0) {
    return rotationType(root, "left");
  } else if(balanceFactorRoot < -1 && balanceFactorRight > 0) {
    root->right = rotationType(root->right, "right");
    return rotationType(root, "left");
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
  Node *curr = root;

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
      Node *temp = root->left ? root->left : root->right;
      if(!temp) {
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
        free(temp);
      } 
    } else {
      Node *temp = predecessor(root->left);
      root->value = temp->value;
      root->left = deleteNode(root->left, temp->value);
    }
  }

  return (root) ? rotation(root) : root;
}

void printInOrder(Node *root) {
  if(root) {
    printInOrder(root->left);
    printf("Height: %d, Value %d\n", root->height, root->value);
    printInOrder(root->right);
  }
}

void printAVL(Node *root) {
  printf("\nCurrent tree: \n");
  printInOrder(root);
  printf("\n\n");
}

int main() {
  Node *baseRoot = NULL;
  int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4, 1, 9, 25, 6, 30};

  for(int i = 0; i < 15; i++) {
    baseRoot = insertNode(baseRoot, toInsert[i]);
    printf("Added %d to the tree.", toInsert[i]);
    printAVL(baseRoot);
  }

  time_t t;
  srand((unsigned) time(&t));

  for(int i = 0; i < 15; i++) {
    bool deleted = false;

    while(!deleted) {
      int randomNumber = rand() % 31;

      for(int j = 0; j < 15; j++) {
        if(toInsert[j] == randomNumber) {
          printf("Removed %d from the tree.", randomNumber);
          baseRoot = deleteNode(baseRoot, randomNumber);
          printAVL(baseRoot);
          toInsert[j] = -1;
          deleted = true;
          break;
        }
      }
    }
  }
  
  return 0;
}