#include <iostream>
using namespace std;
#define int long long

void merge(int *arr, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = 0;
    int n = right - left + 1;

    int temp[right - left + 1];

    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = 0; i < n; i++)
        arr[i + left] = temp[i];
}

void sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + ((right - left) / 2));
        sort(arr, left, mid);
        sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

class couple
{
public:
    int first;
    int second;
};

class heap
{
    couple *arr;
    int capacity, curr_size;

public:
    heap(int cap)
    {
        capacity = cap;
        curr_size = 0;
        arr = new couple[cap];
    }

    couple top()
    {
        return arr[0];
    }

    int size()
    {
        return curr_size;
    }

    void push(couple a)
    {
        curr_size++;
        arr[curr_size - 1] = a;

        int i = curr_size - 1;
        int parent = (i - 1) / 2;
        while (i != 0 && arr[parent].first > arr[i].first)
        {
            couple temp = arr[i];
            arr[i] = arr[parent];
            arr[parent] = temp;
            i = parent;
        }
    }

    void pop()
    {
        if (curr_size == 1)
        {
            curr_size--;
            return;
        }
        arr[0] = arr[curr_size - 1];
        heapify(0);
        curr_size--;
    }

    void heapify(int i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;
        if (l < curr_size && arr[l].first < arr[i].first)
            smallest = l;
        if (r < curr_size && arr[r].first < arr[smallest].first)
            smallest = r;
        if (smallest != i)
        {
            couple temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            heapify(smallest);
        }
    }
};

signed main()
{
    int n, k;
    cin >> n >> k;
    int elements[n];
    int max_sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> elements[i];
        if (elements[i] > 0)
            max_sum += elements[i];
        else
            elements[i] = -elements[i];
    }

    sort(elements, 0, n - 1);

    if (k == 1)
    {
        cout << max_sum;
        return 0;
    }

    int to_be_subtracted[k - 1];
    int i = 0;

    heap pq(k);

    couple x;
    x.first = elements[0];
    x.second = 0;

    pq.push(x);

    while (pq.size() && i < k - 1)
    {
        couple curr = pq.top();
        pq.pop();

        to_be_subtracted[i++] = curr.first;
        int idx = curr.second;

        if (idx < n - 1)
        {
            couple a, b;
            a.first = curr.first + elements[idx + 1];
            b.first = elements[idx + 1] + (curr.first - elements[idx]);
            a.second = b.second = idx + 1;
            pq.push(a);
            pq.push(b);
        }
    }

    cout << max_sum << " ";
    for (auto a : to_be_subtracted)
        cout << max_sum - a << " ";
    cout << endl;
    return 0;
}