#include <iostream>
#include <queue>

using namespace std;

struct btnode
{
    int value;
    btnode *left;
    btnode *right;
    btnode(int value)
    {
        this->value = value;
        left = NULL;
        right = NULL;
    }
};

void freeTree(btnode *root);

struct tree
{
    btnode *root;
    tree()
    {
        root = NULL;
    }
    ~tree()
    {
        freeTree(root);
    }
};

int nodenum(btnode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return nodenum(root->left) + nodenum(root->right) + 1;
}

void preOrder(btnode *root)
{
    while (root != NULL)
    {
        cout << root->value << endl;
        preOrder(root->left);
        root = root->right;
    }
}

void inOrder(btnode *root)
{
    while (root != NULL)
    {
        inOrder(root->left);
        cout << root->value << endl;
        root = root->right;
    }
}

void postOrder(btnode *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->value << endl;
}

void freeTree(btnode *root)
{
    while (root != NULL)
    {
        btnode *left = root->left;
        btnode *right = root->right;
        delete root;
        freeTree(left);
        root = right;
    }
}

void bfs(btnode *root)
{
    if (root == NULL)
    {
        return;
    }
    queue<btnode *> q;
    q.push(root);
    while (!q.empty())
    {
        btnode *front = q.front();
        q.pop();
        cout << front->value << endl;
        if (front->left != NULL)
        {
            q.push(front->left);
        }
        if (front->right != NULL)
        {
            q.push(front->right);
        }
    }
}

int main()
{
    tree t;
    t.root = new btnode(3);
    t.root->left = new btnode(4);
    t.root->right = new btnode(1);
    t.root->left->left = new btnode(0);
    t.root->left->right = new btnode(9);
    // cout << nodenum(t.root) << endl;
    // postOrder(t.root);
    bfs(t.root);

    system("pause");
    return 0;
}