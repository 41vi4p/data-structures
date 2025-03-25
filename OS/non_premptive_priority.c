#include <stdio.h>

#define MAX 10  // Maximum number of processes

// Function to calculate waiting time and turnaround time for NPP
void calculateTimes(int processes[], int n, int bt[], int wt[], int tat[], int priority[]) {
    int completed[MAX], time = 0, min_priority, next_process;
    
    // Initialize completed array to track finished processes
    for (int i = 0; i < n; i++) {
        completed[i] = 0;  // 0 means not completed
    }

    // Process execution
    for (int count = 0; count < n; count++) {
        min_priority = 1000;  // Arbitrarily large value to start with
        next_process = -1;

        // Find the process with the highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 && priority[i] < min_priority) {
                min_priority = priority[i];
                next_process = i;
            }
        }

        // The selected process will now execute
        time += bt[next_process];  // Increase time by burst time of the selected process
        wt[next_process] = time - bt[next_process];  // Calculate waiting time
        tat[next_process] = time;  // Calculate turnaround time
        completed[next_process] = 1;  // Mark process as completed
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverageTimes(int wt[], int tat[], int n) {
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average Waiting Time (AWT): %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time (ATAT): %.2f\n", (float)total_tat / n);
}

int main() {
    int processes[MAX], bt[MAX], wt[MAX], tat[MAX], priority[MAX];
    int n;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst time for each process
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Process IDs (1, 2, 3, ...)
        printf("Process P%d: ", processes[i]);
        scanf("%d", &bt[i]);
    }

    // Input priority for each process
    printf("Enter priority for each process (lower number means higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Priority of Process P%d: ", processes[i]);
        scanf("%d", &priority[i]);
    }

    // Calculate waiting time and turnaround time
    calculateTimes(processes, n, bt, wt, tat, priority);

    // Display the results
    printf("\nProcess ID | Burst Time | Waiting Time | Turnaround Time | Priority\n");
    for (int i = 0; i < n; i++) {
        printf("P%d         | %d          | %d            | %d              | %d\n", 
                processes[i], bt[i], wt[i], tat[i], priority[i]);
    }

    // Calculate and display average times
    calculateAverageTimes(wt, tat, n);

    return 0;
}
