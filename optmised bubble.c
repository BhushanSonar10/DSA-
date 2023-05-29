#include <stdio.h>

void bubbleSort(int array[], int size) {
    int swapped;

    for (int step = 0; step < size - 1; ++step) {
        swapped = 0;

        for (int i = 0; i < size - step - 1; ++i) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = 1;
            }
        }

        // If no swaps were made, the array is already sorted
        if (swapped == 0)
            break;
    }
}

void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d  ", array[i]);
    }
}

int main() {
    int a[] = { 45, 0, 11, -9 };
    int n = sizeof(a) / sizeof(a[0]);

    bubbleSort(a, n);

    printf("Sorted Array in Ascending Order:\n");
    printArray(a, n);

    return 0;
}
