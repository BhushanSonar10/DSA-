#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Tree Node Structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new Node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a Node into the Binary Tree
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else {
        if (data < root->data) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
    }
    return root;
}

// Get the number of siblings for each level
void countSiblingsPerLevel(struct Node* root, int level, int* countArr) {
    if (root == NULL)
        return;

    countArr[level]++;

    countSiblingsPerLevel(root->left, level + 1, countArr);
    countSiblingsPerLevel(root->right, level + 1, countArr);
}

// Count the number of siblings at each level
void countSiblings(struct Node* root) {
    if (root == NULL)
        return;

    int maxLevel = 0;
    // Calculate the maximum level in the binary tree
    getMaxLevel(root, 0, &maxLevel);

    int* countArr = (int*)calloc(maxLevel + 1, sizeof(int));
    countSiblingsPerLevel(root, 0, countArr);

    // Print the count of siblings at each level
    for (int i = 0; i <= maxLevel; i++) {
        printf("Level %d: %d sibling(s)\n", i, countArr[i]);
    }

    free(countArr);
}

// Calculate the maximum level in the binary tree
void getMaxLevel(struct Node* root, int level, int* maxLevel) {
    if (root == NULL)
        return;

    if (level > *maxLevel)
        *maxLevel = level;

    getMaxLevel(root->left, level + 1, maxLevel);
    getMaxLevel(root->right, level + 1, maxLevel);
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate random numbers and store them in the input file
    FILE* inputFile = fopen("input.txt", "w");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    int numCount = 10; // Number of random numbers to generate
    int minRange = 1;  // Minimum range of random numbers
    int maxRange = 100; // Maximum range of random numbers

    for (int i = 0; i < numCount; i++) {
        int num = (rand() % (maxRange - minRange + 1)) + minRange;
        fprintf(inputFile, "%d\n", num);
    }

    // Close the input file
    fclose(inputFile);

    // Open the input file
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    // Read numbers from the input file and insert into the Binary Tree
    int num;
    struct Node* root = NULL;
    while (fscanf(inputFile, "%d", &num) == 1) {
        root = insertNode(root, num);
    }

    // Close the input file
    fclose(inputFile);

    // Count the number of siblings at each level
    countSiblings(root);

    return 0;
}
