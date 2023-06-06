#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node_t
{
    int data;
    struct Node_t *left;
    struct Node_t *right;
} Node_t, *Node;

Node newNode(int data)
{
    Node node = (Node)calloc(1, sizeof(Node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node insertIntoBst(Node root,int data)
{
    if(root==NULL)
    {
        root = newNode(data);
        return root;
    }
    if(data>root->data)
    {
        root->right = insertIntoBst(root->right,data);
    }
    else if(data<=root->data)
    {
        root->left = insertIntoBst(root->left,data);
    }

    return root;

}

Node minVal(Node root)
{
    while(root->left!=NULL)
    {
        root=root->left;
    }
    return root;
}

Node deleteFromBst(Node root,int data)
{
    if(root==NULL)
    {
        return root;
    }
    if(root->data==data)
    {

        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }

        if(root->left!=NULL && root->right==NULL)
        {
            Node temp = root->left;
            free(root);
            return temp;
        }

        if(root->right!=NULL && root->left==NULL)
        {
            Node temp = root->right;
            free(root);
            return temp;
        }

        if(root->right!=NULL && root->left!=NULL)
        {
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deleteFromBst(root->right,mini);
            return root;

        }
    }
    else if(data>root->data)
    {
        root->right = deleteFromBst(root->right,data);
        return root;
    }
    else
    {
        root->left = deleteFromBst(root->left,data);
        return root;
    }
}


void inorder(Node root)
{
    if(root==NULL)
    {
        return ;
    }

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);

}


int main()
{

    int n;
    scanf("%d",&n);

    Node root = NULL;

    for(int i = 0;i<n;i++)
    {
        int num;
        scanf("%d",&num);
        root = insertIntoBst(root,num);
    }

    inorder(root);
    printf("\n");


    deleteFromBst(root,3);
    inorder(root);




}