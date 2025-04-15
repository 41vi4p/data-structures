#include <stdio.h>   // For input/output operations
#include <stdlib.h>  // For memory allocation functions

// Structure to represent each term in the polynomial
// Each term has coefficient, exponent and pointer to next term
struct Node {
    int coeff;          // Coefficient of the term
    int exp;            // Exponent of the term
    struct Node* next;  // Pointer to the next term
};

// Function to create a new node for polynomial term
struct Node* createNode(int coeff, int exp) {
    // Allocate memory for new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // Check if memory allocation was successful
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    // Initialize node with given coefficient and exponent
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into polynomial in descending order of exponents
struct Node* insertTerm(struct Node* head, int coeff, int exp) {
    // Create new node with given coefficient and exponent
    struct Node* newNode = createNode(coeff, exp);
    
    // If list is empty or new term has higher exponent than head
    if (head == NULL || head->exp < exp) {
        newNode->next = head;
        head = newNode;
    } else {
        // Traverse to find correct position to insert
        struct Node* temp = head;
        while (temp->next != NULL && temp->next->exp >= exp) {
            temp = temp->next;
        }
        // Insert new node at correct position
        newNode->next = temp->next;
        temp->next = newNode;
    }
    return head;
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;  // To store resultant polynomial
    struct Node* p1 = poly1;     // Pointer to traverse first polynomial
    struct Node* p2 = poly2;     // Pointer to traverse second polynomial

    // While both polynomials have terms remaining
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            // If exponents are equal, add coefficients
            result = insertTerm(result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            // If p1's exponent is higher, add p1's term
            result = insertTerm(result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            // If p2's exponent is higher, add p2's term
            result = insertTerm(result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    // Add remaining terms from first polynomial
    while (p1 != NULL) {
        result = insertTerm(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    // Add remaining terms from second polynomial
    while (p2 != NULL) {
        result = insertTerm(result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Function to display polynomial in readable format
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        // Print each term in format: coefficient x^exponent
        printf("%dx^%d", temp->coeff, temp->exp);
        temp = temp->next;
        // Print plus sign between terms
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to input polynomial from user
struct Node* inputPolynomial() {
    struct Node* poly = NULL;
    int n, coeff, exp;
    n = 4;  // Fixed number of terms (4)
    
    // Input each term's coefficient and exponent
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coeff, &exp);
        poly = insertTerm(poly, coeff, exp);
    }
    return poly;
}

// Main function
int main() {
    struct Node* poly1 = NULL;   // First polynomial
    struct Node* poly2 = NULL;   // Second polynomial
    struct Node* result = NULL;  // Resultant polynomial

    // Input first polynomial
    printf("Enter the first polynomial:\n");
    poly1 = inputPolynomial();

    // Input second polynomial
    printf("Enter the second polynomial:\n");
    poly2 = inputPolynomial();

    // Display both polynomials
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Add polynomials and display result
    result = addPolynomials(poly1, poly2);
    printf("Resultant Polynomial: ");
    displayPolynomial(result);

    return 0;
}