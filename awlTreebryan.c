#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    int height; 
};

struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; 
    return newNode;
}

int height(struct TreeNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

struct TreeNode *rightRotate(struct TreeNode *y)
{
    struct TreeNode *x = y->left;
    struct TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

struct TreeNode *leftRotate(struct TreeNode *x)
{
    struct TreeNode *y = x->right;
    struct TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

int getBalance(struct TreeNode *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}


struct TreeNode *insertNode(struct TreeNode *node, int data)
{
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else 
        return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printPreOrder(struct TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

struct TreeNode *balanceBST(struct TreeNode *root, int *sortedArr, int start, int end)
{
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    root = createNode(sortedArr[mid]);

    root->left = balanceBST(root->left, sortedArr, start, mid - 1);
    root->right = balanceBST(root->right, sortedArr, mid + 1, end);

    return root;
}

int main()
{
    int input[] = {1, 2, 3, 4, 5};
    int n = sizeof(input) / sizeof(input[0]);

    struct TreeNode *root = NULL;
    for (int i = 0; i < n; i++)
    {
        root = insertNode(root, input[i]);
    }

    printf("BST Pre-order: ");
    printPreOrder(root);
    printf("\n");

    int sortedArr[n];
    int index = 0;
    void getSortedArray(struct TreeNode * root)
    {
        if (root != NULL)
        {
            getSortedArray(root->left);
            sortedArr[index++] = root->data;
            getSortedArray(root->right);
        }
    }
    getSortedArray(root);

    root = balanceBST(root, sortedArr, 0, n - 1);

    printf("Balanced-AVL Pre-order: ");
    printPreOrder(root);
    printf("\n");

    return 0;
}
