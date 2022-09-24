#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T val;
    Node *left;
    Node *right;
    int height, freq, count;

    Node(T key)
    {
        val = key;
        freq = 1, height = 1;
        left = right = NULL;
        count = 1;
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

    void delete (T key)
    {
        root = deletenode(root, key);
    }

    bool search(T key)
    {
        return search(root, key);
    }

    int count(Node<T> *node)
    {
        return (node ? node->count : 0);
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

    T upper_bound(T key)
    {
        Node<T> *result = solve_upper_bound(root, NULL, key);
        return (!result ? T() : result->val);
    }

    Node<T> *solve_upper_bound(Node<T> *node, Node<T> *temp, T key)
    {
        if (!node)
            return temp;

        if (node->val == key)
        {
            if (node->right)
            {
                Node<T> *temp1 = node->right;
                while (temp1->left)
                    temp1 = temp1->left;
                return temp1;
            }
        }
        else if (node->val > key)
            return solve_upper_bound(node->left, node, key);
        else
            return solve_upper_bound(node->right, temp, key);

        return temp;
    }

    T lower_bound(T key)
    {
        Node<T> *result = solve_lower_bound(root, NULL, key);
        return (!result ? T() : result->val);
    }

    Node<T> *solve_lower_bound(Node<T> *node, Node<T> *temp, T key)
    {
        if (!node)
            return temp;

        if (node->val == key)
            return node;
        else if (node->val > key)
            return solve_lower_bound(node->left, node, key);
        else
            return solve_lower_bound(node->right, temp, key);

        return temp;
    }

    Node<T> *maximum(Node<T> *root)
    {
        while (root->right)
            root = root->right;

        return root;
    }

    Node<T> *predecessor(Node<T> *node, Node<T> *temp, int key)
    {
        if (!node)
            return temp;

        if (node->val == key)
        {
            if (node->left)
            {
                Node<T> *temp1 = node->left;
                while (temp1->right)
                    temp1 = temp1->right;
                return temp1;
            }
        }
        else if (node->val > key)
            return predecessor(node->left, temp, key);
        else
            return predecessor(node->right, node, key);

        return temp;
    }

    T closest_element(T key)
    {
        Node<T> *result = solve_closest_element(root, key);
        return result->val;
    }

    Node<T> *solve_closest_element(Node<T> *root, T key)
    {
        Node<T> *temp = solve_lower_bound(root, NULL, key);
        Node<T> *temp1 = predecessor(root, NULL, key);
        if (temp)
        {
            if (temp->val == key || !temp1)
                return temp;
            else
            {
                T rightside = temp->val - key;
                T leftside = temp1->val - key;

                if (rightside < leftside)
                    return temp;
                else
                    return temp1;
            }
        }
        return maximum(root);
    }

    T Kth_largest(int k)
    {
        return solve_kth_largest(root, k);
    }

    int count_range(T left, T right)
    {
        return solve_count_range(root, left, right);
    }

    int solve_count_range(Node<T> *node, T left, T right)
    {
        if (!node)
            return 0;
        if (node->val == left && node->val == right)
            return node->freq;
        if (node->val <= right && node->val >= left)
            return node->freq + solve_count_range(node->left, left, right) + solve_count_range(node->right, left, right);
        else if (node->val > right)
            return solve_count_range(node->left, left, right);
        else
            return solve_count_range(node->right, left, right);
    }

    T solve_kth_largest(Node<T> *node, int k)
    {
        if (k < 0 || !node)
            return 0;
        if (k <= count(node->right))
            return solve_kth_largest(node->right, k);
        else if (k <= count(node->right) + node->freq)
            return node->val;
        else
            return solve_kth_largest(node->left, k - count(node->right) - node->freq);
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

        node->count = node->freq + count(node->left) + count(node->right);
        temp->count = temp->freq + count(temp->left) + count(temp->right);

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

        node->count = node->freq + count(node->left) + count(node->right);
        temp->count = temp->freq + count(temp->left) + count(temp->right);

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
            root->count++;
        }
        else if (key > root->val)
        {
            root->right = insertnode(root->right, key);
            root->count++;
        }
        else
        {
            root->freq += 1;
            root->count++;
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

    cout << "[" << temp->val << ":" << temp->freq << "| " << temp->count << " | {" << temp->height - 1 << "}]" << endl;

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
    int arr[] = {1, 1, 2, 2, 2, 5};

    for (int i : arr)
        avl.insert(i);

    cout << avl.closest_element(1) << endl;
    cout << avl.closest_element(3) << endl;
    cout << avl.closest_element(4) << endl;
    cout << avl.closest_element(80) << endl;

    // cout << avl.count_range(1, 6) << " ";
    // cout << avl.count_range(2, 3) << " ";
    // cout << avl.count_range(2, 2) << " ";
    // cout << avl.count_range(3, 10) << endl;

    // for (int i = 1; i <= 9; i++)
    //     cout << avl.Kth_largest(i) << " ";
    // // cout << endl;
    // cout << avl.Kth_largest(90) << endl;
    // cout << avl.count_occurence(9) << endl;
    // cout << avl.count_occurence(2) << endl;
    // cout << avl.count_occurence(4) << endl;
    // cout << avl.count_occurence(-1) << endl;

    // cout << avl.search(90) << endl;
    printAVL<int>(avl.root, 0);

    return 0;
}