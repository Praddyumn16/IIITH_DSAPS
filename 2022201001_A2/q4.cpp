#include <iostream>
using namespace std;

template <typename T>
class triplet
{
public:
    int row, col;
    T val;
};

template <typename T>
class sparseArray
{
public:
    triplet<T> *arr;
    int curr_size, capacity;

    sparseArray()
    {
        curr_size = 0;
        capacity = 2;
        arr = new triplet<T>[capacity];
    }

    sparseArray(int cap)
    {
        curr_size = cap;
        capacity = cap;
        arr = new triplet<T>[capacity];
    }

    void push(int r, int c, T value)
    {
        if (curr_size == capacity)
        {
            capacity *= 2;
            triplet<T> *temp = new triplet<T>[capacity];
            for (int i = 0; i < curr_size; i++)
                temp[i] = arr[i];
            delete arr;
            arr = temp;
        }
        arr[curr_size] = {r, c, value};
        curr_size++;
    }

    void print()
    {
        for (int i = 0; i < curr_size; i++)
        {
            cout << arr[i].row << " " << arr[i].col << " " << arr[i].val << endl;
        }
    }
};

template <typename T>
sparseArray<T> addition_arr(sparseArray<T> *mat1, sparseArray<T> *mat2)
{

    sparseArray<T> result;
    int l1 = mat1->curr_size, l2 = mat2->curr_size;
    int i = 0, j = 0;
    while (i < l1 && j < l2)
    {
        triplet<T> curr1 = mat1->arr[i];
        triplet<T> curr2 = mat2->arr[j];
        if (curr1.row == curr2.row && curr1.col == curr2.col)
        {
            result.push(curr1.row, curr1.col, curr1.val + curr2.val);
            i++, j++;
        }
        else if (curr1.row != curr2.row)
        {
            if (curr1.row < curr2.row)
            {
                result.push(curr1.row, curr1.col, curr1.val);
                i++;
            }
            else
            {
                result.push(curr2.row, curr2.col, curr2.val);
                j++;
            }
        }
        else
        {
            if (curr1.col < curr2.col)
            {
                result.push(curr1.row, curr1.col, curr1.val);
                i++;
            }
            else
            {
                result.push(curr2.row, curr2.col, curr2.val);
                j++;
            }
        }
    }

    while (i < l1)
    {
        result.push(mat1->arr[i].row, mat1->arr[i].col, mat1->arr[i].val);
        i++;
    }

    while (j < l2)
    {
        result.push(mat2->arr[j].row, mat2->arr[j].col, mat2->arr[j].val);
        j++;
    }

    return result;
}

template <typename T>
sparseArray<T> transpose_arr(sparseArray<T> *mat, int r, int c)
{
    int count[c + 1];
    for (int i = 0; i <= c; i++)
        count[i] = 0;

    int len = mat->curr_size;
    for (int i = 0; i < len; i++)
        count[mat->arr[i].col]++;

    int prefix_count[c + 1];
    prefix_count[0] = 0;

    for (int i = 1; i <= c; i++)
        prefix_count[i] = count[i - 1] + prefix_count[i - 1];

    sparseArray<T> result(len);

    for (int i = 0; i < len; i++)
    {
        triplet curr = mat->arr[i];
        int temp = prefix_count[curr.col]++;
        result.arr[temp] = {curr.col, curr.row, curr.val};
    }

    return result;
}

template <typename T>
sparseArray<T> multiply_arr(sparseArray<T> *mat1, sparseArray<T> *mat2)
{
    sparseArray<T> result;
    int l1 = mat1->curr_size, l2 = mat2->curr_size;
    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < l2; j++)
        {
            if (mat1->arr[i].col == mat2->arr[j].col)
            {
                int l3 = result.curr_size;
                bool flag = false;
                for (int k = 0; k < l3; k++) // checking if this entry exists already
                {
                    if (result.arr[k].row == mat1->arr[i].row && result.arr[k].col == mat2->arr[j].row)
                    {
                        flag = true;
                        result.arr[k].val += mat1->arr[i].val * mat2->arr[j].val;
                        break;
                    }
                }
                if (!flag)
                    result.push(mat1->arr[i].row, mat2->arr[j].row, mat1->arr[i].val * mat2->arr[j].val);
            }
        }
    }
    return result;
}

template <typename T>
void print_arr(sparseArray<T> *res, int r, int c)
{
    int k = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (k < res->curr_size && res->arr[k].row == i && res->arr[k].col == j)
                cout << res->arr[k++].val << " ";
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
}

template <typename T>
class Node
{
public:
    int row, col;
    T val;
    Node *next;

    Node(int r, int c, T value)
    {
        row = r;
        col = c;
        val = value;
        next = NULL;
    }
};

