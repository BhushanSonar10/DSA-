
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
struct node {
  int data;
  struct node *left, *right;
};
FILE *fp,*in,*pre,*post;

struct node *createNode(int item) {
  struct node* newNode = (struct node *)malloc(sizeof(struct node));
  newNode->data = item;
  newNode->left = newNode->right = NULL;
  return newNode;
}

struct node*insert(struct node*root,int val){
    if(root==NULL) {
        root=createNode(val);
        return root;
    }
    if(root->data>val){
        root->left=insert(root->left,val);
    }else{
        root->right=insert(root->right,val);
    }
    return root;
}
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL)
        return root;


    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {

        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
            } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
