#include <stdio.h>
#define K 10

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int value = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > value) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = value;
        printArray(arr, high + 1);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int pIndex = low;
    for (int i = low; i < high; i++) {
        if (arr[i] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[pIndex];
            arr[pIndex] = temp;
            pIndex++;
        }
    }
    int temp = arr[pIndex];
    arr[pIndex] = arr[high];
    arr[high] = temp;
    return pIndex;
}

void hybridQuickSort(int arr[], int low, int high, int size) {
    while (low < high) {
        if (high - low < K) {
            insertionSort(arr, low, high);
            break;
        } else {
            int pivot = partition(arr, low, high);
            printArray(arr, size); 
            if (pivot - low < high - pivot) {
                hybridQuickSort(arr, low, pivot - 1, size);
                low = pivot + 1;
            } else {
                hybridQuickSort(arr, pivot + 1, high, size);
                high = pivot - 1;
            }
        }
    }
}

int main() {
    int arr[] = {29, 10, 14, 37, 14, 1, 45, 84, 124, 1234, 5543, 12, 547, 134, 543, 817293, 2310};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Mang ban dau: \n");
    printArray(arr, n);

    hybridQuickSort(arr, 0, n - 1, n);

    printf("Mang sau khi sap xep: \n");
    printArray(arr, n);

    return 0;
}