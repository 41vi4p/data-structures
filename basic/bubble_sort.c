#include <stdio.h>

void printArray(int arr[], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int n) {
    int pass = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            pass = pass + 1;
            printf("\nPass %d:",pass);
            printArray(arr, n); 
        }
    }
    printf("\nTotal passes: %d\n", pass);
}



void insertionSort(int arr[], int n) {
    int pass = 0;
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
        pass = pass + 1;
        printf("\nPass %d:",pass);
        printArray(arr, n); 
    }
    printf("\nTotal passes: %d\n", pass);
}

int main() {
    int n = 0;
    int arr[100];
    printf("Enter elements (press 'q' to stop):\n");
    while (scanf("%d", &arr[n]) == 1) {
        n++;
    }

    int choice;
    printf("\nChoose sorting method:\n1. Bubble Sort\n2. Selection Sort\n");
    while (getchar() != '\n'); // Clear buffer
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        bubbleSort(arr, n);
        break;
    case 2:
        insertionSort(arr, n);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
    printf("\nSorted array: ");
    printArray(arr, n);
    return 0;
}