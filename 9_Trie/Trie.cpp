#include <iostream>

using namespace std;

struct TrieNode
{
    TrieNode *next[27];
    TrieNode()
    {
        for (int i = 0; i < 27; ++i)
        {
            next[i] = NULL;
        }
    }
};

struct Trie
{
    TrieNode root;
    void deleteHelper(TrieNode *parent)
    {
        if (parent == NULL)
        {
            return;
        }
        for (int i = 0; i < 27; ++i)
        {
            deleteHelper(parent->next[i]);
        }
        delete parent;
    }
    ~Trie()
    {
        for (int i = 0; i < 27; ++i)
        {
            deleteHelper(root.next[i]);
        }
    }
    void add(const string &s)
    {
        TrieNode *parent = &root;
        for (int i = 0; i < s.length(); ++i)
        {
            int idx = s[i] - 'a' + 1;
            if (parent->next[idx] != NULL)
            {
                parent = parent->next[idx];
            }
            else
            {
                TrieNode *node = new TrieNode();
                parent->next[idx] = node;
                parent = node;
            }
        }
        if (parent->next[0] == NULL)
        {
            parent->next[0] = new TrieNode();
        }
    }

    static void hintHelper(const TrieNode *parent, string &path)
    {
        if (parent == NULL)
        {
            return;
        }
        // cout << int(parent->val) << endl;       
        if (parent->next[0] != NULL)
        {
            cout << path << endl;
        }
        path.push_back('\0');
        for (int i = 1; i < 27; ++i)
        {
            path.back() = 'a' + i - 1;
            hintHelper(parent->next[i], path);
        }
        path.pop_back();
    }

    void hint(const string &s) const
    {
        const TrieNode *parent = &root;
        for (int i = 0; i < s.length(); ++i)
        {
            int idx = s[i] - 'a' + 1;
            TrieNode *next = parent->next[idx];
            // for(int j = 0; j < 27; ++j){
            //     cout << parent->next[j] << " ";
            // }
            // cout << endl;
            if (next == NULL)
            {
                return;
            }
            // cout << "find:" << s[i] << endl;
            parent = next;
        }
        string path = s;
        //cout << "hint:" << path << endl;
        hintHelper(parent, path);
    }
};

int main()
{
    Trie t;
    t.add("ability");
    t.add("abandon");
    t.add("abnormal");
    t.add("apple");
    t.add("billion");
    t.add("binary");
    t.add("bibliography");
    t.add("abc");
    t.add("abd");
    t.add("bill");
    t.hint("de");
}
