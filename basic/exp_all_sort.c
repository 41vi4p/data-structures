#include <stdio.h>
#include <unistd.h> // For usleep function
#include <stdlib.h> // For system function

// Configuration for animation
int delay_ms = 300; // Default delay in milliseconds
int animate = 1;    // Animation enabled by default

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void delay() {
    if (animate) {
        usleep(delay_ms * 1000); // Convert ms to microseconds
    }
}

void printArray(int arr[], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printArrayWithHighlight(int arr[], int n, int pos1, int pos2) {
    if (!animate) return;
    
    clearScreen();
    printf("\n");
    for (int i = 0; i < n; i++) {
        if (i == pos1 || i == pos2) {
            printf("\033[1;32m%d\033[0m ", arr[i]); // Green highlight for compared elements
        } else {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
    
    // Visual indicator line
    for (int i = 0; i < n; i++) {
        if (i == pos1 || i == pos2) {
            printf("^ "); // Mark positions being compared
        } else {
            printf("  ");
        }
    }
    printf("\n");
    
    delay();
}

void bubbleSort(int arr[], int n) {
    int pass = 0;
    printf("\n--- BUBBLE SORT ---\n");
    printf("Logic: Compare adjacent elements and swap if they're in wrong order\n");
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Highlight elements being compared
            printArrayWithHighlight(arr, n, j, j+1);
            
            if (arr[j] > arr[j + 1]) {
                printf("Swapping %d and %d\n", arr[j], arr[j+1]);
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
                // Show the array after swapping
                printArrayWithHighlight(arr, n, j, j+1);
            } else {
                printf("No swap needed\n");
            }
            
            pass = pass + 1;
            printf("\nPass %d:",pass);
            printArray(arr, n);
            delay();
        }
        printf("\nEnd of outer loop iteration %d. Largest element is now at position %d\n", i+1, n-i-1);
        delay();
    }
    printf("\nTotal passes: %d\n", pass);
}

void insertionSort(int arr[], int n) {
    int pass = 0;
    printf("\n--- INSERTION SORT ---\n");
    printf("Logic: Build sorted array one element at a time\n");
    
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;
        
        printf("\nInserting element %d into sorted portion\n", temp);
        printArrayWithHighlight(arr, n, i, -1);
        
        while (j >= 0 && arr[j] > temp) {
            printArrayWithHighlight(arr, n, j, j+1);
            printf("Moving %d right to position %d\n", arr[j], j+1);
            
            arr[j + 1] = arr[j];
            j--;
            
            printArrayWithHighlight(arr, n, j+1, -1);
            delay();
        }
        
        arr[j + 1] = temp;
        printf("Placing %d at position %d\n", temp, j+1);
        printArrayWithHighlight(arr, n, j+1, -1);
        
        pass = pass + 1;
        printf("\nPass %d:",pass);
        printArray(arr, n);
        delay();
    }
    printf("\nTotal passes: %d\n", pass);
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    
    printf("\nMerging subarrays: [%d...%d] and [%d...%d]\n", left, mid, mid+1, right);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    printf("Left subarray: ");
    for (int i = 0; i < n1; i++) printf("%d ", L[i]);
    printf("\nRight subarray: ");
    for (int i = 0; i < n2; i++) printf("%d ", R[i]);
    printf("\n");
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        printf("Comparing L[%d]=%d with R[%d]=%d\n", i, L[i], j, R[j]);
        delay();
        
        if (L[i] <= R[j]) {
            printf("Placing L[%d]=%d at position %d\n", i, L[i], k);
            arr[k] = L[i];
            i++;
        } else {
            printf("Placing R[%d]=%d at position %d\n", j, R[j], k);
            arr[k] = R[j];
            j++;
        }
        k++;
        
        printArrayWithHighlight(arr, right+1, k-1, -1);
    }
    
    while (i < n1) {
        printf("Placing remaining L[%d]=%d at position %d\n", i, L[i], k);
        arr[k] = L[i];
        i++;
        k++;
        printArrayWithHighlight(arr, right+1, k-1, -1);
        delay();
    }
    
    while (j < n2) {
        printf("Placing remaining R[%d]=%d at position %d\n", j, R[j], k);
        arr[k] = R[j];
        j++;
        k++;
        printArrayWithHighlight(arr, right+1, k-1, -1);
        delay();
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
        printf("\nPass %d:", pass);
        printArray(arr, right - left + 1);
    }
    return pass;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    printf("\nPivot selected: %d (at index %d)\n", pivot, high);
    printArrayWithHighlight(arr, high+1, high, -1);
    
    int i = (low - 1);
    
    for (int j = low; j < high; j++) {
        printf("Comparing element %d with pivot %d\n", arr[j], pivot);
        printArrayWithHighlight(arr, high+1, j, high);
        delay();
        
        if (arr[j] <= pivot) {
            i++;
            printf("Element %d <= pivot, swapping elements at positions %d and %d\n", arr[j], i, j);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            printArrayWithHighlight(arr, high+1, i, j);
        } else {
            printf("Element %d > pivot, no swap\n", arr[j]);
        }
        delay();
    }
    
    printf("Placing pivot in its final sorted position\n");
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    printArrayWithHighlight(arr, high+1, i+1, high);
    
    printf("Partition complete: pivot %d is now at position %d\n", pivot, i+1);
    printf("Elements to the left are <= pivot, elements to the right are > pivot\n");
    delay();
    
    return (i + 1);
}

