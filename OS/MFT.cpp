#include <iostream>
#include <string>

using namespace std;

struct Process {
    int id;
    int size;
    bool allocated;
};

void MFT(int memorySize, int blockSize, Process processes[], int numProcesses) {
    int numBlocks = memorySize / blockSize;
    int memory[numBlocks];
    for (int i = 0; i < numBlocks; i++) {
        memory[i] = -1;
    }

    cout << "\nMFT Allocation:\n";
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].size <= blockSize) {
            bool allocated = false;
            for (int j = 0; j < numBlocks; j++) {
                if (memory[j] == -1) {
                    memory[j] = processes[i].id;
                    processes[i].allocated = true;
                    allocated = true;
                    break;
                }
            }
            if (!allocated) {
                cout << "Process " << processes[i].id << " could not be allocated (No free block).\n";
            }
        } else {
            cout << "Process " << processes[i].id << " could not be allocated (Size exceeds block size).\n";
        }
    }

    cout << "\nMemory Blocks:\n";
    for (int i = 0; i < numBlocks; i++) {
        cout << "Block " << i + 1 << ": ";
        if (memory[i] == -1) {
            cout << "Free\n";
        } else {
            cout << "Process " << memory[i] << "\n";
        }
    }
}

int main() {
    int memorySize, blockSize, numProcesses;

    cout << "Enter the total memory size: ";
    cin >> memorySize;

    cout << "Enter the block size: ";
    cin >> blockSize;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    Process processes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter size for Process " << i + 1 << ": ";
        cin >> processes[i].size;
        processes[i].id = i + 1;
        processes[i].allocated = false;
    }

    MFT(memorySize, blockSize, processes, numProcesses);

    return 0;
}
