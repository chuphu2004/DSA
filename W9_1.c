#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char fileName[100];
    int fileSize;       // Kích thước file tính bằng KB
    int timestamp;      // Giả sử là số nguyên để biểu diễn thời gian
    struct Node *next;
} Node;

// Tạo một node mới cho file
Node* createNode(const char *fileName, int fileSize, int timestamp) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->fileName, fileName);
    newNode->fileSize = fileSize;
    newNode->timestamp = timestamp;
    newNode->next = NULL;
    return newNode;
}

// Chèn file vào danh sách theo thứ tự thời gian
void insertFile(Node **head, Node *newNode) {
    if (*head == NULL || (*head)->timestamp > newNode->timestamp) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL && current->next->timestamp < newNode->timestamp) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Tính toán tổng kích thước các file
int calculateTotalSize(Node *head) {
    int totalSize = 0;
    Node *current = head;
    while (current != NULL) {
        totalSize += current->fileSize;
        current = current->next;
    }
    return totalSize;
}

// Loại bỏ các file có kích thước nhỏ nhất nếu cần
void removeSmallestFiles(Node **head, int maxSize) {
    while (*head != NULL && calculateTotalSize(*head) > maxSize) {
        Node *current = *head;
        Node *prev = NULL;
        Node *smallest = *head;
        Node *smallestPrev = NULL;
        
        while (current != NULL) {
            if (current->fileSize < smallest->fileSize) {
                smallest = current;
                smallestPrev = prev;
            }
            prev = current;
            current = current->next;
        }
        
        if (smallestPrev == NULL) {
            *head = (*head)->next;
        } else {
            smallestPrev->next = smallest->next;
        }
        free(smallest);
    }
}

// Hàm in thông tin các file trong thư mục
void printFiles(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("File: %s, Size: %d KB, Timestamp: %d\n", current->fileName, current->fileSize, current->timestamp);
        current = current->next;
    }
}

// Hàm main thực hiện các thao tác
int main() {
    Node *head = NULL;
    
    // Thêm các file vào danh sách
    insertFile(&head, createNode("file1.txt", 200, 3));
    insertFile(&head, createNode("file2.txt", 300, 1));
    insertFile(&head, createNode("file3.txt", 100, 2));
    insertFile(&head, createNode("file4.txt", 500, 4));
    insertFile(&head, createNode("file5.txt", 32000, 4));
    
    printf("Files in directory:\n");
    printFiles(head);
    
    // Tính tổng kích thước thư mục trước khi xóa
    printf("\nTotal file size: %d KB\n", calculateTotalSize(head));
    
    int usbSize = 32 * 1024 * 1024; // 32GB in KB
    removeSmallestFiles(&head, usbSize);
    
    // In lại danh sách sau khi loại bỏ
    printf("\nFiles after removal to fit 32GB USB:\n");
    printFiles(head);
    printf("\nTotal file size after removal: %d KB\n", calculateTotalSize(head));
    
    return 0;
}
