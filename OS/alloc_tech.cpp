#include <iostream>

using namespace std;

void displayFileAllocationInfo(int n, string fileName[], int startBlock[], int size[], int next[]) {
    
    cout << "File Name\tStart Block\tSize\tAllocation Chain" << endl;
    cout << "-----------------------------------------------------" << endl;
    
    for (int i = 0; i < n; i++) {
        cout << fileName[i] << "\t\t" << startBlock[i] << "\t\t" << size[i] << "\t";
        
        int current = startBlock[i];
        cout << current;
        while (next[current] != -1) {
            cout << " -> " << next[current];
            current = next[current];
        }
        cout << endl;
    }
}

void linkedfileallocation(int n, string fileName[], int size[], int** blocks)
{
    const int DISK_SIZE = 100; // set total disk size
    int disk[DISK_SIZE];
    int next[DISK_SIZE]; // Next pointers 
    int startBlock[n];   // To store the starting block of each file
    
    // Initialize disk blocks as free (-1)
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i] = -1;
        next[i] = -1; 
    }
    
    // Allocate blocks for each file based on user input
    for (int i = 0; i < n; i++) {
        startBlock[i] = blocks[i][0]; // First block is the starting block
        
        // Mark all blocks as allocated to file i
        for (int j = 0; j < size[i]; j++) {
            int blockNum = blocks[i][j];
            
            if (disk[blockNum] != -1) {
                cout << "Warning: Block " << blockNum << " is already allocated to another file." << endl;
            }
            
            disk[blockNum] = i; // Mark as allocated to file i
            
            // Link current block to next block (if not the last block)
            if (j < size[i] - 1) {
                next[blockNum] = blocks[i][j + 1];
            } else {
                next[blockNum] = -1; // End of file
            }
        }
    }
    
    displayFileAllocationInfo(n, fileName, startBlock, size, next);
}

int main()
{
    int n;
    cout << "Enter the number of files: ";
    cin >> n;
    
    string fileName[n];
    int size[n];
    

    int** blocks = new int*[n];
    
    for (int i = 0; i < n; i++)
    {
        cout << "For File " << i + 1 << endl;
        cout << "Enter the file name: ";
        cin >> fileName[i];
        cout << "Enter the size of the file (number of blocks): ";
        cin >> size[i];
        
        // Allocate memory for this file's blocks
        blocks[i] = new int[size[i]];
        
        cout << "Enter " << size[i] << " block numbers where file will be stored:" << endl;
        
        for (int j = 0; j < size[i]; j++) {
            cout << "Block " << j+1 << ": ";
            cin >> blocks[i][j];
            
            // Validate block number is within disk size
            if (blocks[i][j] < 0 || blocks[i][j] >= 100) {
                cout << "Block number must be between 0 and 99. Please re-enter: ";
                cin >> blocks[i][j];
            }
        }
    }
    
    cout << endl;
    cout << "Linked File Allocation:" << endl;
    linkedfileallocation(n, fileName, size, blocks);
    cout << endl;
    
    // Clean up dynamically allocated memory
    for (int i = 0; i < n; i++) {
        delete[] blocks[i];
    }
    delete[] blocks;
    
    return 0;
}