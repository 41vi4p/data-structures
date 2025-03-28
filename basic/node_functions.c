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

void deleteAtStart(Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void deleteAtPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (position == 0) {
        deleteAtStart(head);
        return;
    }
    Node* temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range\n");
        return;
    }
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

void reverseList(Node** head) {
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

int searchList(Node* head, int key) {
    int position = 0;
    while (head != NULL) {
        if (head->data == key) {
            return position;
        }
        head = head->next;
        position++;
    }
    return -1;
}

int main() {
    Node* head = NULL;
    int choice, data, position, key;

    while (1) {
        printf("\n1. Insert at Start");
        printf("\n2. Insert at End");
        printf("\n3. Display List");
        printf("\n4. Insert at Middle");
        printf("\n5. Delete at Start");
        printf("\n6. Delete at End");
        printf("\n7. Delete at Position");
        printf("\n8. Reverse List");
        printf("\n9. Search List");
        printf("\n10. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
                deleteAtStart(&head);
                break;

            case 6:
                deleteAtEnd(&head);
                break;

            case 7:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;

            case 8:
                reverseList(&head);
                break;

            case 9:
                printf("Enter data to search: ");
                scanf("%d", &key);
                position = searchList(head, key);
                if (position != -1) {
                    printf("Element found at position: %d\n", position);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 10:
                printf("Exiting program\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

