//insert at start, insert at end and insert at middle

#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node* next;
}Node;


Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode){
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void printList(Node* node)
{
    while(node){
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("null\n");
}

void insertAtStart(Node** head, int data)
{
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(Node** head, int data)
{
    Node* newNode = createNode(data);
    if(*head == NULL){
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtMiddle(Node* prevNode, int data)
{
    if(prevNode == NULL){
        printf("Previous node cannot be NULL\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}


int main() {
    Node* head = NULL;
    int choice, data,position;

    while(1) {
        printf("\n1. Insert at Start");
        printf("\n2. Insert at End");
        printf("\n3. Display List");
        printf("\n4. Insert at Middle");    
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter data to insert at start: ");
                scanf("%d", &data);
                insertAtStart(&head, data);
                break;

            case 2:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;

            case 3:
                printf("Linked List: ");
                printList(head);
                break;

            case 4:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position after which to insert (0 for first position): ");
                scanf("%d", &position);
                
                if (position == 0) {
                    insertAtStart(&head, data);
                } else {
                    Node* current = head;
                    int count = 1;
                    while (current != NULL && count < position) {
                        current = current->next;
                        count++;
                    }
                    if (current == NULL) {
                        printf("Position out of range!\n");
                    } else {
                        insertAtMiddle(current, data);
                    }
                }
                break;

            case 5:
                printf("Exiting program\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

