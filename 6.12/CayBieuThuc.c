#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    char value;
    struct Node *left, *right;
} Node;

// Tạo một node mới
Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Kiểm tra xem một ký tự có phải là toán tử không
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Hàm dựng cây từ biểu thức hậu tố
Node* constructTree(char postfix[]) {
    Node* stack[100];
    int top = -1; // Con trỏ đỉnh của stack

    for (int i = 0; i < strlen(postfix); i++) {
        char c = postfix[i];
        if (isOperator(c)) {
            Node* node = createNode(c);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        } else {
            stack[++top] = createNode(c); // Toán hạng
        }
    }
    return stack[top]; // Gốc cây
}

// Duyệt cây theo thứ tự trước (Pre-order)
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%c ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Duyệt cây theo thứ tự giữa (In-order)
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%c ", root->value);
        inOrder(root->right);
    }
}

// Duyệt cây theo thứ tự sau (Post-order)
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%c ", root->value);
    }
}

// Hàm main để kiểm tra
int main() {
    char postfix[] = "ab+cde+**"; // Biểu thức hậu tố
    Node* root = constructTree(postfix);

    printf("Duyệt trước (Pre-order):\n");
    preOrder(root);
    printf("\nDuyệt giữa (In-order):\n");
    inOrder(root);
    printf("\nDuyệt sau (Post-order):\n");
    postOrder(root);

    return 0;
}
