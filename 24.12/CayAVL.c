#include <stdio.h>
#include <stdlib.h>


struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};


int height(struct Node *n) {
    return (n == NULL) ? 0 : n->height;
}


int getBalance(struct Node *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}


struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node* rotateRight(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;


    x->right = y;
    y->left = T2;


    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}


struct Node* rotateLeft(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;


    y->left = x;
    x->right = T2;


    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}


struct Node* insert(struct Node* node, int key) {

    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;


    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));


    int balance = getBalance(node);


    if (balance > 1 && key < node->left->key)
        return rotateRight(node);


    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);


    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }


    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


void inOrder(struct Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}


void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


void postOrder(struct Node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

int main() {
    struct Node *root = NULL;
    int inputArray[] = {10, 20, 30, 40, 50, 25};
    int size = sizeof(inputArray) / sizeof(inputArray[0]);

    printf("Thêm các phần tử vào cây AVL:\n");
    for (int i = 0; i < size; i++) {
        root = insert(root, inputArray[i]);
        printf("Cây sau khi thêm %d:\n", inputArray[i]);
        printf("In-order: ");
        inOrder(root);
        printf("\nPre-order: ");
        preOrder(root);
        printf("\nPost-order: ");
        postOrder(root);
        printf("\n\n");
    }

    return 0;
}
