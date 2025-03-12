#include <stdio.h>

#define MAX 10  // Maximum number of processes

// Function to calculate waiting time and turnaround time
void calculateTimes(int processes[], int n, int bt[], int wt[], int tat[], int quantum) {
    int remaining_bt[MAX], time = 0;
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }
    
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = 0;
                if (remaining_bt[i] > quantum) {
                    time += quantum;
                    remaining_bt[i] -= quantum;
                } else {
                    time += remaining_bt[i];
                    wt[i] = time - bt[i];
                    tat[i] = time;
                    remaining_bt[i] = 0;
                }
            }
        }
        if (done == 1) break;
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
    int processes[MAX], bt[MAX], wt[MAX], tat[MAX];
    int n, quantum;

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

    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Calculate waiting time and turnaround time
    calculateTimes(processes, n, bt, wt, tat, quantum);

    // Display the results
    printf("\nProcess ID | Burst Time | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d         | %d          | %d            | %d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    // Calculate and display average times
    calculateAverageTimes(wt, tat, n);

    return 0;
}
