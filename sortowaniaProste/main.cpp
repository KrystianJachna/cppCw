#include <iostream>
#define SIZE 100
using namespace std;

void swap(int *arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void printArr(int *arr) {
    for (int i = 0; i < SIZE; ++i) {
        cout << arr[i] << ", ";
    }
    cout << endl << endl;
}

void bubbleSort(int *arr) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr, j, j+1);

}

void insertionSort(int *arr) {
    int j = 0;
    int cur = 0;

    for (int i = 1; i < SIZE; ++i) {
        cur = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > cur) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = cur;
    }
}

void selectionSort(int *arr) {
    for (int i = 0; i < SIZE - 1; ++i) {
        int minID = i;

        for (int j = i + 1; j < SIZE; ++j)
            if (arr[j] < arr[minID])
                minID = j;
        swap(arr, minID, i);
    }
}

// sortowania proste z ulepszeniami

void cocktailSort(int *arr) {
    bool swapped = true;
    int lBorder = 0;
    int rBorder = SIZE - 1;

    while (swapped) {
        swapped = false;
        for (int i = lBorder; i < rBorder; ++i) {
            if (arr[i] > arr[i+1]) {
                swapped = true;
                swap(arr, i, i+1);
            }
        }

        rBorder = rBorder - 1;
        if (!swapped)
            break;
        swapped = false;

        for (int i = rBorder; i > lBorder; --i) {
            if (arr[i - 1] > arr[i]) {
                swapped = true;
                swap(arr, i,  i - 1);
            }
        }
        lBorder = lBorder + 1;
    }
}

void stableSelectionSort(int *arr) {
    int minID = 0;

    for (int i = 0; i < SIZE - 1; ++i) {
        minID = i;
        for (int j = i + 1; j < SIZE; ++j)
            if (arr[j] < arr[minID])
                minID = j;

        int tmp = arr[minID];

        while (minID > i) {
            arr[minID] = arr[minID - 1];
            minID--;
        }
        arr[i] = tmp;
    }
}

int binSearch(int elem, int *arr, int R) {
    int L = 0;
    int mid = 0;

    while (L <= R) {
        mid = (L + R) / 2;

        if (arr[mid] == elem)
            return mid + 1;
        else if (arr[mid] > elem)
            R = mid - 1;
        else
            L = mid + 1;
    }
    return L;
}

void binaryInstertionSort(int * arr) {
    for (int i = 1; i < SIZE; ++i) {
        int tmp = arr[i];
        int j = i - 1;

        int place = binSearch(tmp, arr, j);

        while (j >= place) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = tmp;
    }
}

int Partition(int *arr, int L, int R) {
    int i = L - 1;
    int pivot = arr[R];

    for (int j = L; j < R; ++j) {
        if (arr[j] <= pivot) {
            i = i + 1;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, R);
    return i + 1;
}

void QuickSort(int *arr, int L = 0, int R = SIZE -1) {
    if (L >= R) return;

    int q = Partition(arr, L, R);

    QuickSort(arr, L, q - 1);
    QuickSort(arr, q + 1, R);

}

int main() {
    int arr[SIZE] = {1, 68, 26, 75, 82, 36, 86, 14, 62, 6, 50, 47, 19, 91, 30, 77, 29, 66,
            5, 81, 54, 70, 55, 7, 58, 44, 31, 61, 39, 32, 28, 27, 35, 41, 16, 88,
            76, 21, 97, 95, 34, 60, 17, 52, 74, 2, 85, 93, 79, 22, 18, 72, 69, 43,
            90, 3, 20, 53, 51, 96, 65, 11, 8, 67, 13, 100, 64, 40, 23, 71, 94, 38,
            63, 98, 87, 33, 80, 12, 83, 49, 46, 48, 4, 59, 57, 56, 78, 89, 92, 25,
            84, 15, 42, 10, 99, 9, 37, 45, 73, 24};

    printArr(arr);
    //bubbleSort(arr);
    //insertionSort(arr);
    //selectionSort(arr);
    //cocktailSort(arr);
    //stableSelectionSort(arr);
    //binaryInstertionSort(arr);
    QuickSort(arr);
    printArr(arr);

    return 0;
}