#include<stdio.h>

int front=-1,rear=-1,size=3, maxsize=3,queue[3];

void enqueue(int value)
{
    if ((rear +1) % size == front)
    {
        printf("Queue if full");
        return;
    }
    else if (front==-1)
    {
        front = 0;
    }
    rear = (rear+1)% size;
    queue[rear]=value;
    printf("\nElement inserted: %d",value);
}

int dequeue()
{
    if (front == -1)
    {
        printf("\nQueue is Empty");
        return -1;
    }

    int data = queue[front];

   
    if (front == rear) {
        front = -1;
        rear = -1;
    }
   
    else {
        front = (front + 1) % maxsize;
    }

    return data;
}

void display()
{
    if (front == -1)
    {
        printf("Queue if Empty");
        return;
    }
    printf("\n\nQueue Elements: ");
    int index = front;
    while (1)
    {
        printf("%d\t",queue[index]);
        if (index == rear)
        {
            break;
        }
        index = (index + 1) % size;

    }
    printf("\n");
}

int main()
{   
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
 
}