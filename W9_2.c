#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc của một node trong danh sách liên kết
typedef struct Node {
    char word[50];
    int count;
    struct Node* next;
} Node;

// Hàm tạo node mới
Node* createNode(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm từ vào danh sách
void addWord(Node** head, char* word) {
    Node* temp = *head;
    Node* prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            temp->count++;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    Node* newNode = createNode(word);
    if (prev == NULL) {
        *head = newNode;
    } else {
        prev->next = newNode;
    }
}

// Hàm xác định từ xuất hiện nhiều nhất
Node* findMostFrequentWord(Node* head) {
    Node* temp = head;
    Node* maxNode = head;
    while (temp != NULL) {
        if (temp->count > maxNode->count) {
            maxNode = temp;
        }
        temp = temp->next;
    }
    return maxNode;
}

// Hàm xóa từ láy liền kề
void removeConsecutiveDuplicateWords(Node** head) {
    Node* temp = *head;
    while (temp != NULL && temp->next != NULL) {
        if (strcmp(temp->word, temp->next->word) == 0) {
            Node* duplicate = temp->next;
            temp->next = temp->next->next;
            free(duplicate);
        } else {
            temp = temp->next;
        }
    }
}

// Hàm đếm số từ vựng
int countVocabulary(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Hàm xây dựng lại chuỗi từ danh sách liên kết
void buildSentenceFromList(Node* head, char* sentence) {
    Node* temp = head;
    sentence[0] = '\0';  // Đảm bảo chuỗi bắt đầu rỗng
    while (temp != NULL) {
        strcat(sentence, temp->word);
        if (temp->next != NULL) {
            strcat(sentence, " ");
        }
        temp = temp->next;
    }
}

// Hàm in danh sách liên kết
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("Từ: %s, Xuất hiện: %d lần\n", temp->word, temp->count);
        temp = temp->next;
    }
}

// Hàm giải phóng bộ nhớ của danh sách liên kết
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    char sentence[] = "xanh đỏ xanh xanh đỏ đỏ xanh xanh";
    char processedSentence[200];  // Chuỗi để lưu câu sau khi xử lý
    
    printf("Chuỗi ban đầu: %s\n", sentence);

    char* word = strtok(sentence, " ");
    
    // Thêm từng từ vào danh sách
    while (word != NULL) {
        addWord(&head, word);
        word = strtok(NULL, " ");
    }

    printf("\nDanh sách từ ban đầu:\n");
    printList(head);

    // Xác định từ xuất hiện nhiều nhất
    Node* mostFrequent = findMostFrequentWord(head);
    if (mostFrequent != NULL) {
        printf("\nTừ xuất hiện nhiều nhất: %s với %d lần\n", mostFrequent->word, mostFrequent->count);
    }

    // Xây dựng lại chuỗi từ danh sách trước khi xử lý
    buildSentenceFromList(head, processedSentence);
    printf("\nChuỗi trước khi xử lý từ láy: %s\n", processedSentence);

    // Loại bỏ từ láy liền kề
    removeConsecutiveDuplicateWords(&head);
    printf("\nDanh sách sau khi loại bỏ từ láy liền kề:\n");
    printList(head);

    // Xây dựng lại chuỗi từ danh sách sau khi xử lý
    buildSentenceFromList(head, processedSentence);
    printf("\nChuỗi sau khi xử lý từ láy: %s\n", processedSentence);

    // Đếm số từ vựng trong câu
    int vocabularyCount = countVocabulary(head);
    printf("\nSố từ vựng trong câu: %d\n", vocabularyCount);

    // Giải phóng bộ nhớ
    freeList(head);
    
    return 0;
}
