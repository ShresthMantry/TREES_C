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

typedef struct queue
{
    int front, rear;
    unsigned capacity;
    Node *arr;
} Queue_t, *Queue;

Queue newQueue(unsigned capacity)
{

    Queue q = (Queue)calloc(1, sizeof(Queue_t));
    q->front = -1;
    q->capacity = capacity;
    q->rear = -1;
    q->arr = (Node *)calloc(capacity, sizeof(Node));
    // printf("done");

    return q;
}

void push(Queue q, Node data)
{
    if (q->rear == (q->capacity - 1))
    {
        return;
    }

    if (q->front == -1)
    {
        q->front = 0;
        q->rear = 0;
        q->arr[0] = data;
    }

    else
    {
        q->rear++;
        q->arr[q->rear] = data;
    }
    // printf("done");
}

Node pop(Queue q)
{
    // printf("%d\n",st->top);
    if (q->front == -1)
    {
        return NULL;
    }

    else if (q->front == q->rear)
    {
        Node ele = q->arr[q->front];
        q->front = -1;
        q->rear = -1;
        return ele;
    }

    else
    {
        Node ele = q->arr[q->front];
        for (int i = 1; i <= q->rear; i++)
        {
            q->arr[i - 1] = q->arr[i];
        }
        q->rear--;
        return ele;
    }
}

Node buildTree(Node root)
{
    int data;
    scanf("%d", &data);

    if (data == -1)
    {
        return NULL;
    }

    root = newNode(data);
    printf("Enter data of %d -> left \n", data);
    root->left = buildTree(root->left);
    printf("Enter data of %d -> right \n", data);
    root->right = buildTree(root->right);

    return root;
}

Node buildFromLevelOrder()
{
    Node root = NULL;
    int data;
    printf("Enter root\n");
    scanf("%d", &data);

    Queue q = newQueue(20);
    root = newNode(data);
    push(q, root);

    while (q->front > -1)
    {
        Node temp = pop(q);

        printf("Enter %d -> left \n", temp->data);
        int l;
        scanf("%d", &l);

        if (l != -1)
        {
            temp->left = newNode(l);
            push(q, temp->left);
        }

        printf("Enter %d -> right \n", temp->data);
        int r;
        scanf("%d", &r);

        if (r != -1)
        {
            temp->right = newNode(r);
            push(q, temp->right);
        }
    }
    free(q);
    return root;
}

void levelOrderTraversal(Node root)
{
    Queue q = newQueue(20);
    push(q, root);
    push(q, NULL);
    while (q->front > -1)
    {
        Node temp = pop(q);

        if (temp == NULL)
        {
            printf("\n");
            if (q->front > -1)
            {
                push(q, NULL);
            }
        }
        else
        {
            printf("%d ", temp->data);

            if (temp->left)
            {
                push(q, temp->left);
            }
            if (temp->right)
            {
                push(q, temp->right);
            }
        }
    }

    free(q);
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
    Node root = NULL;
    // 1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
    root = buildTree(root);
    // levelOrderTraversal(root);
    inorder(root);
    
}