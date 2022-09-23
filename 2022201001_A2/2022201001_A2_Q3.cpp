#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T val;
    Node *left;
    Node *right;
    int height, freq, lcount, rcount;

    Node(T key)
    {
        val = key;
        freq = 1, height = 1;
        left = right = NULL;
        lcount = rcount = 0;
    }
};

template <typename T>
class AVL
{
public:
    Node<T> *root = NULL;

    void insert(T key)
    {
        root = insertnode(root, key);
    }

    bool search(T key)
    {
        return search(root, key);
    }

    int count_occurence(T key)
    {
        return count_occurence(root, key);
    }

    int count_occurence(Node<T> *root, T key)
    {
        if (!root)
            return 0;
        if (root->val > key)
            return count_occurence(root->left, key);
        else if (root->val < key)
            return count_occurence(root->right, key);
        else
            return root->freq;
    }

    bool search(Node<T> *root, T key)
    {
        if (!root)
            return false;
        if (root->val > key)
            return search(root->left, key);
        else if (root->val < key)
            return search(root->right, key);
        else
            return true;
    }

    Node<T> *rotate_right(Node<T> *node)
    {
        Node<T> *temp = node->left;
        Node<T> *temp1 = temp->right;

        temp->right = node;
        node->left = temp1;

        node->lcount = temp->rcount;
        temp->rcount = node->rcount + 1;

        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
        temp->height = 1 + max((temp->left ? temp->left->height : 0), (temp->right ? temp->right->height : 0));

        return temp;
    }

    Node<T> *rotate_left(Node<T> *node)
    {
        Node<T> *temp = node->right;
        Node<T> *temp1 = temp->left;

        temp->left = node;
        node->right = temp1;

        node->rcount = temp->lcount;
        temp->lcount = node->lcount + 1;

        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
        temp->height = 1 + max((temp->left ? temp->left->height : 0), (temp->right ? temp->right->height : 0));

        return temp;
    }

    Node<T> *insertnode(Node<T> *root, int key)
    {
        if (root == NULL)
        {
            Node<T> *newnode = new Node(key);
            return root = newnode;
        }
        if (key < root->val)
        {
            root->left = insertnode(root->left, key);
            root->lcount++;
        }
        else if (key > root->val)
        {
            root->right = insertnode(root->right, key);
            root->rcount++;
        }
        else
        {
            root->freq += 1;
            return root;
        }

        root->height = 1 + max((root->left ? root->left->height : 0), (root->right ? root->right->height : 0));

        int diff = (root ? ((root->left ? root->left->height : 0) - (root->right ? root->right->height : 0)) : 0);

        if (diff > 1)
        {
            if (key < root->left->val) // ll
                return rotate_right(root);
            else if (key > root->left->val) // lr
            {
                root->left = rotate_left(root->left);
                return rotate_right(root);
            }
        }
        else if (diff < -1)
        {
            if (key > root->right->val) // rr
                return rotate_left(root);
            else if (key < root->right->val) // rl
            {
                root->right = rotate_right(root->right);
                return rotate_left(root);
            }
        }

        return root;
    }
};

template <typename T>
void printAVL(Node<T> *root, int depth)
{
    if (root == NULL)
    {
        cout << "X" << endl;
        return;
    }

    Node<T> *temp = root;

    cout << "[" << temp->val << ":" << temp->freq << "| " << temp->lcount << ", " << temp->rcount << " | {" << temp->height - 1 << "}]" << endl;

    for (int i = 0; i < depth; ++i)
    {
        cout << "     ";
    }
    cout << "├──";
    printAVL(root->left, depth + 1);

    for (int i = 0; i < depth; ++i)
    {
        cout << "     ";
    }
    cout << "└──";
    printAVL(root->right, depth + 1);
}

int main()
{
    AVL<int> avl;
    int arr[] = {1, 1, 2, 2, 2, 3};

    for (int i = 0; i < 6; i++)
        avl.insert(arr[i]);

    // cout << avl.count_occurence(9) << endl;
    // cout << avl.count_occurence(2) << endl;
    // cout << avl.count_occurence(4) << endl;
    // cout << avl.count_occurence(-1) << endl;

    // cout << avl.search(90) << endl;
    printAVL<int>(avl.root, 0);

    return 0;
}