#include<stdio.h>

int front=-1,rear=-1,size=5, maxsize=5,queue[5];

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

void dequeue(int value)
{
    if (front == -1)
    {
        printf("\nQueue if Empty");
        return -1;
    }
    
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
    int value = 10;
    enqueue(value);
    enqueue(20);
    enqueue(30);
    display();
}