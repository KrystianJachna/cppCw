#include <iostream>
#define SIZE 100
using namespace std;

void swap(int *arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = arr[i];
}

void bubbleSort(int * arr) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr, j, j+1);

}

void insertionSort

int main() {
    int arr[SIZE] = {1, 68, 26, 75, 82, 36, 86, 14, 62, 6, 50, 47, 19, 91, 30, 77, 29, 66,
            5, 81, 54, 70, 55, 7, 58, 44, 31, 61, 39, 32, 28, 27, 35, 41, 16, 88,
            76, 21, 97, 95, 34, 60, 17, 52, 74, 2, 85, 93, 79, 22, 18, 72, 69, 43,
            90, 3, 20, 53, 51, 96, 65, 11, 8, 67, 13, 100, 64, 40, 23, 71, 94, 38,
            63, 98, 87, 33, 80, 12, 83, 49, 46, 48, 4, 59, 57, 56, 78, 89, 92, 25,
            84, 15, 42, 10, 99, 9, 37, 45, 73, 24};



    return 0;
}