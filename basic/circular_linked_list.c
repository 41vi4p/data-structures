#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//Insert at end
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    
  
    if (head == NULL) {
        head = newNode;
        head->next = head; 
        return head;
    }
    
  
    struct Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->next = head;
    return head;
}

// delete first node
struct Node* deleteFirst(struct Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    
    if (head->next == head) {
        free(head);
        return NULL;
    }
    
  
    struct Node* temp = head;
    struct Node* last = head;
    while (last->next != head) {
        last = last->next;
    }
    
    
    head = head->next;
    last->next = head;
    free(temp);
    return head;
}

//display function
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    struct Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

//search function
struct Node* search(struct Node* head, int key) {
    if (head == NULL) return NULL;
    
    struct Node* temp = head;
    do {
        if (temp->data == key) return temp;
        temp = temp->next;
    } while (temp != head);
    
    return NULL;
}

int main() {
    struct Node* head = NULL;
    int choice, data, searchKey;
    struct Node* result;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at end\n");
        printf("2. Delete first\n");
        printf("3. Display list\n");
        printf("4. Search\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 2:
                head = deleteFirst(head);
                break;
            case 3:
                display(head);
                break;
            case 4:
                printf("Enter value to search: ");
                scanf("%d", &searchKey);
                result = search(head, searchKey);
                if (result != NULL) {
                    printf("Value %d found in the list!\n", searchKey);
                } else {
                    printf("Value %d not found in the list!\n", searchKey);
                }
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}