int quickSort(int arr[], int low, int high) {
    int pass = 0; // Track the number of passes
    if (low < high) {
        int pi = partition(arr, low, high);
        pass++;
        printf("\nPass %d:", pass);
        printArray(arr, high - low + 1);

        pass += quickSort(arr, low, pi - 1);
        pass += quickSort(arr, pi + 1, high);
    }
    return pass;
}

void resetPassCounters() {
    // Reset static counters for mergeSort and quickSort
    mergeSort(0, 0, 0); // Dummy call to reset static pass counter
    quickSort(0, 0, 0); // Dummy call to reset static pass counter
}

int main() {
    int n = 0;
    int arr[100], tempArr[100];
    
    printf("Enable animation? (0 for no, 1 for yes): ");
    scanf("%d", &animate);
    
    if (animate) {
        printf("Enter delay in milliseconds (recommended: 300-1000): ");
        scanf("%d", &delay_ms);
    }
    
    printf("Enter elements (press 'q' to stop):\n");
    while (scanf("%d", &arr[n]) == 1) {
        n++;
    }

    int choice;
    printf("\nChoose sorting method:\n1. Bubble Sort\n2. Selection Sort\n3. Merge Sort\n4. Quick Sort\n5. All of the above\n");
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
    case 5: {
        int bubblePasses, insertionPasses, mergePasses, quickPasses;

        printf("\nExecuting Bubble Sort:");
        for (int i = 0; i < n; i++) tempArr[i] = arr[i];
        bubbleSort(tempArr, n);
        bubblePasses = n * (n - 1) / 2; // Bubble Sort pass count formula

        printf("\nExecuting Insertion Sort:");
        for (int i = 0; i < n; i++) tempArr[i] = arr[i];
        insertionSort(tempArr, n);
        insertionPasses = n * (n - 1) / 2; // Insertion Sort pass count formula

        printf("\nExecuting Merge Sort:");
        for (int i = 0; i < n; i++) tempArr[i] = arr[i];
        mergePasses = mergeSort(tempArr, 0, n - 1);

        printf("\nExecuting Quick Sort:");
        for (int i = 0; i < n; i++) tempArr[i] = arr[i];
        quickPasses = quickSort(tempArr, 0, n - 1);

        printf("\nSummary of Passes:\n");
        printf("Bubble Sort: %d passes\n", bubblePasses);
        printf("Insertion Sort: %d passes\n", insertionPasses);
        printf("Merge Sort: %d passes\n", mergePasses);
        printf("Quick Sort: %d passes\n", quickPasses);
        break;
    }
    default:
        printf("Invalid choice\n");
        break;
    }
    printf("\nSorted array: ");
    printArray(arr, n);
    return 0;
}