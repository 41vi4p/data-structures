#include<stdio.h>

int top=-1, n, stack[10];
void push();
void pop();
void show();

void main()
{
    int choice,mainlp=1;
    printf("\n***************Stack Implementation***************");
    printf("\n--------------------------------------------------\n");
    printf("Enter number of elements in the stack: ");
    scanf("%d", &n);

    while(mainlp!=0){
    printf("\n\nMenu:\n1. PUSH \n2. POP\n3. SHOW\n4. EXIT\n");
    printf("Enter choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        push();
        break;
    case 2:
        pop();
        break;

    case 3: 
        show();
        break;
    
    case 4:
        mainlp = 0;
        break;

    default:
        printf("Invalid Input!!");
        break;
    }
    }
}

void push()
{
    if(top == n)
    {
        printf("------------------------Stack Overflow------------------------");
    }
    else{
        printf("Enter value: ");
        top = top+1;
        scanf("%d",&stack[top]);
        
    }
}


void pop()
{
    if(top == -1)
    {
        printf("------------------------Stack Underflow------------------------");
    }
    else{
        printf("\nValue: %d",stack[top]);
        top = top-1;
    }
}

void show()
{
    for(int i=top;i>=0;i--)
        {
            printf("Value[%d]: %d\n",i,stack[i]);
        }
        
    

}