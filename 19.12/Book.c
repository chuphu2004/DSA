#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc của một node trong cây
typedef struct Node {
    char title[100];         // Tiêu đề của mục (chapter, section,...)
    int pages;               // Số trang của mục
    struct Node* firstChild; // Con đầu tiên
    struct Node* nextSibling; // Anh chị em tiếp theo
} Node;

// Tạo một node mới
Node* createNode(const char* title, int pages) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->title, title);
    newNode->pages = pages;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Thêm một mục con vào một node
void addChild(Node* parent, Node* child) {
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        Node* temp = parent->firstChild;
        while (temp->nextSibling) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Đếm số chương của cuốn sách (các node con của root)
int countChapters(Node* root) {
    int count = 0;
    Node* temp = root->firstChild;
    while (temp) {
        count++;
        temp = temp->nextSibling;
    }
    return count;
}

// Tìm chương dài nhất của cuốn sách (node con có nhiều trang nhất)
Node* findLongestChapter(Node* root) {
    Node* longestChapter = NULL;
    int maxPages = 0;
    Node* temp = root->firstChild;
    while (temp) {
        if (temp->pages > maxPages) {
            maxPages = temp->pages;
            longestChapter = temp;
        }
        temp = temp->nextSibling;
    }
    return longestChapter;
}

// Tìm và xoá một mục khỏi cây
int removeNode(Node* parent, const char* title) {
    Node* temp = parent->firstChild;
    Node* prev = NULL;

    while (temp) {
        if (strcmp(temp->title, title) == 0) {
            if (prev) {
                prev->nextSibling = temp->nextSibling;
            } else {
                parent->firstChild = temp->nextSibling;
            }
            free(temp);
            return 1; // Đã xoá thành công
        }
        prev = temp;
        temp = temp->nextSibling;
    }
    return 0; // Không tìm thấy
}

// Hàm tính tổng số trang của một mục (bao gồm cả con của nó)
int calculateTotalPages(Node* node) {
    if (!node) return 0;
    int totalPages = 0; // Chỉ tính tổng trang từ các mục con
    Node* child = node->firstChild;
    while (child) {
        totalPages += calculateTotalPages(child); // Gọi đệ quy để tính tổng trang của các mục con
        child = child->nextSibling;
    }
    return totalPages;
}

// Cập nhật số trang của một mục
void updatePages(Node* node) {
    if (!node) return;
    Node* temp = node->firstChild;
    while (temp) {
        updatePages(temp); // Cập nhật đệ quy cho các mục con trước
        temp->pages = calculateTotalPages(temp); // Số trang được cập nhật từ các mục con
        temp = temp->nextSibling;
    }
}

// Hàm hiển thị cây (dùng để kiểm tra)
void printTree(Node* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s (%d pages)\n", node->title, node->pages);
    printTree(node->firstChild, level + 1);
    printTree(node->nextSibling, level);
}

int main() {
    // Tạo root của cuốn sách
    Node* book = createNode("Book", 0);

    // Thêm các chương và mục vào sách
    Node* chapter1 = createNode("Chapter 1", 0);
    Node* chapter2 = createNode("Chapter 2", 0);
    Node* section1 = createNode("Section 1.1", 5);
    Node* section2 = createNode("Section 1.2", 3);
    Node* subsection1 = createNode("Subsection 1.1.1", 2);
    Node* subsection2 = createNode("Subsection 1.1.2", 1);

    addChild(section1, subsection1);
    addChild(section1, subsection2);
    addChild(chapter1, section1);
    addChild(chapter1, section2);
    addChild(book, chapter1);
    addChild(book, chapter2);

    // Hiển thị cây
    printf("Book structure:\n");
    printTree(book, 0);

    // Đếm số chương
    printf("\nNumber of chapters: %d\n", countChapters(book));

    // Tìm chương dài nhất
    Node* longestChapter = findLongestChapter(book);
    if (longestChapter) {
        printf("Longest chapter: %s (%d pages)\n", longestChapter->title, longestChapter->pages);
    }

    // Cập nhật số trang và hiển thị lại cây
    updatePages(book);
    printf("\nUpdated Book structure:\n");
    printTree(book, 0);

    return 0;
}
