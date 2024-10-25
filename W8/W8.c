#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ngay;
    int thang;
    int nam;
} Ngay;

typedef struct {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
} SinhVien;

typedef struct Node {
    SinhVien data;
    struct Node* link;
} Node;

typedef struct {
    Node* first;
    Node* last;
} List;

// Tạo danh sách trống
void initList(List* list) {
    list->first = NULL;
    list->last = NULL;
}

// Tạo một sinh viên
SinhVien taoSinhVien(char maSV[], char hoTen[], int gioiTinh, Ngay ngaySinh, char diaChi[], char lop[], char khoa[]) {
    SinhVien sv;
    strcpy(sv.maSV, maSV);
    strcpy(sv.hoTen, hoTen);
    sv.gioiTinh = gioiTinh;
    sv.ngaySinh = ngaySinh;
    strcpy(sv.diaChi, diaChi);
    strcpy(sv.lop, lop);
    strcpy(sv.khoa, khoa);
    return sv;
}

// Tạo một node mới
Node* initNode(SinhVien sv) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = sv;
    node->link = NULL;
    return node;
}

// Thêm sinh viên vào danh sách theo thứ tự tăng dần của mã sinh viên
void themSinhVien(List* list, SinhVien sv) {
    Node* newNode = initNode(sv);
    if (list->first == NULL || strcmp(list->first->data.maSV, sv.maSV) > 0) {
        newNode->link = list->first;
        list->first = newNode;
        if (list->last == NULL) {
            list->last = newNode;
        }
    } else {
        Node* current = list->first;
        while (current->link != NULL && strcmp(current->link->data.maSV, sv.maSV) < 0) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
        if (newNode->link == NULL) {
            list->last = newNode;
        }
    }
}

// In danh sách sinh viên
void inDanhSachSinhVien(List list) {
    Node* current = list.first;
    while (current != NULL) {
        SinhVien sv = current->data;
        printf("Ma SV: %s, Ho ten: %s, Gioi tinh: %d, Ngay sinh: %02d/%02d/%04d, Dia chi: %s, Lop: %s, Khoa: %s\n",
               sv.maSV, sv.hoTen, sv.gioiTinh, sv.ngaySinh.ngay, sv.ngaySinh.thang, sv.ngaySinh.nam, sv.diaChi, sv.lop, sv.khoa);
        current = current->link;
    }
}

// Tìm và in các sinh viên có cùng ngày sinh
void timSinhVienCungNgaySinh(List list, Ngay ngaySinh) {
    int found = 0;
    Node* current = list.first;
    while (current != NULL) {
        if (current->data.ngaySinh.ngay == ngaySinh.ngay &&
            current->data.ngaySinh.thang == ngaySinh.thang &&
            current->data.ngaySinh.nam == ngaySinh.nam) {
            SinhVien sv = current->data;
            printf("Ma SV: %s, Ho ten: %s, Gioi tinh: %d, Ngay sinh: %02d/%02d/%04d, Dia chi: %s, Lop: %s, Khoa: %s\n",
                   sv.maSV, sv.hoTen, sv.gioiTinh, sv.ngaySinh.ngay, sv.ngaySinh.thang, sv.ngaySinh.nam, sv.diaChi, sv.lop, sv.khoa);
            found = 1;
        }
        current = current->link;
    }
    if (!found) {
        printf("Khong tim thay sinh vien cung ngay sinh\n");
    }
}

// Xóa sinh viên có cùng ngày sinh khỏi danh sách
void xoaSinhVienCungNgaySinh(List* list, Ngay ngaySinh) {
    Node* current = list->first;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->data.ngaySinh.ngay == ngaySinh.ngay &&
            current->data.ngaySinh.thang == ngaySinh.thang &&
            current->data.ngaySinh.nam == ngaySinh.nam) {
            if (prev == NULL) {
                list->first = current->link;
                if (list->first == NULL) {
                    list->last = NULL;
                }
            } else {
                prev->link = current->link;
                if (current->link == NULL) {
                    list->last = prev;
                }
            }
            Node* temp = current;
            current = current->link;
            free(temp);
        } else {
            prev = current;
            current = current->link;
        }
    }
}

// Hàm kiểm tra chương trình
int main() {
    List listSV;
    initList(&listSV);

    // Nhập danh sách sinh viên
    Ngay ngaySinh1 = {1, 1, 2000};
    Ngay ngaySinh2 = {2, 2, 2001};
    Ngay ngaySinh3 = {1, 1, 2000};
    Ngay ngaySinh4 = {1, 1, 2000};
    Ngay ngaySinh5 = {1, 1, 2000};

    SinhVien sv1 = taoSinhVien("20220001", "Nguyen Van A", 1, ngaySinh1, "Ha Noi", "01", "ET-E9");
    SinhVien sv2 = taoSinhVien("20220002", "Nguyen Van B", 0, ngaySinh2, "Ha Noi", "02", "ET-E9");
    SinhVien sv3 = taoSinhVien("20220003", "Nguyen Van C", 1, ngaySinh3, "Ha Noi", "02", "ET-E9");
    SinhVien sv4 = taoSinhVien("20220005", "Nguyen Van D", 1, ngaySinh4, "Ha Noi", "02", "ET-E9");
    SinhVien sv5 = taoSinhVien("20220004", "Nguyen Van E", 1, ngaySinh5, "Ha Noi", "01", "ET-E9");

    themSinhVien(&listSV, sv1);
    themSinhVien(&listSV, sv2);
    themSinhVien(&listSV, sv3);
    themSinhVien(&listSV, sv4);
    themSinhVien(&listSV, sv5);

    printf("Danh sach sinh vien:\n");
    inDanhSachSinhVien(listSV);

    // Tìm sinh viên cùng ngày sinh
    printf("\nSinh vien cung ngay sinh 01/01/2000:\n");
    timSinhVienCungNgaySinh(listSV, ngaySinh1);

    // Xóa sinh viên cùng ngày sinh
    xoaSinhVienCungNgaySinh(&listSV, ngaySinh1);
    printf("\nDanh sach sinh vien sau khi xoa sinh vien cung ngay sinh 01/01/2000:\n");
    inDanhSachSinhVien(listSV);

    return 0;
}
