#include <stdio.h>
#include <stdlib.h>

// Cấu trúc của một node trong danh sách
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Hàm tạo node mới
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm một node vào cuối danh sách
void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Hàm in danh sách kèm thứ tự các node
void printListWithIndex(Node* head) {
    Node* temp = head;
    int index = 1;
    while (temp != NULL) {
        printf("Node %d: %d\n", index, temp->data);
        temp = temp->next;
        index++;
    }
}

// Hàm xoá node sau một node cho trước (dựa trên số thứ tự)
int deleteAfterNodeByIndex(Node** head, int index) {
    if (*head == NULL) {
        printf("Danh sách rỗng, không thể xoá.\n");
        return 0;
    }

    Node* temp = *head;
    int currentIndex = 1;

    // Tìm node ở vị trí index
    while (temp != NULL && currentIndex < index) {
        temp = temp->next;
        currentIndex++;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Không thể xoá, node sau node %d không tồn tại.\n", index);
        return 0;
    }

    // Xoá node tiếp theo
    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
    printf("Đã xoá node sau node %d thành công.\n", index);
    return 1;
}

int main() {
    Node* head = NULL;

    // Thêm dữ liệu vào danh sách
    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);
    append(&head, 50);

    int index;
    while (1) {
        // Kiểm tra danh sách rỗng
        if (head == NULL) {
            printf("Danh sách đã hết node. Nhập 0 để thoát chương trình.\n");
            scanf("%d", &index);
            if (index == 0) {
                printf("Thoát chương trình.\n");
                break;
            }
            continue;
        }

        // In danh sách
        printf("\nDanh sách hiện tại:\n");
        printListWithIndex(head);

        // Nhập số thứ tự của node
        printf("\nNhập số thứ tự của node (từ 1) để xoá node ngay sau nó, hoặc nhập 0 để thoát: ");
        scanf("%d", &index);

        if (index == 0) {
            printf("Thoát chương trình.\n");
            break;
        }

        // Kiểm tra số thứ tự hợp lệ
        if (index < 1) {
            printf("Số thứ tự không hợp lệ. Vui lòng nhập lại.\n");
            continue;
        }

        // Xoá node
        if (!deleteAfterNodeByIndex(&head, index)) {
            printf("Vui lòng nhập số thứ tự hợp lệ.\n");
        }
    }

    return 0;
}