template <typename T>
void insert_node(Node<T> **mat, Node<T> *newnode)
{
    Node<T> *curr = *mat;

    if (curr == NULL)
        *mat = newnode;
    else
    {
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = newnode;
    }
}

template <typename T>
Node<T> *addition_list(Node<T> *mat1, Node<T> *mat2)
{
    Node<T> *result = NULL;

    while (mat1 && mat2)
    {
        if (mat1->row == mat2->row && mat1->col == mat2->col)
        {
            Node<int> *newnode = new Node(mat1->row, mat1->col, mat1->val + mat2->val);
            insert_node(&result, newnode);
            mat1 = mat1->next;
            mat2 = mat2->next;
        }
        else if (mat1->row < mat2->row)
        {
            Node<int> *newnode = new Node(mat1->row, mat1->col, mat1->val);
            insert_node(&result, newnode);
            mat1 = mat1->next;
        }
        else if (mat1->row > mat2->row)
        {
            Node<int> *newnode = new Node(mat2->row, mat2->col, mat2->val);
            insert_node(&result, newnode);
            mat2 = mat2->next;
        }
        else
        {
            if (mat1->col < mat2->col)
            {
                Node<int> *newnode = new Node(mat1->row, mat1->col, mat1->val);
                insert_node(&result, newnode);
                mat1 = mat1->next;
            }
            else
            {
                Node<int> *newnode = new Node(mat2->row, mat2->col, mat2->val);
                insert_node(&result, newnode);
                mat2 = mat2->next;
            }
        }
    }

    while (mat1)
    {
        Node<int> *newnode = new Node(mat1->row, mat1->col, mat1->val);
        insert_node(&result, newnode);
        mat1 = mat1->next;
    }

    while (mat2)
    {
        Node<int> *newnode = new Node(mat2->row, mat2->col, mat2->val);
        insert_node(&result, newnode);
        mat2 = mat2->next;
    }
    return result;
}

template <typename T>
Node<T> *transpose_list(Node<T> *head)
{
    Node<T> *result = NULL;
    while (head)
    {
        Node<int> *newnode = new Node(head->col, head->row, head->val);
        insert_node(&result, newnode);
        head = head->next;
    }
    return result;
}

template <typename T>
void print_list(Node<T> *head, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (head->row == i && head->col == j)
            {
                cout << head->val << " ";
                head = head->next;
            }
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
}

template <typename T>
void test_print(Node<T> *head)
{
    while (head)
    {
        cout << head->row << " " << head->col << " " << head->val << endl;
        head = head->next;
    }
}

template <typename T>
Node<T> *mergeList(Node<T> *l1, Node<T> *l2)
{

    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    Node<T> *l3head;
    if (l1->row < l2->row)
    {
        l3head = l1;
        l1 = l1->next;
    }
    else if (l1->row > l2->row)
    {
        l3head = l2;
        l2 = l2->next;
    }
    else
    {
        if (l1->col < l2->col)
        {
            l3head = l1;
            l1 = l1->next;
        }
        else
        {
            l3head = l2;
            l2 = l2->next;
        }
    }

    Node<T> *l3tail = l3head;
    while ((l1 != nullptr) && (l2 != nullptr))
    {
        if (l1->row < l2->row)
        {
            l3tail->next = l1;
            l3tail = l3tail->next;
            l1 = l1->next;
        }
        else if (l1->row > l2->row)
        {
            l3tail->next = l2;
            l3tail = l3tail->next;
            l2 = l2->next;
        }
        else
        {
            if (l1->col < l2->col)
            {
                l3tail->next = l1;
                l3tail = l3tail->next;
                l1 = l1->next;
            }
            else
            {
                l3tail->next = l2;
                l3tail = l3tail->next;
                l2 = l2->next;
            }
        }
    }

    if (l1 == NULL)
        l3tail->next = l2;
    if (l2 == NULL)
        l3tail->next = l1;

    return l3head;
}

template <typename T>
Node<T> *sortList(Node<T> *head)
{

    if (head == NULL || head->next == NULL)
        return head;

    Node<T> *slow = head;
    Node<T> *fast = head->next;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node<T> *head2 = slow->next;
    slow->next = NULL;

    head = sortList(head);
    head2 = sortList(head2);

    return mergeList(head, head2);
}

template <typename T>
Node<T> *multiply_list(Node<T> *mat1, Node<T> *m2)
{
    Node<T> *result = NULL;
    while (mat1)
    {
        Node<T> *mat2 = m2;
        while (mat2)
        {
            if (mat1->col == mat2->col)
            {
                Node<T> *temp = result;
                bool flag = false;
                while (temp)
                {
                    if (temp->row == mat1->row && temp->col == mat2->row)
                    {
                        flag = true;
                        temp->val += (mat1->val * mat2->val);
                        break;
                    }
                    temp = temp->next;
                }
                if (!flag)
                {
                    Node<T> *newnode = new Node(mat1->row, mat2->row, mat1->val * mat2->val);
                    insert_node(&result, newnode);
                }
            }
            mat2 = mat2->next;
        }
        mat1 = mat1->next;
    }
    return result;
}

