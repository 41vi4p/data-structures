#include <stdio.h>
#include <stdlib.h>

// A Huffman tree node
typedef struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

// Min Heap structure
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    MinHeapNode **array;
} MinHeap;

// Function to create a new min heap node
MinHeapNode* CreateNode(char data, unsigned freq) {
    MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Function to create a min heap of given capacity
MinHeap* CreateMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Utility function to swap two min heap nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify function
void Heapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        Heapify(minHeap, smallest);
    }
}

// Function to build min heap
void BuildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        Heapify(minHeap, i);
}

// Function to extract minimum value node from heap
MinHeapNode* ExtractMin(MinHeap* minHeap) {
    MinHeapNode* min = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    Heapify(minHeap, 0);
    return min;
}

// Function to insert a new node to Min Heap
void Insert(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// Print array (code)
void printArr(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

// Function to generate codes recursively
void GenerateCodes(MinHeapNode* node, int arr[], int top) {
    // Assign 0 to left edge and recur
    if (node->left) {
        arr[top] = 0;
        GenerateCodes(node->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (node->right) {
        arr[top] = 1;
        GenerateCodes(node->right, arr, top + 1);
    }

    // If this is a leaf node, print the code
    if (node->left == NULL && node->right == NULL) {
        printf("%c: ", node->data);
        printArr(arr, top);
    }
}

// The main function to build Huffman Tree and generate codes
void HuffmanCodes(char chars[], int freqs[], int size) {
    // STEP 1: Build a Min Heap
    MinHeap* minHeap = CreateMinHeap(size);
    
    for (int i = 0; i < size; ++i) {
        MinHeapNode* node = CreateNode(chars[i], freqs[i]);
        minHeap->array[i] = node;
    }
    
    minHeap->size = size;
    BuildMinHeap(minHeap);
    
    // STEP 2: Build the Huffman Tree
    while (minHeap->size > 1) {
        MinHeapNode* left = ExtractMin(minHeap);
        MinHeapNode* right = ExtractMin(minHeap);
        
        unsigned sumFreq = left->freq + right->freq;
        MinHeapNode* top = CreateNode('$', sumFreq);
        
        top->left = left;
        top->right = right;
        
        Insert(minHeap, top);
    }
    
    // STEP 3: Generate and Print Huffman Codes
    MinHeapNode* root = ExtractMin(minHeap);
    
    int arr[100]; // Array to store codes
    int top = 0;
    
    GenerateCodes(root, arr, top);
}

void calculateFrequency(char* word, char* chars, int* freqs, int* size) {
    int freq[256] = {0};
    int i, count = 0;
    
    // Count frequency of each character
    for(i = 0; word[i] != '\0'; i++) {
        freq[(unsigned char)word[i]]++;
    }
    
    // Store characters and their frequencies
    for(i = 0; i < 256; i++) {
        if(freq[i] > 0) {
            chars[count] = (char)i;
            freqs[count] = freq[i];
            count++;
        }
    }
    
    *size = count;
}

int main() {
    char word[100];
    char chars[100];
    int freqs[100];
    int size = 0;
    
    printf("Enter a word: ");
    scanf("%s", word);
    
    calculateFrequency(word, chars, freqs, &size);
    
    printf("\nCharacters and their frequencies:\n");
    for(int i = 0; i < size; i++) {
        printf("'%c': %d\n", chars[i], freqs[i]);
    }
    
    printf("\nHuffman Codes:\n");
    HuffmanCodes(chars, freqs, size);
    
    return 0;
}