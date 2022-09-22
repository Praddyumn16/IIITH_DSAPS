#include <bits/stdc++.h>
using namespace std;

class LRUCache
{
public:
    class node
    {
    public:
        int key;
        int val;
        node *next;
        node *prev;
        node(int key1, int val1)
        {
            key = key1;
            val = val1;
        }
    };

    node *head = new node(-1, -1);
    node *tail = new node(-1, -1);

    int cap;
    unordered_map<int, node *> mp;

    LRUCache(int capacity)
    {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    void addNode(node *curr)
    { // adding node in front of the head
        node *temp = head->next;
        head->next = curr;
        curr->next = temp;
        curr->prev = head;
        temp->prev = curr;
    }

    void deleteNode(node *curr)
    {
        node *prev_ = curr->prev;
        node *next_ = curr->next;
        prev_->next = next_;
        next_->prev = prev_;
    }

    int get(int key_)
    {
        if (mp.find(key_) == mp.end())
            return -1;
        else
        {
            node *curr = mp[key_];
            int ans = curr->val;
            deleteNode(curr);
            addNode(curr);
            mp[key_] = head->next;
            return ans;
        }
    }

    void put(int key_, int value_)
    {
        if (mp.find(key_) != mp.end())
        {
            node *existing = mp[key_];
            deleteNode(existing);
        }
        else
        {
            if (mp.size() == cap)
            {
                node *toBeDeleted = tail->prev;
                mp.erase(toBeDeleted->key);
                deleteNode(toBeDeleted);
            }
        }
        node *curr = new node(key_, value_);
        addNode(curr);
        mp[key_] = head->next;
    }
};

