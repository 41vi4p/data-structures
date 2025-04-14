#include <iostream>

using namespace std;

bool isSafeState(int available[], int max[][10], int allocation[][10], int need[][10], int n, int m) {
    int work[10];
    bool finish[10] = {false};
    int safeSequence[10];
    int safeIndex = 0;

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence[safeIndex++] = i;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            cout << "System is not in a safe state.\n";
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < safeIndex; i++) {
        cout << "P" << safeSequence[i] << " ";
    }
    cout << endl;
    return true;
}

int main() {
    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> m;

    int available[10];
    cout << "Enter the available resources: ";
    for (int i = 0; i < m; i++) {
        cin >> available[i];
    }

    int max[10][10], allocation[10][10], need[10][10];
    cout << "Enter the Max matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the Allocation matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    isSafeState(available, max, allocation, need, n, m);

    return 0;
}
