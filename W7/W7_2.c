#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Hàm tạo một nút mới
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode; // Liên kết vòng (tự trỏ đến chính nó)
    return newNode;
}

// Hàm tạo danh sách liên kết vòng với N người chơi
Node* createCircularList(int N) {
    Node* head = createNode(1);
    Node* prev = head;
    for (int i = 2; i <= N; i++) {
        Node* newNode = createNode(i);
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // Hoàn tất vòng tròn
    return head;
}

// Hàm xác định người chiến thắng
int getJosephusPosition(int N, int M) {
    Node* head = createCircularList(N);
    Node* prev = NULL;
    
    // Thực hiện vòng lặp cho đến khi còn 1 người chơi
    while (head->next != head) { 
        // Di chuyển đến người chơi thứ M
        for (int count = 1; count < M; count++) {
            prev = head;
            head = head->next;
        }
        
        // Loại bỏ người chơi thứ M
        printf("Người chơi %d bị loại bỏ\n", head->data);
        prev->next = head->next; // Bỏ qua nút
        free(head);
        head = prev->next; // Chuyển đến người kế tiếp
    }
    
    int winner = head->data;
    free(head); // Giải phóng bộ nhớ cuối cùng
    return winner;
}

int main() {
    int N, M;
    printf("Nhập số người chơi N: ");
    scanf("%d", &N);
    printf("Nhập số đếm M: ");
    scanf("%d", &M);

    int winner = getJosephusPosition(N, M);
    printf("Người chiến thắng là người chơi số %d\n", winner);
    return 0;
}
