#include <vector>
#include <iostream>
#include <string>
#include <limits.h>
using namespace std;

struct node
{
    node *arr[26];
    bool ends_here = false;
    string word;
};

class Trie
{
public:
    node *root;

    Trie()
    {
        root = new node();
    }

    void insert(string word)
    {
        node *temp = root;
        for (char ch : word)
        {
            if (temp->arr[ch - 'a'] == NULL)
                temp->arr[ch - 'a'] = new node();
            temp = temp->arr[ch - 'a'];
        }
        temp->ends_here = true;
        temp->word = word;
    }

    bool search(string word)
    {
        node *temp = root;
        for (char ch : word)
        {
            if (temp->arr[ch - 'a'] == NULL)
                return false;
            temp = temp->arr[ch - 'a'];
        }
        return temp->ends_here;
    }

    void bfs(string curr, node *temp, vector<string> &v)
    {
        if (temp->ends_here)
        {
            v.push_back(curr);
            return;
        }
        for (int i = 0; i < 26; i++)
        {
            if (temp->arr[i] != NULL)
                bfs(curr + (char)(i + 97), temp->arr[i], v);
        }
    }

    void autoComplete(string prefix)
    {
        node *temp = root;
        vector<string> v;
        int i;
        for (char ch : prefix)
        {
            if (temp->arr[ch - 'a'] == NULL)
            {
                cout << 0 << endl;
                return;
            }
            temp = temp->arr[ch - 'a'];
        }
        bfs(prefix, temp, v);
        cout << v.size() << endl;
        for (auto a : v)
            cout << a << endl;
    }

    void fill(node *temp, char c, string prefix, vector<int> prev_row, vector<string> &v)
    {
        vector<int> columns(prefix.size() + 1);
        vector<int> curr_row;

        curr_row.push_back(prev_row[0] + 1);

        for (int i = 1; i <= prefix.size(); i++)
        {
            if (prefix[i - 1] == c)
                curr_row.push_back(prev_row[i - 1]);
            else
                curr_row.push_back(min(prev_row[i - 1] + 1, min(curr_row[i - 1] + 1, prev_row[i] + 1)));
        }

        if (curr_row[prefix.size()] <= 3 && temp->ends_here)
            v.push_back(temp->word);

        int mini = INT_MAX;
        for (auto a : curr_row)
            mini = min(mini, a);

        if (mini <= 3)
        {
            for (int i = 0; i < 26; i++)
            {
                if (temp->arr[i] != NULL)
                    fill(temp->arr[i], (char)(i + 97), prefix, curr_row, v);
            }
        }
    }

    void autoCorrect(string prefix)
    {
        vector<int> curr_row(prefix.size() + 1);
        vector<string> v;

        node *temp = root;
        for (int i = 0; i < 26; i++)
        {
            if (temp->arr[i] != NULL)
                fill(temp->arr[i], (char)(i + 97), prefix, curr_row, v);
        }

        cout << v.size() << endl;
        for (auto a : v)
            cout << a << endl;
    }
};

int main()
{
    Trie t;

    int n, q;
    cin >> n >> q;

    while (n--)
    {
        string s;
        cin >> s;
        t.insert(s);
    }

    while (q--)
    {
        int a;
        string s;
        cin >> a >> s;

        if (a == 1)
            cout << t.search(s) << endl;
        else if (a == 2)
            t.autoComplete(s);
        else
            t.autoCorrect(s);
    }

    return 0;
}