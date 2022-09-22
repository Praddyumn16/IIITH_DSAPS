#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int key, value, count;
    Node *prev;
    Node *next;
    Node(int key_, int value_)
    {
        key = key_;
        value = value_;
        count = 1;
    }
};

struct List
{
    int size;
    Node *head;
    Node *tail;
    List()
    {
        size = 0;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    void addNode(Node *newnode)
    {
        size++;
        Node *temp = head->next;
        head->next = newnode;
        newnode->next = temp;
        newnode->prev = head;
        temp->prev = newnode;
    }

    void deleteNode(Node *curr)
    {
        size--;
        Node *prev_ = curr->prev;
        Node *next_ = curr->next;
        prev_->next = next_;
        next_->prev = prev_;
    }
};

class LFUCache
{
public:
    map<int, List *> freq;
    map<int, Node *> mp;

    int cap, min_freq, curr_size;

    LFUCache(int capacity)
    {
        cap = capacity;
        curr_size = 0;
        min_freq = 0;
    }

    int get(int key)
    {
        if (mp.find(key) == mp.end())
            return -1;
        else
        {
            Node *curr = mp[key];
            int prev_freq = curr->count;
            int ans = curr->value;

            // updating the frequency since this key is accessed again
            mp.erase(key);
            List *prev_list = freq[prev_freq];
            prev_list->deleteNode(curr);

            if (prev_freq == min_freq && prev_list->size == 0)
                min_freq++;

            List *newList = new List();
            if (freq.find(prev_freq + 1) != freq.end())
                newList = freq[prev_freq + 1];
            curr->count++;
            newList->addNode(curr);
            freq[curr->count] = newList;
            mp[key] = curr;
            return ans;
        }
    }

    void put(int key, int value)
    {
        if (cap == 0)
            return;
        if (mp.find(key) != mp.end())
        {
            Node *curr = mp[key];
            curr->value = value;

            // updating the frequency since this key is accessed again
            mp.erase(key);
            int prev_freq = curr->count;
            List *prev_list = freq[prev_freq];
            prev_list->deleteNode(curr);

            if (prev_freq == min_freq && prev_list->size == 0)
                min_freq++;

            List *newList = new List();
            if (freq.find(prev_freq + 1) != freq.end())
                newList = freq[prev_freq + 1];
            curr->count++;
            newList->addNode(curr);
            freq[curr->count] = newList;
            mp[key] = curr;
        }
        else
        {
            if (curr_size == cap)
            {
                List *list = freq[min_freq];
                mp.erase(list->tail->prev->key);
                freq[min_freq]->deleteNode(list->tail->prev);
                curr_size--;
            }
            curr_size++;
            min_freq = 1;
            List *newList = new List();
            if (freq.find(min_freq) != freq.end())
                newList = freq[min_freq];
            Node *newnode = new Node(key, value);
            newList->addNode(newnode);
            mp[key] = newnode;
            freq[min_freq] = newList;
        }
    }
};
