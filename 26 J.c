#include <stdio.h>
#include <stdlib.h>
#include <time.h>
  typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
}Node;
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}
Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update the height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Check the balance factor and balance the tree if required
    int balance = getBalance(root);

    // Left Left Case (single rotation)
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Right Right Case (single rotation)
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Left Right Case (double rotation)
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case (double rotation)
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a key in the AVL tree
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Function to find the minimum value in the AVL tree
int findMinimum(Node* root) {
    if (root == NULL)
        return -1; // Tree is empty

    while (root->left != NULL)
        root = root->left;

    return root->key;
}

// Function to find the maximum value in the AVL tree
int findMaximum(Node* root) {
    if (root == NULL)
        return -1; // Tree is empty

    while (root->right != NULL)
        root = root->right;

    return root->key;
}

// Function to check if the AVL tree is balanced
int isBalanced(Node* root) {
    if (root == NULL)
        return 1;

    int balance = getBalance(root);

    if (balance > 1 || balance < -1)
        return 0;

    return isBalanced(root->left) && isBalanced(root->right);
}

// Function to perform in-order traversal of the AVL tree
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}
// Function to display the structure of the tree
void displayStructure(Node* root, int space,FILE *fp) {
    if (root == NULL)
        return;

    space += 10;

    displayStructure(root->right, space,fp);

    fprintf(fp,"\n");
    for (int i = 10; i < space; i++)
        fprintf(fp," ");
    fprintf(fp,"%d\n", root->key);

    displayStructure(root->left, space,fp);
}

int main() {
    Node* root = NULL;
    int i, num,n,key;
     FILE *fp;
     fp=fopen("avl.txt","w+");
    srand(time(0));
    fprintf(fp,"Inserting random numbers into the AVL tree:\n");
    for (i = 0; i < 10; i++) {
        num = rand() % 100;
        root = insert(root, num);
        fprintf(fp,"%d ", num);
    }
    fprintf(fp,"\n\n");
    fprintf(fp,"In-order traversal of the AVL tree: ");
    inOrder(root);
    fprintf(fp,"\n\n");
    fprintf(fp,"Structure of the AVL tree after deletion:\n");
    displayStructure(root, 0,fp);
    fprintf(fp,"\n");
    int searchKey = 55;
    Node* searchResult = search(root, searchKey);
    if (searchResult != NULL)
        fprintf(fp,"Key %d found in the AVL tree.\n", searchKey);
    else
        fprintf(fp,"Key %d not found in the AVL tree.\n", searchKey);
    printf("\n");
    int minimum = findMinimum(root);
    int maximum = findMaximum(root);
    //printf("Minimum value in the AVL tree: %d\n", minimum);
    //printf("Maximum value in the AVL tree: %d\n", maximum);
    if (isBalanced(root))
        fprintf(fp,"The AVL tree is balanced.\n");
    else
        fprintf(fp,"The AVL tree is not balanced.\n");
    fprintf(fp,"\n");
   fprintf(fp,"Performing deletion operations on the AVL tree:\n");
   printf("enter the number of elments\n");
   scanf("%d",&n);
    for (i = 0; i <n; i++) {

    scanf("%d",&key);
       fprintf(fp,"Deleting %d from the AVL tree.\n", key);
        root = deleteNode(root, key);
    }
    fprintf(fp,"\n");
    fprintf(fp,"In-order traversal of the AVL tree after deletion: ");
    inOrder(root);
    fprintf(fp,"\n\n");
    fprintf(fp,"Structure of the AVL tree after deletion:\n");
    displayStructure(root, 0,fp);
    fprintf(fp,"\n");
    if (isBalanced(root))
        fprintf(fp,"The AVL tree is balanced.\n");
    else
        fprintf(fp,"The AVL tree is not balanced.\n");

return 0;
}
