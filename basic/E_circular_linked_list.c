#include <stdio.h>   // For input/output functions
#include <stdlib.h>  // For memory allocation and exit()

// Define the structure for a node in circular linked list
struct Node {
    int data;           // Stores the actual value
    struct Node* next;  // Pointer to the next node in the list
};

// Function to create a new node with given data
struct Node* createNode(int data) {
    // Dynamically allocate memory for new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // Check if memory allocation was successful
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;    // Store the data
    newNode->next = NULL;    // Initialize next pointer to NULL
    return newNode;          // Return the newly created node
}

// Function to insert a node at the end of circular list
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);  // Create new node
    
    // If list is empty, make the new node point to itself
    if (head == NULL) {
        head = newNode;
        head->next = head;  // Make it circular by pointing to itself
        return head;
    }
    
    // Traverse to find the last node
    struct Node* temp = head;
    while (temp->next != head) {  // Loop until we reach back to head
        temp = temp->next;
    }
    
    // Insert the new node at the end and make it circular
    temp->next = newNode;
    newNode->next = head;  // Point back to head to maintain circularity
    return head;
}

// Function to delete the first node
struct Node* deleteFirst(struct Node* head) {
    // Check if list is empty
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    // If only one node exists
    if (head->next == head) {
        free(head);     // Free the memory
        return NULL;    // Return NULL as list becomes empty
    }
    
    // Find the last node
    struct Node* temp = head;
    struct Node* last = head;
    while (last->next != head) {
        last = last->next;
    }
    
    // Update the head and maintain circularity
    head = head->next;      // Move head to next node
    last->next = head;      // Update last node's next to new head
    free(temp);            // Free the old head node
    return head;
}

// Function to display the circular list
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    // Use do-while to ensure at least one iteration
    struct Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);  // Continue until we reach head again
    printf("(head)\n");     // Indicate the circular nature
}

// Function to search for a value in the list
struct Node* search(struct Node* head, int key) {
    if (head == NULL) return NULL;  // Empty list
    
    struct Node* temp = head;
    do {
        if (temp->data == key) return temp;  // Return node if key found
        temp = temp->next;
    } while (temp != head);  // Continue until we reach head again
    
    return NULL;  // Return NULL if key not found
}

// Main function - Driver code
int main() {
    struct Node* head = NULL;  // Initialize empty list
    int choice, data, searchKey;
    struct Node* result;

    // Menu-driven program
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at end\n");
        printf("2. Delete first\n");
        printf("3. Display list\n");
        printf("4. Search\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle user choices
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
                exit(0);  // Exit program
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}