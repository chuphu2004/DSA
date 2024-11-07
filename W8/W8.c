#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAfter(struct Node* T, int newData) {
    if (T == NULL) {
        printf("Node được trỏ bởi con trỏ T không tồn tại.\n");
        return;
    }
    
    struct Node* newNode = createNode(newData);
    newNode->next = T->next;
    T->next = newNode;
    printf("Đã chèn %d sau node có giá trị %d.\n", newData, T->data);
}


void deleteTail(struct Node** head) {
    if (*head == NULL) {
        printf("Danh sách rỗng.\n");
        return;
    }


    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        printf("Đã xóa node cuối cùng.\n");
        return;
    }


    struct Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    free(temp->next);
    temp->next = NULL;
    printf("Đã xóa node cuối cùng.\n");
}


void deleteNode(struct Node* T) {
    if (T == NULL || T->next == NULL) {
        printf("Không thể xóa node.\n");
        return;
    }
    
    struct Node* temp = T->next;
    T->data = temp->data;
    T->next = temp->next;
    free(temp);
    printf("Đã xóa node.\n");
}


void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


int main() {
    struct Node* head = createNode(10);
    struct Node* second = createNode(20);
    struct Node* third = createNode(30);
    head->next = second;
    second->next = third;

    printf("Danh sách ban đầu: ");
    printList(head);


    insertAfter(head, 15);
    printf("Danh sách sau khi chèn: ");
    printList(head);


    deleteTail(&head);
    printf("Danh sách sau khi xóa node cuối cùng: ");
    printList(head);

    deleteNode(second);
    printf("Danh sách sau khi xóa một node: ");
    printList(head);

    return 0;
}
