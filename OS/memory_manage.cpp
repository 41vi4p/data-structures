#include <iostream>

using namespace std;

void firstFit(int memory[], int m, int process[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (memory[j] >= process[i]) {
                allocation[i] = j;
                memory[j] -= process[i];
                break;
            }
        }
    }

    cout << "\nFirst Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << "\n";
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

void nextFit(int memory[], int m, int process[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    int lastAllocated = 0;
    for (int i = 0; i < n; i++) {
        int j = lastAllocated;
        do {
            if (memory[j] >= process[i]) {
                allocation[i] = j;
                memory[j] -= process[i];
                lastAllocated = j;
                break;
            }
            j = (j + 1) % m;
        } while (j != lastAllocated);
    }

    cout << "\nNext Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << "\n";
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

void bestFit(int memory[], int m, int process[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (memory[j] >= process[i] && (bestIndex == -1 || memory[j] < memory[bestIndex])) {
                bestIndex = j;
            }
        }
        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            memory[bestIndex] -= process[i];
        }
    }

    cout << "\nBest Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << "\n";
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

void worstFit(int memory[], int m, int process[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        for (int j = 0; j < m; j++) {
            if (memory[j] >= process[i] && (worstIndex == -1 || memory[j] > memory[worstIndex])) {
                worstIndex = j;
            }
        }
        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            memory[worstIndex] -= process[i];
        }
    }

    cout << "\nWorst Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << "\n";
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

int main() {
    int m, n;
    cout << "Enter number of memory blocks: ";
    cin >> m;
    int memory[m];
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < m; i++) cin >> memory[i];

    cout << "Enter number of processes: ";
    cin >> n;
    int process[n];
    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < n; i++) cin >> process[i];

    int memoryCopy[m];
    for (int i = 0; i < m; i++) memoryCopy[i] = memory[i];
    firstFit(memoryCopy, m, process, n);

    for (int i = 0; i < m; i++) memoryCopy[i] = memory[i];
    nextFit(memoryCopy, m, process, n);

    for (int i = 0; i < m; i++) memoryCopy[i] = memory[i];
    bestFit(memoryCopy, m, process, n);

    for (int i = 0; i < m; i++) memoryCopy[i] = memory[i];
    worstFit(memoryCopy, m, process, n);

    return 0;
}