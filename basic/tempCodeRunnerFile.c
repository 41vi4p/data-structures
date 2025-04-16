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

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int mergeSort(int arr[], int left, int right) {
    int pass = 0; // Track the number of passes
    if (left < right) {
        int mid = left + (right - left) / 2;
        pass += mergeSort(arr, left, mid);
        pass += mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);

        pass++;
        
    }
    return pass;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

int quickSort(int arr[], int low, int high) {
    int pass = 0; // Track the number of passes
    if (low < high) {
        int pi = partition(arr, low, high);
        pass++;
       
    }
    return pass;
}



int main() {
    int n = 0;
    int arr[100], tempArr[100];
    printf("Enter elements (press 'q' to stop):\n");
    while (scanf("%d", &arr[n]) == 1) {
        n++;
    }

    int choice;
    printf("\nChoose sorting method:\n1. Bubble Sort\n2. Insertion Sort\n3. Merge Sort\n4. Quick Sort\n5. Exit\n");
    while (getchar() != '\n'); // Clear buffer
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        bubbleSort(arr, n);
        break;
    case 2:
        insertionSort(arr, n);
        break;
    case 3:
        mergeSort(arr, 0, n - 1);
        break;
    case 4:
        quickSort(arr, 0, n - 1);
        break;
    
    default:
        printf("Invalid choice\n");
        break;
    }
    printf("\nSorted array: ");
    printArray(arr, n);
    return 0;
}