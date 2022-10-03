#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#define ll long long

using namespace std;

const clock_t start_time = clock();

class couple
{
public:
    ll first;
    ll second;
};

class heap
{
public:
    couple *arr;
    ll capacity, curr_size;

    heap(ll cap)
    {
        capacity = cap;
        curr_size = 0;
        arr = new couple[cap];
    }

    couple top()
    {
        return arr[0];
    }

    ll size()
    {
        return curr_size;
    }

    void push(couple a)
    {
        arr[curr_size] = a;
        ll i = curr_size;
        while (i != 0 && arr[(i - 1) / 2].first > arr[i].first)
        {
            couple temp = arr[i];
            arr[i] = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
        curr_size++;
    }

    void pop()
    {
        if (curr_size == 1)
        {
            curr_size = 0;
            return;
        }
        arr[0] = arr[curr_size - 1];
        heapify(0);
        curr_size--;
    }

    void heapify(ll i)
    {
        ll l = 2 * i + 1;
        ll r = 2 * i + 2;
        ll smallest = i;
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

int main(int argc, char *argv[])
{
    string input_file = argv[1], output_file = argv[2];

    ll number_of_chunks = 1, chunk_size = 1000000;
    vector<ll> curr_chunk;
    ll i = 0, flag = 1;
    string value;

    ifstream in(input_file);

    while (getline(in, value, ' '))
    {
        flag = 1;
        stringstream ss;
        ss << value;
        ll x;
        ss >> x;
        curr_chunk.push_back(x);
        i++;
        if (i == chunk_size)
        {
            sort(curr_chunk.begin(), curr_chunk.end());
            string curr_chunk_output_file = "./data/file" + to_string(number_of_chunks) + ".txt";
            ofstream out(curr_chunk_output_file.c_str());
            for (ll j = 0; j < i; j++)
                out << curr_chunk[j] << ' ';
            out.close();

            curr_chunk.clear();
            i = 0;
            number_of_chunks++;
            flag = 0;
        }
    }

    if (flag)
    {
        sort(curr_chunk.begin(), curr_chunk.end());
        string curr_chunk_output_file = "./data/file" + to_string(number_of_chunks) + ".txt";
        ofstream out(curr_chunk_output_file);
        for (ll j = 0; j < i; j++)
            out << curr_chunk[j] << ' ';
        out.close();
    }
    else
        number_of_chunks--;

    in.close();
    curr_chunk.clear();

    heap minHeap(number_of_chunks + 1);
    ifstream *chunks = new ifstream[number_of_chunks];

    for (ll i = 1; i <= number_of_chunks; i++)
    {
        string sorted_input = "./data/file" + to_string(i) + ".txt";
        chunks[i - 1].open(sorted_input);
        ll firstValue;
        chunks[i - 1] >> firstValue;
        couple c;
        c.first = firstValue;
        c.second = i - 1;
        minHeap.push(c);
    }

    ofstream out(output_file);

    while (minHeap.size())
    {
        couple pair = minHeap.top();
        minHeap.pop();
        out << pair.first << endl;
        ll nextValue;
        flush(out);
        if (chunks[pair.second] >> nextValue)
        {
            couple c;
            c.first = nextValue;
            c.second = pair.second;
            minHeap.push(c);
        }
    }

    for (ll i = 1; i <= number_of_chunks; i++)
        chunks[i - 1].close();

    out.close();
    delete[] chunks;

    float temp = float(clock() - start_time) / CLOCKS_PER_SEC;
    float total_time = round(temp * 100) / 100;
    cout << "The output file was generated in: " << total_time << " seconds." << endl;
    return 0;
}