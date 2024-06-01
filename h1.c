#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HT 100

// A Huffman tree node
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of MinHeapNode (or Huffman tree nodes)
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

// Utility function to allocate a new MinHeapNode
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Standard minHeapify function
void minHeapify(struct MinHeap* minHeap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != i) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[i]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Function to extract the two minimum frequency nodes from the heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Function to build the Huffman tree and store it in minHeap
struct MinHeap* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        insertMinHeap(minHeap, newNode(data[i], freq[i]));
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return minHeap;
}

// Function to print an array of size n
void printArr(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d", arr[i]);
}

// Utility function to print codes stored in Huffman tree
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        printArr(arr, top);
        printf("\n");
    }
}



// Function to get Huffman codes from the Huffman tree
void getCode(struct MinHeapNode* root, char data, int code[], int index, int* found) {
    if (*found)
        return;

    if (root == NULL)
        return;

    if (root->data == data) {
        *found = index;
        return;
    }

    code[index] = 0;
    getCode(root->left, data, code, index + 1, found);
    if (*found == 0) {
        code[index] = 1;
        getCode(root->right, data, code, index + 1, found);
    }
}


// Function to encode input string
void encodeHuffman(struct MinHeapNode* root, char* inputString) {
    printf("ENCODED STRING: ");
    while (*inputString) {
        int bit;
      
        
            int code[HT] = {0};
            int found = 0;
            getCode(root, *inputString, code, 0, &found);
            printArr(code, found);
        
        ++inputString;
    }
    printf("\n");
}


// Function to decode Huffman encoded string
void decodeHuffman(struct MinHeapNode* root, char* encodedString) {
    struct MinHeapNode* temp = root;
    printf("DECODED STRING: ");
    for (int i = 0; encodedString[i] != '\0'; ++i) {
        if (encodedString[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;

        if (temp->left == NULL && temp->right == NULL) {
            printf("%c", temp->data);
            temp = root;
        }
    }
}

// Main function
int main() {
    printf("\t\t\t\t \033[1;33m     #########################################################               \n");
    usleep(80000);
    printf("\t\t\t\t \033[1;33m     ##                                                     ##               \n");
    usleep(80000);
    printf("\t\t\t\t \033[1;33m     ##               \033[1;34m ENCODER AND DECODER       \033[1;33m           ##               \n");
    usleep(80000);
    printf("\t\t\t\t \033[1;33m     ## \033[1;34m      USING HUFFMAN ENCODING TECHNIQUE  \033[1;33m            ##               \n");
    usleep(80000);
    printf("\t\t\t\t \033[1;33m     ##                                                     ##               \n");
    usleep(80000);
    printf("\t\t\t\t \033[1;33m     #########################################################               \n");
    usleep(80000);
    printf("\033[1;0m");
    char inputString[100];
    printf("Enter a string to encode: ");
    fgets(inputString, sizeof(inputString), stdin);
    inputString[strcspn(inputString, "\n")] = '\0'; // Remove newline character

    int freq[256] = {0}; // Assuming ASCII characters
    for (int i = 0; inputString[i] != '\0'; i++)
        freq[inputString[i]]++;

    int size = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0)
            size++;
    }

    char data[size];
    int frequency[size];
    int j = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            data[j] = i;
            frequency[j] = freq[i];
            j++;
        }
    }

    struct MinHeap* minHeap = buildHuffmanTree(data, frequency, size);

    int arr[HT], top = 0;
    printf("Huffman Codes For Entered String:\n");
    printCodes(minHeap->array[0], arr, top);

    encodeHuffman(minHeap->array[0], inputString);

    printf("\n");

    // Decoding Example
    printf("ENTER THE ENCODE OF STRING TO DECODE: ");
    char encodedString[100];
    fgets(encodedString, sizeof(encodedString), stdin);
    encodedString[strcspn(encodedString, "\n")] = '\0'; // Remove newline character

    decodeHuffman(minHeap->array[0], encodedString);

    printf("\n");

printf("\t\t\t\t********************* \033[1;34mEND OF PROGRAMME \033[1;0m***********************\n");
printf("\n");
    return 0;
}

