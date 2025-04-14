#include <iostream>
#include <stdlib.h> 

#define MAX_REQUESTS 100

using namespace std;

int calculateHeadMovement(int order[], int size, int head) {
    int movement = 0;
    int current = head;
    
    for (int i = 0; i < size; i++) {
        movement += abs(order[i] - current);
        current = order[i];
    }
    
    return movement;
}

void fcfs(int requests[], int order[], int size) {
    for (int i = 0; i < size; i++) {
        order[i] = requests[i];
    }
}

void sstf(int requests[], int order[], int size, int head) {
    bool visited[MAX_REQUESTS] = {false};
    int current = head;
    
    for (int i = 0; i < size; i++) {
        int minDistance = 9999;
        int minIndex = -1;
        
        for (int j = 0; j < size; j++) {
            if (!visited[j]) {
                int distance = abs(requests[j] - current);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = j;
                }
            }
        }
        
        visited[minIndex] = true;
        order[i] = requests[minIndex];
        current = requests[minIndex];
    }
}

int scan(int requests[], int order[], int size, int head, int diskSize) {
    int lessThanHead[MAX_REQUESTS];
    int greaterThanHead[MAX_REQUESTS];
    int lessCount = 0, greaterCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (requests[i] < head) {
            lessThanHead[lessCount++] = requests[i];
        } else if (requests[i] > head) {
            greaterThanHead[greaterCount++] = requests[i];
        }
    }
    
    for (int i = 0; i < greaterCount - 1; i++) {
        for (int j = 0; j < greaterCount - i - 1; j++) {
            if (greaterThanHead[j] > greaterThanHead[j + 1]) {
                int temp = greaterThanHead[j];
                greaterThanHead[j] = greaterThanHead[j + 1];
                greaterThanHead[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < lessCount - 1; i++) {
        for (int j = 0; j < lessCount - i - 1; j++) {
            if (lessThanHead[j] < lessThanHead[j + 1]) {
                int temp = lessThanHead[j];
                lessThanHead[j] = lessThanHead[j + 1];
                lessThanHead[j + 1] = temp;
            }
        }
    }
    
    int orderIndex = 0;
    
    for (int i = 0; i < greaterCount; i++) {
        order[orderIndex++] = greaterThanHead[i];
    }
    
    order[orderIndex++] = diskSize - 1;
    
    for (int i = 0; i < lessCount; i++) {
        order[orderIndex++] = lessThanHead[i];
    }
    
    return orderIndex;
}

int look(int requests[], int order[], int size, int head) {
    int lessThanHead[MAX_REQUESTS];
    int greaterThanHead[MAX_REQUESTS];
    int lessCount = 0, greaterCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (requests[i] < head) {
            lessThanHead[lessCount++] = requests[i];
        } else if (requests[i] > head) {
            greaterThanHead[greaterCount++] = requests[i];
        }
    }
    
    for (int i = 0; i < greaterCount - 1; i++) {
        for (int j = 0; j < greaterCount - i - 1; j++) {
            if (greaterThanHead[j] > greaterThanHead[j + 1]) {
                int temp = greaterThanHead[j];
                greaterThanHead[j] = greaterThanHead[j + 1];
                greaterThanHead[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < lessCount - 1; i++) {
        for (int j = 0; j < lessCount - i - 1; j++) {
            if (lessThanHead[j] < lessThanHead[j + 1]) {
                int temp = lessThanHead[j];
                lessThanHead[j] = lessThanHead[j + 1];
                lessThanHead[j + 1] = temp;
            }
        }
    }
    
    int orderIndex = 0;
    
    for (int i = 0; i < greaterCount; i++) {
        order[orderIndex++] = greaterThanHead[i];
    }
    
    for (int i = 0; i < lessCount; i++) {
        order[orderIndex++] = lessThanHead[i];
    }
    
    return orderIndex;
}

void displayResults(const char* algorithm, int order[], int size, int head) {
    cout << "\n" << algorithm << " Algorithm:" << std::endl;
    cout << "Order of requests: ";
    for (int i = 0; i < size; i++) {
        cout << order[i] << " ";
    }
    cout << "\nTotal head movement: " << calculateHeadMovement(order, size, head) << std::endl;
}

int main() {
    int diskSize, numRequests, head;
    int requests[MAX_REQUESTS];
    int order[MAX_REQUESTS * 2];
    
    cout << "Enter the disk size: ";
    cin >> diskSize;
    
    cout << "Enter the current head position: ";
    cin >> head;
    
    cout << "Enter the number of requests: ";
    cin >> numRequests;
    
    cout << "Enter the requests: ";
    for (int i = 0; i < numRequests; i++) {
        std::cin >> requests[i];
    }
    
    fcfs(requests, order, numRequests);
    displayResults("FCFS", order, numRequests, head);
    
    sstf(requests, order, numRequests, head);
    displayResults("SSTF", order, numRequests, head);
    
    int scanSize = scan(requests, order, numRequests, head, diskSize);
    displayResults("SCAN", order, scanSize, head);
    
    int lookSize = look(requests, order, numRequests, head);
    displayResults("LOOK", order, lookSize, head);
    
    return 0;
}