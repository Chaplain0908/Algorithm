#include <iostream>
#include <queue>
#include <stdio.h>
#include "Huffman.hpp"

struct BitInputBuffer
{
    char c;
    int cnt;
    FILE *fp;
    BitInputBuffer(FILE *fp)
    {
        c = 0;
        cnt = 0;
        this->fp = fp;
    }
    int get()
    {
        if (cnt == 0)
        {
            int a = fgetc(fp);
            if (a == EOF)
            {
                return EOF;
            }
            c = a;
        }
        int b = (c >> cnt) & 1;
        cnt++;
        if (cnt == 8)
        {
            cnt = 0;
        }
        return b;
    }
};

class HuffmanUncompresser : HuffmanTree
{
public:
    HuffmanUncompresser() {}

    void uncompress(FILE *fin, FILE *fout)
    {
        for (int i = 0; i < 256; ++i)
        {
            fread(&node[i].val, sizeof(int), 1, fin);
        }
        TreeNode *root = build();
        TreeNode *cur = root;

        BitInputBuffer inputBuffer(fin);
        int b;
        while ((b = inputBuffer.get()) != EOF)
        {
            if (b == 0)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
            if(cur == NULL){
                return;
            }
            if (cur->left == NULL && cur->right == NULL)
            {
                char c = cur - node;
                std::cout << c << std::endl;
                fputc(c, fout);
                cur = root;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./uncompress .dat .txt" << std::endl;
        exit(EXIT_FAILURE);
    }
    FILE *fin = fopen(argv[1], "rb");
    if (fin == NULL)
    {
        std::cout << "Failure in opening compress file" << std::endl;
        exit(EXIT_FAILURE);
    }
    FILE *fout = fopen(argv[2], "wb");
    if (fout == NULL)
    {
        std::cout << "Failure in opening uncompress file" << std::endl;
        fclose(fin);
        exit(EXIT_FAILURE);
    }
    HuffmanUncompresser h;
    h.uncompress(fin, fout);
    fclose(fin);
    fclose(fout);
}