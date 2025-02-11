#include<stdio.h>

#define MAX_SIZE 5
int queue[MAX_SIZE];
int front = -1, rear = -1;

// Check if queue is full
int isFull() {
    return rear == MAX_SIZE - 1;
}

// Check if queue is empty
int isEmpty() {
    return front == -1 || front > rear;
}

// Add element to queue
void enqueue(int value) {
    if (isFull()) {
        printf("\nQueue is Full!");
        return;
    }
    if (front == -1) 
        front = 0;
    queue[++rear] = value;
    printf("\nInserted %d", value);
}

// Remove element from queue
int dequeue() {
    if (isEmpty()) {
        printf("\nQueue is Empty!");
        return -1;
    }
    int value = queue[front++];
    if (front > rear) {
        front = rear = -1;  // Reset queue when last element is removed
    }
    return value;
}

// Display queue elements
void display() {
    if (isEmpty()) {
        printf("\nQueue is Empty!");
        return;
    }
    printf("\nQueue elements: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
}

int main() {
    int choice, value;
    
    while(1) {
        printf("\n\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\nEnter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
                
            case 2:
                value = dequeue();
                if (value != -1)
                    printf("\nDequeued: %d", value);
                break;
                
            case 3:
                display();
                break;
                
            case 4:
                return 0;
                
            default:
                printf("\nInvalid choice!");
        }
    }
    return 0;
}