int main()
{

    int type_of_ds;
    cin >> type_of_ds;

    if (type_of_ds == 1) // array
    {
        int operation;
        cin >> operation;
        if (operation == 1)
        {
            int n1, m1;
            cin >> n1 >> m1;
            sparseArray<int> mat1;
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < m1; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                        mat1.push(i, j, a);
                }
            }

            int n2, m2;
            cin >> n2 >> m2;
            sparseArray<int> mat2;
            for (int i = 0; i < n2; i++)
            {
                for (int j = 0; j < m2; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                        mat2.push(i, j, a);
                }
            }

            if (n1 != n2 || m1 != m2)
            {
                cout << "Addition not possible" << endl;
                return 0;
            }
            sparseArray<int> result = addition_arr<int>(&mat1, &mat2);
            cout << endl;
            cout << "Addition Result:" << endl;
            print_arr(&result, n1, m1);
        }
        else if (operation == 2)
        {
            int n1, m1;
            cin >> n1 >> m1;
            sparseArray<int> mat;
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < m1; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                        mat.push(i, j, a);
                }
            }
            sparseArray<int> result(mat.curr_size);
            result = transpose_arr(&mat, n1, m1);
            cout << endl;
            cout << "Transpose Result:" << endl;
            print_arr(&result, m1, n1);
        }
        else
        {
            int n1, m1;
            cin >> n1 >> m1;
            sparseArray<int> mat1;
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < m1; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                        mat1.push(i, j, a);
                }
            }

            int n2, m2;
            cin >> n2 >> m2;
            sparseArray<int> mat2;
            for (int i = 0; i < n2; i++)
            {
                for (int j = 0; j < m2; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                        mat2.push(i, j, a);
                }
            }

            if (m1 != n2)
            {
                cout << "Multiplication not possible" << endl;
                return 0;
            }
            sparseArray<int> mat2_transpose = transpose_arr(&mat2, n2, m2);
            sparseArray<int> result = multiply_arr<int>(&mat1, &mat2_transpose);
            cout << endl;
            cout << "Multiplication Result:" << endl;
            print_arr(&result, n1, m2);
        }
    }
    else
    {
        int operation;
        cin >> operation;
        if (operation == 1)
        {
            Node<int> *mat1 = NULL;
            int n1, m1;
            cin >> n1 >> m1;
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < m1; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                    {
                        Node<int> *newnode = new Node(i, j, a);
                        insert_node(&mat1, newnode);
                    }
                }
            }

            Node<int> *mat2 = NULL;
            int n2, m2;
            cin >> n2 >> m2;
            for (int i = 0; i < n2; i++)
            {
                for (int j = 0; j < m2; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                    {
                        Node<int> *newnode = new Node(i, j, a);
                        insert_node(&mat2, newnode);
                    }
                }
            }
            if (n1 != n2 || m1 != m2)
                cout << "Addition not possible" << endl;
            else
            {
                Node<int> *result = addition_list(mat1, mat2);
                cout << endl;
                cout << "Addition Result:" << endl;
                print_list(result, n1, m1);
            }
        }
        else if (operation == 2)
        {
            Node<int> *mat1 = NULL;
            int n1, m1;
            cin >> n1 >> m1;
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < m1; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                    {
                        Node<int> *newnode = new Node(i, j, a);
                        insert_node(&mat1, newnode);
                    }
                }
            }

            Node<int> *temp = transpose_list(mat1);
            Node<int> *result = sortList(temp);
            cout << endl;
            cout << "Transpose Result:" << endl;
            print_list(result, m1, n1);
        }
        else
        {
            Node<int> *mat1 = NULL;
            int n1, m1;
            cin >> n1 >> m1;
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < m1; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                    {
                        Node<int> *newnode = new Node(i, j, a);
                        insert_node(&mat1, newnode);
                    }
                }
            }

            Node<int> *mat2 = NULL;
            int n2, m2;
            cin >> n2 >> m2;
            for (int i = 0; i < n2; i++)
            {
                for (int j = 0; j < m2; j++)
                {
                    int a;
                    cin >> a;
                    if (a != 0)
                    {
                        Node<int> *newnode = new Node(i, j, a);
                        insert_node(&mat2, newnode);
                    }
                }
            }

            if (m1 != n2)
                cout << "Multiplication not possible" << endl;
            else
            {
                mat2 = transpose_list(mat2);
                mat2 = sortList(mat2);
                Node<int> *result = multiply_list(mat1, mat2);
                cout << endl;
                cout << "Multiplication Result:" << endl;
                print_list(result, n1, m2);
            }
        }
    }
    return 0;
}