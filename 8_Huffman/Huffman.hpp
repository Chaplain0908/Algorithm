#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <queue>
#include <stdio.h>

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int val;
    TreeNode()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        val = 0;
    }
};

struct HuffmanComparator
{
    bool operator()(TreeNode *a, TreeNode *b)
    {
        return a->val > b->val;
    }
};

class HuffmanTree
{
protected:
    TreeNode node[511];

public:
    HuffmanTree() {}
    TreeNode *build()
    {
        std::priority_queue<TreeNode *, std::vector<TreeNode *>, HuffmanComparator> pq;
        for (int i = 0; i < 256; ++i)
        {
            if (node[i].val != 0)
            {
                pq.push(&node[i]);
            }
        }
        TreeNode *sum = &node[256];
        while (pq.size() > 1)
        {
            TreeNode *a = pq.top();
            pq.pop();
            TreeNode *b = pq.top();
            pq.pop();
            sum->left = a;
            sum->right = b;
            sum->val = a->val + b->val;
            a->parent = sum;
            b->parent = sum;
            pq.push(sum);
            sum++;
        }
        return pq.top();
    }
};






#endif 