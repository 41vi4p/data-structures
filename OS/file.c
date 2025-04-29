#include<stdio.h>
#include<stdlib.h>

typedef struct Block
{
    int blockNum;
    struct Block* next;
}Block;

void sequential(int startingBlock, int fileSize)
{
    int i;
    printf("Block allocation details:\nStarting Block: %d\n", startingBlock);
    for(i=1; i<fileSize; i++)
        printf("%d\n", startingBlock+i);
}

void linked(int startBlock, int fileSize)
{
    int i;
    int* blockArr = (int*)malloc(fileSize * sizeof(int));
    
    printf("\nEnter the blocks where file will be stored:\n");
    for(i=0; i<fileSize-1; i++)
    {
        printf("Block %d: ", i+1);
        scanf("%d", &blockArr[i]);
    }
    
    printf("File stored at following blocks:\nStarting Block: %d\n", startBlock);
    for(i=0; i<fileSize-1; i++)
        printf("%d\n", blockArr[i]);
    
    free(blockArr);
}

void indexed(int sb, int size)
{
    int i;
    int indexBlock;
    int* blocks = (int*)malloc(100);
    printf("\nEnter index block:\n");
    scanf("%d", &indexBlock);

    printf("\nEnter the blocks:\n");
    for(i=0; i<size-1; i++)
    {
        scanf("%d", &blocks[i]);
    }

    printf("Blocks are:\nIndex Block: %d\n", indexBlock);
    for(i=0; i<size-1; i++)
        printf("%d\n", blocks[i]);
}

void displayAllocatedBlocks(int nofile, char filenames[][50], int startBlocks[], int sizes[], int methods[]) {
    int i;
    printf("\n\n-------- ALLOCATION SUMMARY --------\n");
    printf("%-15s %-15s %-15s %-15s\n", "File Name", "Start Block", "Size", "Method");
    printf("---------------------------------------------\n");
    
    for(i = 0; i < nofile; i++) {
        printf("%-15s %-15d %-15d ", filenames[i], startBlocks[i], sizes[i]);
        
        switch(methods[i]) {
            case 1: printf("Sequential\n"); break;
            case 2: printf("Linked\n"); break;
            case 3: printf("Indexed\n"); break;
            default: printf("Unknown\n");
        }
    }
    printf("---------------------------------------------\n");
}

int main()
{
    int nofile, sb, size, i, choice;
    printf("\nFile Allocation Simulator\n");
    printf("Enter number of files: ");
    scanf("%d", &nofile);
    
    char filename[5][50];
    int startBlocks[5], fileSizes[5], allocationMethods[5];
    
    for(i=0; i<nofile; i++)
    {
        printf("\n----- File %d Information -----\n", i+1);
        printf("Enter File name: ");
        scanf("%s", filename[i]); 2023016400966635
        printf("Enter starting block: ");
        scanf("%d", &sb);
        printf("Enter file size (in blocks): ");
        scanf("%d", &size);
        printf("\nSelect allocation method:\n");
        printf("1. Sequential Allocation\n");
        printf("2. Linked Allocation\n");
        printf("3. Indexed Allocation\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice==1)
            sequential(sb,size);
        else if(choice==2)
            linked(sb,size);
        else if(choice==3)
            indexed(sb,size);
        else
            printf("Invalid selection! Please try again.\n");
            
        startBlocks[i] = sb;
        fileSizes[i] = size;
        allocationMethods[i] = choice;
    }
    
    displayAllocatedBlocks(nofile, filename, startBlocks, fileSizes, allocationMethods);
    
    return 0;
}