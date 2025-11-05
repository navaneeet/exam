#include <stdio.h>
#include <stdlib.h>

// Function to get the maximum value in array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Function to swap two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort
int bubbleSort(int arr[], int n) {
    int steps = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            steps++;
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
    return steps;
}

// Insertion Sort
int insertionSort(int arr[], int n) {
    int steps = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            steps++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return steps;
}

// Radix Sort helpers
void countSort(int arr[], int n, int exp, int *steps) {
    int output[n];
    int count[10] = {0};
    
    for (int i = 0; i < n; i++) {
        count[(arr[i]/exp)%10]++;
        (*steps)++;
    }
    
    for (int i = 1; i < 10; i++) {
        count[i] += count[i-1];
        (*steps)++;
    }
    
    for (int i = n-1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
        (*steps)++;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        (*steps)++;
    }
}

int radixSort(int arr[], int n) {
    int steps = 0;
    int m = getMax(arr, n);
    
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp, &steps);
        
    return steps;
}

// Quick Sort helpers
int partition(int arr[], int low, int high, int *steps) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high-1; j++) {
        (*steps)++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortHelper(int arr[], int low, int high, int *steps) {
    if (low < high) {
        int pi = partition(arr, low, high, steps);
        quickSortHelper(arr, low, pi - 1, steps);
        quickSortHelper(arr, pi + 1, high, steps);
    }
}

int quickSort(int arr[], int n) {
    int steps = 0;
    quickSortHelper(arr, 0, n-1, &steps);
    return steps;
}

// Merge Sort helpers
void merge(int arr[], int l, int m, int r, int *steps) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[n1], R[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
        
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        (*steps)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        (*steps)++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        (*steps)++;
    }
}

void mergeSortHelper(int arr[], int l, int r, int *steps) {
    if (l < r) {
        int m = l + (r - l)/2;
        mergeSortHelper(arr, l, m, steps);
        mergeSortHelper(arr, m+1, r, steps);
        merge(arr, l, m, r, steps);
    }
}

int mergeSort(int arr[], int n) {
    int steps = 0;
    mergeSortHelper(arr, 0, n-1, &steps);
    return steps;
}

// Utility functions
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = source[i];
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int *original = (int*)malloc(n * sizeof(int));
    int *arr = (int*)malloc(n * sizeof(int));
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &original[i]);
        
    printf("\nOriginal array: ");
    printArray(original, n);
    
    // Test all sorting algorithms
    int steps;
    
    // Bubble Sort
    copyArray(original, arr, n);
    steps = bubbleSort(arr, n);
    printf("\nBubble Sort:\nSorted array: ");
    printArray(arr, n);
    printf("Steps: %d\n", steps);
    
    // Insertion Sort
    copyArray(original, arr, n);
    steps = insertionSort(arr, n);
    printf("\nInsertion Sort:\nSorted array: ");
    printArray(arr, n);
    printf("Steps: %d\n", steps);
    
    // Radix Sort
    copyArray(original, arr, n);
    steps = radixSort(arr, n);
    printf("\nRadix Sort:\nSorted array: ");
    printArray(arr, n);
    printf("Steps: %d\n", steps);
    
    // Quick Sort
    copyArray(original, arr, n);
    steps = quickSort(arr, n);
    printf("\nQuick Sort:\nSorted array: ");
    printArray(arr, n);
    printf("Steps: %d\n", steps);
    
    // Merge Sort
    copyArray(original, arr, n);
    steps = mergeSort(arr, n);
    printf("\nMerge Sort:\nSorted array: ");
    printArray(arr, n);
    printf("Steps: %d\n", steps);
    
    free(original);
    free(arr);
    return 0;
}