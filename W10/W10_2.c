#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Định nghĩa cấu trúc file
typedef struct FileInfo {
    char name[100];      // Tên file
    long size;           // Dung lượng file (bytes)
    time_t created_time; // Thời gian tạo file (UNIX timestamp)
    struct FileInfo *next; // Con trỏ đến file kế tiếp trong danh sách
} FileInfo;

// Hàm tạo một file mới
FileInfo* createFile(const char *name, long size, time_t created_time) {
    FileInfo *newFile = (FileInfo *)malloc(sizeof(FileInfo));
    strcpy(newFile->name, name);
    newFile->size = size;
    newFile->created_time = created_time;
    newFile->next = NULL;
    return newFile;
}

// Hàm thêm file vào danh sách liên kết
void addFile(FileInfo **head, FileInfo *newFile) {
    if (*head == NULL) {
        *head = newFile;
    } else {
        FileInfo *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newFile;
    }
}

// Hàm in danh sách file
void printFiles(FileInfo *head) {
    FileInfo *temp = head;
    while (temp != NULL) {
        printf("File: %s, Dung lượng: %ld bytes, Thời gian tạo: %s",
               temp->name, temp->size, ctime(&temp->created_time));
        temp = temp->next;
    }
}

// Hàm sắp xếp danh sách theo dung lượng (bubble sort trên danh sách liên kết)
void sortFilesBySize(FileInfo **head) {
    if (*head == NULL) return;

    int swapped;
    FileInfo *ptr1;
    FileInfo *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->size > ptr1->next->size || 
                (ptr1->size == ptr1->next->size && ptr1->created_time > ptr1->next->created_time)) {
                // Hoán đổi thông tin
                char tempName[100];
                strcpy(tempName, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tempName);

                long tempSize = ptr1->size;
                ptr1->size = ptr1->next->size;
                ptr1->next->size = tempSize;

                time_t tempTime = ptr1->created_time;
                ptr1->created_time = ptr1->next->created_time;
                ptr1->next->created_time = tempTime;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Hàm xóa file nhỏ nhất và lâu nhất
void deleteSmallestOldest(FileInfo **head) {
    if (*head == NULL) return;

    FileInfo *temp = *head;
    *head = temp->next;
    printf("\nXóa file: %s, Dung lượng: %ld bytes, Thời gian tạo: %s",
           temp->name, temp->size, ctime(&temp->created_time));
    free(temp);
}

int main() {
    // Khởi tạo danh sách file
    FileInfo *fileList = NULL;

    // Tạo dữ liệu file sẵn
    addFile(&fileList, createFile("file1.txt", 500, 1690012000)); // File lớn
    addFile(&fileList, createFile("file2.txt", 200, 1690011000)); // File nhỏ, lâu nhất
    addFile(&fileList, createFile("file3.txt", 300, 1690013000)); // File trung bình
    addFile(&fileList, createFile("file4.txt", 200, 1690014000)); // File nhỏ, thời gian mới hơn

    printf("Danh sách file ban đầu:\n");
    printFiles(fileList);

    // Sắp xếp danh sách file theo dung lượng tăng dần
    sortFilesBySize(&fileList);

    printf("\nDanh sách file sau khi sắp xếp:\n");
    printFiles(fileList);

    // Xóa file nhỏ nhất và lâu nhất
    deleteSmallestOldest(&fileList);

    printf("\nDanh sách file sau khi xóa:\n");
    printFiles(fileList);

    // Giải phóng bộ nhớ
    while (fileList != NULL) {
        FileInfo *temp = fileList;
        fileList = fileList->next;
        free(temp);
    }

    return 0;
}
