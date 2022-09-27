#include <iostream>
#include <vector>
using namespace std;

struct node
{
    node *arr[26];
    bool ends_here = false;
    string word = "";
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

    void dfs(char **board, int i, int j, int r, int c, node *root, vector<string> &result)
    {
        char ch = board[i][j];

        if (ch == '0' || root->arr[ch - 'a'] == NULL)
            return;

        root = root->arr[ch - 'a'];
        if (root->word.size())
        {
            result.push_back(root->word);
            root->word = "";
        }

        board[i][j] = '0';

        if (i > 0)
            dfs(board, i - 1, j, r, c, root, result); // up
        if (j > 0)
            dfs(board, i, j - 1, r, c, root, result); // left
        if (i < r - 1)
            dfs(board, i + 1, j, r, c, root, result); // down
        if (j < c - 1)
            dfs(board, i, j + 1, r, c, root, result); // right

        board[i][j] = ch;
    }
};

int main()
{
    int r, c;
    cin >> r >> c;

    char **board;
    board = new char *[r];
    for (int i = 0; i < r; i++)
    {
        board[i] = new char[c];
        for (int j = 0; j < c; j++)
            cin >> board[i][j];
    }

    int x;
    cin >> x;
    Trie t;

    for (int i = 0; i < x; i++)
    {
        string s;
        cin >> s;
        t.insert(s);
    }

    vector<string> v;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            t.dfs(board, i, j, r, c, t.root, v);

    cout << v.size() << endl;
    for (auto a : v)
        cout << a << endl;
    return 0;
}