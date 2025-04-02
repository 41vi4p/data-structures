//C program to allocate each process to each block
// of memory using first fit algorithm
#include <stdio.h>
#include <stdlib.h>


int blockSize[] = {150, 350, 400, 500, 600};
// int blockSize[] = {15, 50, 40, 80, 60};
int processSize[] = {300, 25, 125, 50};
int choice = 2;

//allocate memory to first fit algorithm

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    
    int allocation[n]; //store block id allocated to a process
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                
                allocation[i] = j;

                blockSize[j] -= processSize[i];

                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}


//best fit
void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n]; 
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j])
                    {bestIdx = j ;
                        printf("%d\n", bestIdx);
            
                            }        }
        }


    }
    
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}



int main()
{
    
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    switch (choice)
    {
    case 1:
        firstFit(blockSize, m, processSize, n);
        break;

    case 2:
        bestFit(blockSize, m, processSize, n);
        break;
    
    default:
        printf("Invalid choice\n");
        break;
    }
    
    return 0;
}

