#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff; // Hệ số
    int exp;   // Số mũ
    struct Node* next;
} Node;

// Tạo một node mới
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Thêm một node vào danh sách theo thứ tự bậc giảm dần
Node* insertNode(Node* head, int coeff, int exp) {
    if (coeff == 0) return head; // Bỏ qua nếu hệ số bằng 0

    Node* newNode = createNode(coeff, exp);
    if (!head || exp > head->exp) {
        newNode->next = head;
        return newNode;
    }

    Node* temp = head;
    while (temp->next && temp->next->exp > exp) {
        temp = temp->next;
    }

    if (temp->exp == exp) {
        temp->coeff += coeff;
        if (temp->coeff == 0) { // Nếu tổng hệ số bằng 0, xoá node
            Node* toDelete = temp;
            head = temp->next;
            free(toDelete);
        }
        free(newNode);
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }

    return head;
}

// Nhập đa thức
Node* inputPolynomial(int degree) {
    Node* poly = NULL;
    int coeff;
    for (int i = degree; i >= 0; i--) {
        printf("Nhập hệ số cho x^%d: ", i);
        scanf("%d", &coeff);
        poly = insertNode(poly, coeff, i);
    }
    return poly;
}

// Cộng hai đa thức
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 || poly2) {
        if (poly1 && (!poly2 || poly1->exp > poly2->exp)) {
            result = insertNode(result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly2 && (!poly1 || poly2->exp > poly1->exp)) {
            result = insertNode(result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int sumCoeff = poly1->coeff + poly2->coeff;
            result = insertNode(result, sumCoeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    return result;
}

// In đa thức
void printPolynomial(Node* poly) {
    if (!poly) {
        printf("0\n");
        return;
    }

    while (poly) {
        if (poly->coeff > 0) 
            printf(" + ");
        if (poly->exp == 0)
            printf("%d", poly->coeff);
        else if (poly->exp == 1)
            printf("%dx", poly->coeff);
        else
            printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
    }
    printf("\n");
}

// Giải phóng bộ nhớ
void freePolynomial(Node* poly) {
    while (poly) {
        Node* temp = poly;
        poly = poly->next;
        free(temp);
    }
}

// Chương trình chính
int main() {
    int degree1, degree2;
    
    printf("Nhập bậc của đa thức f(x): ");
    scanf("%d", &degree1);
    Node* f = inputPolynomial(degree1);
    
    printf("Nhập bậc của đa thức g(x): ");
    scanf("%d", &degree2);
    Node* g = inputPolynomial(degree2);

    printf("Đa thức f(x) = ");
    printPolynomial(f);

    printf("Đa thức g(x) = ");
    printPolynomial(g);

    Node* h = addPolynomials(f, g);
    printf("Tổng h(x) = f(x) + g(x) = ");
    printPolynomial(h);

    // Giải phóng bộ nhớ
    freePolynomial(f);
    freePolynomial(g);
    freePolynomial(h);

    return 0;
}
